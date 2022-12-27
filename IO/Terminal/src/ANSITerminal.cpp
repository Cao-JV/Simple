/*
 * Simple ANSI Terminal v0.1αß
 *
 * An unsophisticated ANSITerminal class for quick commandline development.
 * This Is the standard terminal UTF8 ersion - using non-wide characters.
 *
 *  The MIT License
 *
 * Copyright 2022, CaoS.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "ANSITerminal.hpp"
#include <stdarg.h>
#include <chrono>


#ifdef __linux__
    #include <sys/ioctl.h> 
    #include <unistd.h> 
#endif

using std::cout;
using std::cin;
using std::endl;
using std::chrono::steady_clock;
using std::string;

namespace Simple {
    namespace IO {

        ANSITerminal::ANSITerminal(bool EchoOn, std::string SystemLocale) :  AStdTerminal(){
            //std::setlocale(LC_ALL, SystemLocale.c_str());
            this->_initialize(EchoOn);
        }
        ANSITerminal::~ANSITerminal() {
            #ifdef __linux__
            // Reset ANSITerminal I/O settings to original state before intercept
            tcsetattr(0, TCSANOW, &this->m_OriginalTerminal);            
            #endif
        }
        void ANSITerminal::ClearScreen() {
            this->_sendCommand('J', std::to_string(TerminalClear::Entire));
        }
        void ANSITerminal::ClearLine() {
            this->_sendCommand('K', std::to_string(TerminalClear::ToEnd));
        }
        void ANSITerminal::FlushOut() {
            cout << endl;
        }
        void ANSITerminal::Print(const char Char) {
            cout << this->_translate(Char);
            // We're letting the internal handlers parse the codes, so check if screen pos changed
            //this->GetXY(this->m_CurrentX, this->m_CurrentY);
        }
        void ANSITerminal::Print(const char *Format, ...) {
            va_list args;
            va_start(args, Format);
             this->VPrint(Format, args);
            va_end(args);
        }
        /**
         * @brief Poor dev's printf - to preserve "C++"ness in output. 
         * Yes, I am aware variadic args is a "C" thing.
         * @todo replace with Variadic template
         * @param Format 
         * @param Args 
         */
        void ANSITerminal::VPrint(const std::string Format, va_list Args) {
            // We're going to call this over & over (& over) again in our app. Let's just hold on to the memory.
            static unsigned int i; // This is going to parse our ints
            static std::string s;     // "     " "     "  "     "   strings
            static char formatOutput;
            
            for(int formatIndex = 0; formatIndex < Format.length(); formatIndex++) 
            {   
                if (formatIndex < Format.length()) {
                    formatOutput = Format[formatIndex];
                }
                if (formatOutput == '%') {
                    // If there more chars in the wcstring, get the next one, or move on. Don't worry about the lack of code...
                    if (formatIndex < Format.length() - 1) {
                        formatIndex++; 
                        formatOutput = Format[formatIndex];
                    }

                    switch(formatOutput) 
                    { 
                        case 'c' : i = va_arg(Args,int);
                                   cout << this->_translate(i);
                                    break; 
                        case 's': s = va_arg(Args,char *);
                                    cout << this->_translate(s);
                                    break;
                        case 'x': i = va_arg(Args,unsigned int);
                                    cout << std::hex << i << std::dec; 

                                    break; 
                        case 'o': i = va_arg(Args,unsigned int);
                                    cout << std::oct << i << std::dec;
                                    break; 

                        case 'i' : i = va_arg(Args,int);
                                    cout << i;
                                    break; 
                        // ..it won't be left dangling if there were no more chars
                        default:    cout << this->_translate(formatOutput);
                                    break;


                    } 
                } else {
                    if (formatIndex < Format.length()) 
                    cout << this->_translate(formatOutput);
                } 
            }
            va_end(Args); 
        }
        void ANSITerminal::Print(const std::string Format, ...) {
            va_list args; 

            va_start(args, Format);
            this->Print(Format.c_str(), args);
            va_end(args);
        }
        void ANSITerminal::PrintLn(const char *Format, ...) {
            va_list args; 

            va_start(args, Format);
            this->Print(Format, args);
            va_end(args);
            cout << '\n';
        }
        void ANSITerminal::PrintLn(const std::string Format, ...) {
            va_list args; 
            va_start(args, Format);
            this->PrintLn(Format.c_str(), args);
            va_end(args);
            
        }
         int ANSITerminal::GetChar(const int TimeOutMS) {
             char result = {0};
            std::chrono::milliseconds maxtime{TimeOutMS};
            auto starttime = steady_clock::now();
            auto currenttime = steady_clock::now();
            while(result == 0 && 
                  (TimeOutMS == 0 || std::chrono::duration_cast<std::chrono::milliseconds>(currenttime - starttime) < maxtime)) {
                result = cin.get();
                currenttime = steady_clock::now();
            }
             return result;
         }
         string ANSITerminal::GetLine(const char Terminator, const int MaxLength, const int TimeOutMS) {
            string result = string();
            char keypress = { 0 };
            std::chrono::milliseconds maxtime{TimeOutMS};
            auto starttime = steady_clock::now();
            auto currenttime = steady_clock::now();

            while (keypress != Terminator && 
                   (TimeOutMS == 0 || std::chrono::duration_cast<std::chrono::milliseconds>(currenttime - starttime) < maxtime)) {
                       keypress = this->GetChar(TimeOutMS);
                       if (keypress == 127
                           && result.length() > 0) {
                           this->CursorMove(1, TerminalCursorMovement::Left);
                           result.pop_back();
                       } else
                       if (keypress != Terminator && 
                            (MaxLength == 0 || result.length() < MaxLength)) {
                           result.push_back(keypress);
                       }
                   } 
            return result;
         }
         void ANSITerminal::GetMaxXY(int &X, int &Y) {
            #ifdef __linux__
            struct winsize result;
            // Not standard POSIX - Should use Linux, anyway.
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &result);
            
             X = result.ws_col;
             Y = result.ws_row;
             #endif
         }
         void ANSITerminal::GetXY(int &X, int &Y) {
             #ifdef __linux__
             // Soo... apparently Linux isn't advanced enough to just have a function... You need to talk to the terminal. If it supports being talked to.
             string result;
             int semiColonIndex = 0
                ,startingIndex = 2
                ,endingIndex = 1;

             this->_sendCommand('n', "6");
             result = this->GetLine('R', 0);
             if (result.length()) {
                cout << "(" << result << ")" << endl;
                semiColonIndex = result.find_first_of(';');
                endingIndex = result.find_first_of('R') - 1;
                if (semiColonIndex == startingIndex) {
                    X = 1;
                } else {
                    X = std::stoi(result.substr(startingIndex, semiColonIndex - startingIndex));
                }
                Y = std::stoi(result.substr(semiColonIndex + 1, endingIndex - (semiColonIndex + 1)));
             } else {
                 cout << "!darn!";
             }
             #endif
         }
         void ANSITerminal::SetMaxXY(const int X, const int Y) {
             string commandData = "8;";
             commandData.append(std::to_string(Y));
             commandData.push_back(';');
             commandData.append(std::to_string(X));
             this->_sendCommand('t', commandData);
             // If we broke the upper physical boundaries, this could be different than specified
             this->GetMaxXY(this->m_MaxX, this->m_MaxY);
         }
         void ANSITerminal::SetXY(const int X, const int Y, const bool AsEdit) {
             // ANSITerminal may have been resized... Will add a signal handler, maybe.
             this->GetMaxXY(this->m_MaxX, this->m_MaxY);
             this->m_CurrentX = (X > this->m_MaxX ? this->m_MaxX : 
                               (X > 0 ? X : 1));
             this->m_CurrentY = (Y > this->m_MaxY ? this->m_MaxY : 
                               (Y > 0 ? Y : 1));
             this->_sendCommand((AsEdit ? 'H' : 'f'), std::to_string(this->m_CurrentY) + ";" + std::to_string(this->m_CurrentX));
         }
         void ANSITerminal::CursorMove(const int Value, const TerminalCursorMovement Movement) {
             this->_sendCommand((char)Movement, std::to_string(Value));
         }
         void ANSITerminal::SaveXY() {
             // keeping track manually - will come in handy
             this->GetXY(this->m_SavedX, this->m_SavedY);
             // ANSI command to save current position
             this->_sendCommand('s', "");
         }
         void ANSITerminal::RestoreXY() {
             // Keeping track manually - will come in handy
             this->m_CurrentX = this->m_SavedX;
             this->m_CurrentY = this->m_SavedY;
             // ANSI command to return to saved position
             this->_sendCommand('u', "");
         }
         void ANSITerminal::SetForegroundColour(const int ForegroundColour) {
            switch (this->m_ColourMode) {
                case TerminalColourModes::Modern: {
                                // Modern terminals can support 256 (8bit) colours. starting at 0 & counting up. Like a normal system.
                                // However, the original spec had already broke the colours into 8-index pages (see below). So this choice of commands seems arbitrary &
                                // unintuitive. I've written this in C++, let that sink in.
                                this->_sendCommand('m', "38;5;" + std::to_string(ForegroundColour));
                            }
                            break;
                case TerminalColourModes::Legacy: {
                                // Colours are described 0 to 7 & are either high or low. Giving a combination of 16 (4bit) colours. 
                                // Derive those colours from a less confusing scale of 0 to 15. It's broken like this because we used to have 2bit colour capability*.
                                int newColour = ((ForegroundColour < 8) ? ForegroundColour + 30 : ForegroundColour + 82);
                                std::string colourData;
                                colourData.append(std::to_string(newColour));
                                this->_sendCommand('m', colourData);
                        }
                        break;
                case TerminalColourModes::None:
                default: // If there is no Colour mode, don't change colour.
                        break;
             } 
             this->m_ForegroundColour = ForegroundColour;
         }
         void ANSITerminal::SetBackgroundColour(const int BackgroundColour) {
             // We could merge Fore & Back colours together for clever algorithmicness. I'd rather keep this readable & straight forward. So, I'm not clever.
            switch (this->m_ColourMode) {
                case TerminalColourModes::Modern: {
                                // Modern terminals can support 256 (8bit) colours. starting at 0 & counting up. Like a normal system.
                                // However, the original spec had already broke the colours into 8-index pages (see below). So this choice of commands seems arbitrary &
                                // unintuitive. I've written this in C++, let that sink in.
                                this->_sendCommand('m', "48;5;" + std::to_string(BackgroundColour));
                            }
                            break;
                case TerminalColourModes::Legacy: {
                                // Colours are described 0 to 7 & are either high or low. Giving a combination of 16 (4bit) colours. 
                                // Derive those colours from a less confusing scale of 0 to 15. It's broken like this because we used to have 2bit colour capability*.
                                int newColour = ((BackgroundColour < 8) ? BackgroundColour + 40 : BackgroundColour + 72);
                                std::string colourData = std::to_string(newColour);
                                this->_sendCommand('m', colourData);
                        }
                        break;
                case TerminalColourModes::None:
                default: // If there is no Colour mode, don't change colour.
                        break;
             } 
         }
        void ANSITerminal::SetConsoleColourMode(const TerminalColourModes Mode)  {
            this->m_ColourMode = Mode;
        }
        void ANSITerminal::SetTerminalAttribute(const TerminalAttributes Attribute, const bool State) {
            // If the setting is in the same state, let's just not bother doing it again
            if (this->IsTerminalAttributeOn(Attribute) == State) {
                return;
            }
            // Change the attribute to it's opposite value
            this->m_TerminalAttributes = ~Attribute;
            switch (Attribute) {
                case TerminalAttributes::Echo: {
                    this->_updateTerminalSettings(TerminalAttributes::Echo, State);
                }
                break;
                case TerminalAttributes::Cursor: {
                    this->_sendCommand((State ? 'h' : 'l'), "?25" );
                }
                break;
                default:break;
            }
            if (Attribute == TerminalAttributes::Cursor) {
                
            }
        }
        TerminalColourModes ANSITerminal::GetConsoleColourMode() {
            return this->m_ColourMode;
        }
        bool ANSITerminal::IsTerminalAttributeOn(const TerminalAttributes Attribute) {
            return (this->m_TerminalAttributes & Attribute) == Attribute;
        }
        void ANSITerminal::_initialize(bool EchoOn) {
            this->_loadTerminalSettings();
            this->_updateTerminalSettings(TerminalAttributes::Echo, EchoOn, false);
            this->_updateTerminalSettings(TerminalAttributes::LineBuffer, false);
            this->_sendCommand('m', "0");
            this->SetXY(1,1);
            this->SetForegroundColour(this->m_ForegroundColour);
            this->SetBackgroundColour(this->m_BackgroundColour);

        }
        void ANSITerminal::_updateTerminalSettings(TerminalAttributes Attribute, bool State, bool WriteSettingsNow) {
            #ifdef __linux__
                switch (Attribute) {
                    // If configured for Echo...
                    case TerminalAttributes::Echo: if (State) {
                                                        // ...Turn it on in the ANSITerminal
                                                        this->m_CurrentTerminal.c_lflag |= ECHO;
                                                    } else {
                                                        // ...Or, turn it off in ANSITerminal
                                                        this->m_CurrentTerminal.c_lflag &= ~ECHO;
                                                    }
                                                    break;
                    case TerminalAttributes::LineBuffer: if (State) {
                                                            // Disable Line Buffering for Input
                                                            this->m_CurrentTerminal.c_lflag |= ICANON;
                                                        } else {
                                                            // Disable Line Buffering for Input
                                                            this->m_CurrentTerminal.c_lflag &= ~ICANON;
                                                        }
                                                        break;
                }
                if (WriteSettingsNow) {
                    // Update the settings to ANSITerminal
                    tcsetattr(fileno(stdin), TCSANOW, &this->m_CurrentTerminal);
                }
            #endif
        }
        void ANSITerminal::_loadTerminalSettings() {
            #ifdef __linux__
            // Get ANSITerminal I/O settings
            tcgetattr(fileno(stdin), &this->m_OriginalTerminal);
            // Copy them
            this->m_CurrentTerminal = this->m_OriginalTerminal;
            #endif
        }
        void ANSITerminal::_sendCommand(const char code, const std::string data) {
            this->Print("%s%s%c", EscapeSequenceBegin.c_str(), data.c_str(), code);
        }
        std::string ANSITerminal::_translate(const char Char) {
             std::string result = {0};

            if (this->IsTerminalAttributeOn(TerminalAttributes::ExtendedAscii) && (Char < 0)) {
                char     output[3]  = {0};
                // life is good, until you try to call a negative array indice.
                wchar_t  input[1]  = {ASCIIToUTF8Chars[(unsigned char)Char]};
                int      size      =  0 ;
                size = wcstombs(output, input, 3);
                result.push_back(output[0]);
                result.push_back(output[1]);
                if (size == 3) {
                    result.push_back(output[2]);
                }
            } else {
                result.push_back(Char);
            }
            return result;
        }
        std::string ANSITerminal::_translate(const std::string String) {
            std::string result = "";
            for (unsigned char character : String) {
                   result.append(this->_translate(character));
            }
            return result;
        }
    } // NS:IO

} // NS: Simple

// * It was actually 3bit colour, but that ruined the wordplay.


