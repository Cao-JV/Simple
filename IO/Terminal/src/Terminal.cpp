/*
 * Simple Terminal v0.1αß
 *
 * An unsophisticated Terminal class for quick commandline development.
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
#include "Terminal.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
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
        Terminal::Terminal(bool EchoOn, std::string SystemLocale) {
            std::setlocale(LC_ALL, SystemLocale.c_str());
            this->_initialize();
            this->SetMaxXY(80, 25);
            this->_sendCommand('m', L"0");
            this->SetForegroundColour(this->m_ForegroundColour);
            this->SetBackgroundColour(this->m_BackgroundColour);
            this->SetTerminalAttribute(TerminalAttributes::Echo, EchoOn);
        }
        Terminal::~Terminal() {
            #ifdef __linux__
            // Reset Terminal I/O settings to original state before intercept
            tcsetattr(0, TCSANOW, &this->m_OriginalTerminal);            
            #endif
        }
        void Terminal::ClearScreen() {
            this->_sendCommand('J', std::to_wstring(TerminalClear::Entire));
        }
        void Terminal::ClearLine() {
            this->_sendCommand('K', std::to_wstring(TerminalClear::ToEnd));
        }
        void Terminal::Print(const wchar_t Char) {
            // We're letting the internal handlers parse the codes, so check if screen pos changed
            this->GetXY(this->m_CurrentX, this->m_CurrentY);
        }
        void Terminal::Print(const wchar_t *Format, ...) {
            va_list args;
            va_start(args, Format);
            this->VPrint(Format, args);
            va_end(args);
        }
        void Terminal::VPrint(const std::wstring Format, va_list Args) {
            // We're going to call this over & over (& over) again in our app. Let's just hold on to the memory.
            static unsigned int i; // This is going to parse our ints
            static std::wstring s;     // "     " "     "  "     "   strings
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
                                    wcout << this->_translate(_intToString(i,16));
                                    break; 
                        case 'o': i = va_arg(Args,unsigned int);
                                    wcout << this->_translate(_intToString(i,8));
                                    break; 

                        case 'i' : i = va_arg(Args,int);
                                    wcout << i;// _intToString(i,10);
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
        void Terminal::Print(const std::wstring Format, ...) {
            va_list args; 

            va_start(args, Format);
            this->Print(Format.c_str(), args);
            va_end(args);
        }
        void Terminal::PrintLn(const wchar_t *Format, ...) {
            va_list args; 

            va_start(args, Format);
            this->Print(Format, args);
            va_end(args);
            wcout << '\n';
        }
        void Terminal::PrintLn(const std::wstring Format, ...) {
            va_list args; 
            va_start(args, Format);
            this->PrintLn(Format.c_str(), args);
            va_end(args);
            
        }
         int Terminal::GetChar(const int TimeOutMS) {
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
         wstring Terminal::GetLine(const int MaxLength, const wchar_t Terminator, const int TimeOutMS) {
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

         void Terminal::GetMaxXY(int &X, int &Y) {
            struct winsize result;
            // Not standard POSIX - Use Linux, anyway.
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &result);

             X = this->m_MaxX = result.ws_col;
             Y = this->m_MaxY = result.ws_row;
         }
         void Terminal::GetXY(int &X, int &Y) {
             X = 0;
             Y = 0;
         }
         void Terminal::SetMaxXY(const int X, const int Y) {
             this->m_MaxX = X;
             this->m_MaxY = Y;
         }
         void Terminal::CursorMove(const int Value, const TerminalCursorMovement Movement) {

             this->_sendCommand((char)Movement, std::to_wstring(Value));
         }
         void Terminal::SetXY(const int X, const int Y, const bool AsEdit) {
             this->_sendCommand((AsEdit ? 'H' : 'f'), std::to_wstring(Y) + L";" + std::to_wstring(X));
         }

         void Terminal::SaveXY() {}
         void Terminal::RestoreXY() {}
         void Terminal::SetForegroundColour(const int ForegroundColour) {
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
                                std::wstring colourData;
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
         void Terminal::SetBackgroundColour(const int BackgroundColour) {
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
                                std::wstring colourData = std::to_wstring(newColour);
                                this->_sendCommand('m', colourData);
                        }
                        break;
                case TerminalColourModes::None:
                default: // If there is no Colour mode, don't change colour.
                        break;
             } 
         }
        void Terminal::SetConsoleColourMode(const TerminalColourModes Mode)  {
            this->m_ColourMode = Mode;
        }
        void Terminal::SetTerminalAttribute(const TerminalAttributes Attribute, const bool State) {
            if (this->IsTerminalAttributeOn(Attribute) != State) {
                this->m_TerminalAttributes = ~Attribute;
            }
            if (Attribute == TerminalAttributes::Echo) {
                this->_updateTerminalSettings();
            }
            if (Attribute == TerminalAttributes::Cursor) {
                this->_sendCommand((State ? 'h' : 'l'), L"?25" );
            }
        }
        TerminalColourModes Terminal::GetConsoleColourMode() {
            return this->m_ColourMode;
        }
        bool Terminal::IsTerminalAttributeOn(const TerminalAttributes Attribute) {
            return (this->m_TerminalAttributes & Attribute) == Attribute;
        }

        void Terminal::_initialize() {
            #ifdef __linux__
            // Get Terminal I/O settings
            tcgetattr(0, &this->m_OriginalTerminal);
            // Copy them
            this->m_CurrentTerminal = this->m_OriginalTerminal;
            // Disable Line Buffering for Input
            this->m_CurrentTerminal.c_lflag &= ~ICANON;
            // Update the settings to Terminal
            tcsetattr(0, TCSANOW, &this->m_CurrentTerminal);
            #endif
        }
        #ifdef __linux__
        void Terminal::_updateTerminalSettings() {
            // If configured for Echo...
            if (this->IsTerminalAttributeOn(TerminalAttributes::Echo)) {
                // ...Turn it on in the Terminal
                this->m_CurrentTerminal.c_cflag |= ECHO;
            } else {
                // ...Or, turn it off in Terminal
                this->m_CurrentTerminal.c_cflag &= ~ECHO;
            }
            // Update the settings to Terminal
            tcsetattr(fileno(stdin), TCSANOW, &this->m_CurrentTerminal);
        }
        #endif
        void Terminal::_sendCommand(const char code, const std::wstring data) {
             this->Print(L"%s%s%c", EscapeSequenceBegin.c_str(), data.c_str(), code);
        }
        std::wstring Terminal::_intToString(const unsigned int Value, const int NumberBase) 
        { 
            static wchar_t buffer[33] = { 0 }; 
            static int maxIndex = 32;
            static unsigned int quotient = Value;

            while (quotient != 0) {
                buffer[maxIndex] = this->m_NumberFaces[Value % NumberBase];
                quotient /= NumberBase;
            }

            return buffer; 
        }
        wchar_t Terminal::_translate(const wchar_t Char) {
            return ((this->IsTerminalAttributeOn(TerminalAttributes::ExtendedAscii)) ? 
                    ((Char < 255 && Char > 127) ? ASCIIToUTF8Chars[Char] : Char)
                    : Char);
        }
        std::wstring Terminal::_translate(const std::wstring String) {
            std::wstring result;
            for (wchar_t character : String) {
                result.push_back(this->_translate(character));
            }
            return result;
        }
    } // NS:IO

} // NS: Simple

// * It was actually 3bit colour, but that ruined the wordplay.


