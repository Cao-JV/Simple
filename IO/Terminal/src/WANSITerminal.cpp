/*
 * Simple WANSITerminal v0.1αß
 *
 * An unsophisticated WANSITerminal class for quick commandline development.
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
#include "WANSITerminal.hpp"
#include <stdarg.h>
#include <chrono>


#ifdef __linux__
    #include <sys/ioctl.h> 
    #include <unistd.h> 
#endif

using std::wcout;
using std::wcin;
using std::endl;
using std::chrono::steady_clock;
using std::wstring;

namespace Simple {
    namespace IO {
        WANSITerminal::WANSITerminal(bool EchoOn, wstring SystemLocale) : AStdTerminal::AStdTerminal(){
            //std::setlocale(LC_ALL, SystemLocale.c_str());
            this->_initialize(EchoOn);
        }
        WANSITerminal::~WANSITerminal() {
            #ifdef __linux__
            // Reset WANSITerminal I/O settings to original state before intercept
            tcsetattr(0, TCSANOW, &this->m_OriginalTerminal);            
            #endif
        }
        void WANSITerminal::ClearScreen() {
            this->_sendCommand('J', std::to_wstring(TerminalClear::Entire));
        }
        void WANSITerminal::ClearLine() {
            this->_sendCommand('K', std::to_wstring(TerminalClear::ToEnd));
        }
        void WANSITerminal::FlushOut() {
            wcout << endl;
        }
        void WANSITerminal::Print(const wchar_t Char) {
            wcout << this->_translate(Char);
            // We're letting the internal handlers parse the codes, so check if screen pos changed
            //this->GetXY(this->m_CurrentX, this->m_CurrentY);
        }
        void WANSITerminal::Print(const wchar_t *Format, ...) {
            va_list args;
            va_start(args, Format);
            this->VPrint(Format, args);
            va_end(args);
        }
        void WANSITerminal::VPrint(const wstring Format, va_list Args) {
            // We're going to call this over & over (& over) again in our app. Let's just hold on to the memory.
            static unsigned int i; // This is going to parse our ints
            static wstring s;     // "     " "     "  "     "   strings
            static wchar_t formatOutput;
            
            for(int formatIndex = 0; formatIndex < Format.length(); formatIndex++) 
            {   
                if (formatIndex < Format.length()) {
                    formatOutput = Format[formatIndex];
                }
                if (formatOutput == '%') {
                    // If there more wchars in the wcstring, get the next one, or move on. Don't worry about the lack of code...
                    if (formatIndex < Format.length() - 1) {
                        formatIndex++; 
                        formatOutput = Format[formatIndex];
                    }

                    switch(formatOutput) 
                    { 
                        case 'c' : i = va_arg(Args,int);
                                   wcout << this->_translate(i);
                                    break; 
                        case 's': s = va_arg(Args,wchar_t *);
                                    wcout << this->_translate(s);
                                    break;
                        case 'x': i = va_arg(Args,unsigned int);
                                    wcout << std::hex << i << std::dec; 

                                    break; 
                        case 'o': i = va_arg(Args,unsigned int);
                                    wcout << std::oct << i << std::dec;
                                    break; 

                        case 'i' : i = va_arg(Args,int);
                                    wcout << i;
                                    break; 
                        // ..it won't be left dangling if there were no more wchars
                        default:    wcout << this->_translate(formatOutput);
                                    break;


                    } 
                } else {
                    if (formatIndex < Format.length()) 
                    wcout << this->_translate(formatOutput);
                } 
            }
            va_end(Args); 
        }
        void WANSITerminal::Print(const wstring Format, ...) {
            va_list args; 

            va_start(args, Format);
            this->Print(Format.c_str(), args);
            va_end(args);
        }
        void WANSITerminal::PrintLn(const wchar_t *Format, ...) {
            va_list args; 

            va_start(args, Format);
            this->Print(Format, args);
            va_end(args);
            wcout << '\n';
        }
        void WANSITerminal::PrintLn(const wstring Format, ...) {
            va_list args; 
            va_start(args, Format);
            this->PrintLn(Format.c_str(), args);
            va_end(args);
            
        }
         int WANSITerminal::GetChar(const int TimeOutMS) {
             wchar_t result = {0};
            std::chrono::milliseconds maxtime{TimeOutMS};
            auto starttime = steady_clock::now();
            auto currenttime = steady_clock::now();
            while(result == 0 && 
                  (TimeOutMS == 0 || std::chrono::duration_cast<std::chrono::milliseconds>(currenttime - starttime) < maxtime)) {
                result = wcin.get();
                currenttime = steady_clock::now();
            }
             return result;
         }
         wstring WANSITerminal::GetLine(const wchar_t Terminator, const int MaxLength, const int TimeOutMS) {
            wstring result = wstring();
            wchar_t keypress = { 0 };
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
         void WANSITerminal::GetMaxXY(int &X, int &Y) {
            #ifdef __linux__
            struct winsize result;
            // Not standard POSIX - Should use Linux, anyway.
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &result);
            
             X = result.ws_col;
             Y = result.ws_row;
             #endif
         }
         void WANSITerminal::GetXY(int &X, int &Y) {
             #ifdef __linux__
             // Soo... apparently Linux isn't advanced enough to just have a function... You need to talk to the terminal. If it supports being talked to.
             wstring result;
             int semiColonIndex = 0
                ,startingIndex = 2
                ,endingIndex = 1;

             this->_sendCommand('n', L"6");
             result = this->GetLine(L'R', 0);

             semiColonIndex = result.find_first_of(L';');
             endingIndex = result.find_first_of(L'R') - 1;
             X = std::stoi(result.substr(startingIndex, semiColonIndex - startingIndex));
             Y = std::stoi(result.substr(semiColonIndex + 1, endingIndex - (semiColonIndex + 1)));
             #endif
         }
         void WANSITerminal::SetMaxXY(const int X, const int Y) {
             wstring commandData = L"8;";
             commandData.append(std::to_wstring(Y));
             commandData.push_back(L';');
             commandData.append(std::to_wstring(X));
             this->_sendCommand('t', commandData);
             // If we broke the upper physical boundaries, this could be different than specified
             this->GetMaxXY(this->m_MaxX, this->m_MaxY);
         }
         void WANSITerminal::SetXY(const int X, const int Y, const bool AsEdit) {
             // WANSITerminal may have been resized... Will add a signal handler, maybe.
             this->GetMaxXY(this->m_MaxX, this->m_MaxY);
             this->m_CurrentX = (X > this->m_MaxX ? this->m_MaxX : 
                               (X > 0 ? X : 1));
             this->m_CurrentY = (Y > this->m_MaxY ? this->m_MaxY : 
                               (Y > 0 ? Y : 1));
             this->_sendCommand((AsEdit ? 'H' : 'f'), std::to_wstring(this->m_CurrentY) + L";" + std::to_wstring(this->m_CurrentX));
         }
         void WANSITerminal::CursorMove(const int Value, const TerminalCursorMovement Movement) {
             this->_sendCommand((char)Movement, std::to_wstring(Value));
         }
         void WANSITerminal::SaveXY() {
             // keeping track manually - will come in handy
             this->GetXY(this->m_SavedX, this->m_SavedY);
             // ANSI command to save current position
             this->_sendCommand('s', L"");
         }
         void WANSITerminal::RestoreXY() {
             // Keeping track manually - will come in handy
             this->m_CurrentX = this->m_SavedX;
             this->m_CurrentY = this->m_SavedY;
             // ANSI command to return to saved position
             this->_sendCommand('u', L"");
         }
         void WANSITerminal::SetForegroundColour(const int ForegroundColour) {
            switch (this->m_ColourMode) {
                case TerminalColourModes::Modern: {
                                // Modern terminals can support 256 (8bit) colours. starting at 0 & counting up. Like a normal system.
                                // However, the original spec had already broke the colours into 8-index pages (see below). So this choice of commands seems arbitrary &
                                // unintuitive. I've written this in C++, let that sink in.
                                this->_sendCommand('m', L"0;38;5;" + std::to_wstring(ForegroundColour));
                            }
                            break;
                case TerminalColourModes::Legacy: {
                                // Colours are described 0 to 7 & are either high or low. Giving a combination of 16 (4bit) colours. 
                                // Derive those colours from a less confusing scale of 0 to 15. It's broken like this because we used to have 2bit colour capability*.
                                int newColour = ((ForegroundColour < 8) ? ForegroundColour + 30 : ForegroundColour + 82);
                                wstring colourData;
                                colourData.append(std::to_wstring(newColour));
                                this->_sendCommand('m', colourData);
                        }
                        break;
                case TerminalColourModes::None:
                default: // If there is no Colour mode, don't change colour.
                        break;
             } 
             this->m_ForegroundColour = ForegroundColour;
         }
         void WANSITerminal::SetBackgroundColour(const int BackgroundColour) {
             // We could merge Fore & Back colours together for clever algorithmicness. I'd rather keep this readable & straight forward. So, I'm not clever.
            switch (this->m_ColourMode) {
                case TerminalColourModes::Modern: {
                                // Modern terminals can support 256 (8bit) colours. starting at 0 & counting up. Like a normal system.
                                // However, the original spec had already broke the colours into 8-index pages (see below). So this choice of commands seems arbitrary &
                                // unintuitive. I've written this in C++, let that sink in.
                                this->_sendCommand('m', L"0;48;5;" + std::to_wstring(BackgroundColour));
                            }
                            break;
                case TerminalColourModes::Legacy: {
                                // Colours are described 0 to 7 & are either high or low. Giving a combination of 16 (4bit) colours. 
                                // Derive those colours from a less confusing scale of 0 to 15. It's broken like this because we used to have 2bit colour capability*.
                                int newColour = ((BackgroundColour < 8) ? BackgroundColour + 40 : BackgroundColour + 72);
                                wstring colourData = std::to_wstring(newColour);
                                this->_sendCommand('m', colourData);
                        }
                        break;
                case TerminalColourModes::None:
                default: // If there is no Colour mode, don't change colour.
                        break;
             } 
         }
        void WANSITerminal::SetConsoleColourMode(const TerminalColourModes Mode)  {
            this->m_ColourMode = Mode;
        }
        void WANSITerminal::SetTerminalAttribute(const TerminalAttributes Attribute, const bool State) {
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
                    this->_sendCommand((State ? 'h' : 'l'), L"?25" );
                }
                break;
                default:break;
            }
            if (Attribute == TerminalAttributes::Cursor) {
                
            }
        }
        TerminalColourModes WANSITerminal::GetConsoleColourMode() {
            return this->m_ColourMode;
        }
        bool WANSITerminal::IsTerminalAttributeOn(const TerminalAttributes Attribute) {
            return (this->m_TerminalAttributes & Attribute) == Attribute;
        }
        void WANSITerminal::_initialize(bool EchoOn) {
            this->_loadTerminalSettings();
            this->_updateTerminalSettings(TerminalAttributes::Echo, EchoOn, false);
            this->_updateTerminalSettings(TerminalAttributes::LineBuffer, false);
            this->_sendCommand('m', L"0");
            this->SetXY(1,1);
            this->SetForegroundColour(this->m_ForegroundColour);
            this->SetBackgroundColour(this->m_BackgroundColour);

        }
        void WANSITerminal::_updateTerminalSettings(TerminalAttributes Attribute, bool State, bool WriteSettingsNow) {
            #ifdef __linux__
                switch (Attribute) {
                    // If configured for Echo...
                    case TerminalAttributes::Echo: if (State) {
                                                        // ...Turn it on in the WANSITerminal
                                                        this->m_CurrentTerminal.c_lflag |= ECHO;
                                                    } else {
                                                        // ...Or, turn it off in WANSITerminal
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
                    // Update the settings to WANSITerminal
                    tcsetattr(fileno(stdin), TCSANOW, &this->m_CurrentTerminal);
                }
            #endif
        }
        void WANSITerminal::_loadTerminalSettings() {
            #ifdef __linux__
            // Get WANSITerminal I/O settings
            tcgetattr(fileno(stdin), &this->m_OriginalTerminal);
            // Copy them
            this->m_CurrentTerminal = this->m_OriginalTerminal;
            #endif
        }
        void WANSITerminal::_sendCommand(const wchar_t code, const wstring data) {
             this->Print(L"%s%s%c", EscapeSequenceBegin.c_str(), data.c_str(), code);
        }
        wstring WANSITerminal::_translate(const wchar_t Char) {
            wstring result;
            result.push_back(((this->IsTerminalAttributeOn(TerminalAttributes::ExtendedAscii)) ? 
                    ((Char < 255 && Char > 127) ? ASCIIToUTF8Chars[Char] : Char)
                    : Char));
                return result;
        }
        wstring WANSITerminal::_translate(const wstring String) {
            wstring result;
            for (wchar_t character : String) {
                result.append(this->_translate(character));
            }
            return result;
        }
    } // NS:IO

} // NS: Simple

// * It was actually 3bit colour, but that ruined the wordplay.


