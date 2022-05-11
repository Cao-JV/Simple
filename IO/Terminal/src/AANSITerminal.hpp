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
#ifndef AANSITERMINAL_HPP
#define AANSITERMINAL_HPP
    #include <stdlib.h>
    #include <string>
    #include <stdio.h>
    #include <iostream>
    #include <chrono>
    #include <stdarg.h>
    #include "ATerminal.hpp"
    #include "TerminalInfo.hpp"
    #ifdef __linux__
        #include <termios.h>
        #include <sys/ioctl.h> 
        #include <unistd.h> 
    #endif
    using namespace std;
    using std::chrono::steady_clock;

    namespace Simple {
        namespace IO {
            template<typename Character> struct SelectOutput;

            template<> struct SelectOutput<char> { static std::ostream &Output; };
            std::ostream &SelectOutput<char>::Output = std::cout;

            template<> struct SelectOutput<wchar_t> { static std::wostream &Output; };
            std::wostream &SelectOutput<wchar_t>::Output = std::wcout;

            template <typename CharType = wchar_t, typename StringType = wstring>
            class AANSITerminal : ATerminal <CharType, StringType> {
                public:
                AANSITerminal(bool EchoOn, std::string SystemLocale) {
                    std::locale::global(std::locale(SystemLocale));
                    this->_initialize(EchoOn);
                }
                virtual ~AANSITerminal(){
                    #ifdef __linux__
                    // Reset AANSITerminal<class CharType, class StringType> I/O settings to original state before intercept
                    tcsetattr(0, TCSANOW, &this->m_OriginalTerminal);            
                    #endif
                }
                virtual void ClearScreen() {
                    this->_sendCommand('J', TerminalClear::Entire);
                }
                virtual void ClearLine() {
                    this->_sendCommand('K', TerminalClear::ToEnd);
                }
                virtual void FlushOut() {
                    this->Output << endl;
                }
                virtual void Print(const CharType Char) {
                    this->Output << this->_translate(Char);
                }
                virtual void Print(const CharType *Format, ...) {
                    va_list args;
                    va_start(args, Format);
                    this->VPrint(Format, args);
                    va_end(args);
                }
                virtual void Print(const StringType Format, ...) {
                    va_list args;
                    va_start(args, Format);
                    this->VPrint(Format, args);
                    va_end(args);
                }
                virtual void VPrint(const StringType Format, va_list Args) {
                    // We're going to call this over & over (& over) again in our app. Let's just hold on to the memory.
                    static unsigned int i; // This is going to parse our ints
                    static StringType s;     // "     " "     "  "     "   strings
                    static CharType formatOutput;
                    
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
                                            this->Output << this->_translate(i);
                                            break; 
                                case 's': s = va_arg(Args,wchar_t *);
                                            this->Output << this->_translate(s);
                                            break;
                                case 'x': i = va_arg(Args,unsigned int);
                                            this->Output << std::hex << i << std::dec; 

                                            break; 
                                case 'o': i = va_arg(Args,unsigned int);
                                            this->Output << std::oct << i << std::dec;
                                            break; 

                                case 'i' : i = va_arg(Args,int);
                                            this->Output << i;
                                            break; 
                                // ..it won't be left dangling if there were no more wchars
                                default:    this->Output << this->_translate(formatOutput);
                                            break;


                            } 
                        } else {
                            if (formatIndex < Format.length()) 
                            this->Output << this->_translate(formatOutput);
                        } 
                    }
                    va_end(Args); 
                }
                virtual void PrintLn(const CharType *Format, ...) {
                    va_list args; 
                
                    va_start(args, Format);
                    this->Print(Format, args);
                    va_end(args);
                    this->Output << (CharType)'\n';
                }
                virtual void PrintLn(const StringType Format, ...) {
                    va_list args; 
                
                    va_start(args, Format);
                    this->Print(Format, args);
                    va_end(args);
                    this->Output << (CharType)'\n';
                }
                virtual CharType  GetChar(const int TimeOutMS = 0) {
                    CharType result = {0};
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
                virtual StringType GetLine(const int MaxLength = 0, const CharType Terminator = '\n', const int TimeOutMS = 0) {
                    StringType result = { 0 };
                    CharType keypress = { 0 };
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
                virtual void GetMaxXY(int &X, int &Y) {
                    #ifdef __linux__
                    struct winsize result;
                    // Not standard POSIX - Should use Linux, anyway.
                    ioctl(STDOUT_FILENO, TIOCGWINSZ, &result);
                    
                    X = result.ws_col;
                    Y = result.ws_row;
                    #endif
                }
                virtual void GetXY(int &X, int &Y) {
                    #ifdef __linux__
                    // Soo... apparently Linux isn't advanced enough to just have a function... You need to talk to the terminal. If it supports being talked to.
                    wstring result;
                    int semiColonIndex = 0
                        ,startingIndex = 2
                        ,endingIndex = 1;

                    this->_sendCommand((CharType)'n', 6);
                    result = this->GetLine(0, (CharType)'R');

                    semiColonIndex = result.find_first_of(L';');
                    endingIndex = result.find_first_of(L'R') - 1;
                    X = std::stoi(result.substr(startingIndex, semiColonIndex - startingIndex));
                    Y = std::stoi(result.substr(semiColonIndex + 1, endingIndex - (semiColonIndex + 1)));
                    #endif
                }
                virtual void SetMaxXY(const int X, const int Y) {
                    StringType commandData = "8;";
                    commandData.append(std::to_string(Y));
                    commandData.push_back((CharType)';');
                    commandData.append(std::to_string(X));
                    this->_sendCommand((CharType)'t', commandData);
                    // If we broke the upper physical boundaries, this could be different than specified
                    this->GetMaxXY(this->m_MaxX, this->m_MaxY);
                }
                virtual void SetXY(const int X, const int Y, const bool AsEdit = true) {
                    // AANSITerminal<class CharType, class StringType> may have been resized... Will add a signal handler, maybe.
                    this->GetMaxXY(this->m_MaxX, this->m_MaxY);
                    this->m_CurrentX = (X > this->m_MaxX ? this->m_MaxX : 
                                    (X > 0 ? X : 1));
                    this->m_CurrentY = (Y > this->m_MaxY ? this->m_MaxY : 
                                    (Y > 0 ? Y : 1));
                    this->_sendCommand((AsEdit ? 'H' : 'f'), std::to_string(this->m_CurrentY) + ";" + std::to_string(this->m_CurrentX));
                }
                virtual void CursorMove(const int Value, const TerminalCursorMovement Movement) {
                        this->_sendCommand((char)Movement, Value);
                }
                virtual void SaveXY() {
                    // keeping track manually - will come in handy
                    this->GetXY(this->m_SavedX, this->m_SavedY);
                    // ANSI command to save current position
                    this->_sendCommand('s', "");
                }
                virtual void RestoreXY() {
                        // Keeping track manually - will come in handy
                    this->m_CurrentX = this->m_SavedX;
                    this->m_CurrentY = this->m_SavedY;
                    // ANSI command to return to saved position
                    this->_sendCommand('u', "");
                }
                virtual void SetForegroundColour(const int ForegroundColour) {
                    switch (this->m_ColourMode) {
                        case TerminalColourModes::Modern: {
                                        // Modern terminals can support 256 (8bit) colours. starting at 0 & counting up. Like a normal system.
                                        // However, the original spec had already broke the colours into 8-index pages (see below). So this choice of commands seems arbitrary &
                                        // unintuitive. I've written this in C++, let that sink in.
                                        this->_sendCommand('m', "0;38;5;" + std::to_string(ForegroundColour));
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
                virtual void SetBackgroundColour(const int BackgroundColour) {
                    // We could merge Fore & Back colours together for clever algorithmicness. I'd rather keep this readable & straight forward. So, I'm not clever.
                    switch (this->m_ColourMode) {
                        case TerminalColourModes::Modern: {
                                        // Modern terminals can support 256 (8bit) colours. starting at 0 & counting up. Like a normal system.
                                        // However, the original spec had already broke the colours into 8-index pages (see below). So this choice of commands seems arbitrary &
                                        // unintuitive. I've written this in C++, let that sink in.
                                        this->_sendCommand('m', "0;48;5;" + std::to_string(BackgroundColour));
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
                virtual void SetTerminalAttribute(const TerminalAttributes Attribute, bool State) {
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
                virtual void SetConsoleColourMode(const TerminalColourModes Mode) {
                    this->m_ColourMode = Mode;
                }
                virtual TerminalColourModes GetConsoleColourMode() {
                    return this->m_ColourMode;
                }
                virtual bool IsTerminalAttributeOn(const TerminalAttributes Attribute) {
                    return (this->m_TerminalAttributes & Attribute) == Attribute;

                }
            protected:
                int                  m_SavedX
                                    ,m_SavedY
                                    ,m_CurrentX
                                    ,m_CurrentY
                                    ,m_MaxX
                                    ,m_MaxY
                                    ,m_ForegroundColour   = 7
                                    ,m_BackgroundColour   = 0;

                #ifdef __linux__
                struct termios       m_OriginalTerminal
                                    ,m_CurrentTerminal;
                #endif
                const CharType      *m_EscapeSequenceBegin = (char *)"\u001b[";

                TerminalColourModes          m_ColourMode         = TerminalColourModes::Modern;
                TerminalAttributes           m_TerminalAttributes = TerminalAttributes::Echo | TerminalAttributes::ExtendedAscii;
                std::basic_ostream<CharType> &Output              = SelectOutput<CharType>::Output;
                virtual void _initialize(bool EchoOn) {
                    this->_loadTerminalSettings();
                    this->_updateTerminalSettings(TerminalAttributes::Echo, EchoOn, false);
                    this->_updateTerminalSettings(TerminalAttributes::LineBuffer, false);
                    this->ClearScreen();
                    this->_sendCommand('m', 0);
                    this->SetXY(1,1);
                    this->SetForegroundColour(this->m_ForegroundColour);
                    this->SetBackgroundColour(this->m_BackgroundColour);
                }
                virtual void _updateTerminalSettings(TerminalAttributes Attribute, bool State, bool WriteSettingsNow = true) {
                    #ifdef __linux__
                        switch (Attribute) {
                            // If configured for Echo...
                            case TerminalAttributes::Echo: if (State) {
                                                                // ...Turn it on in the AANSITerminal<class CharType, class StringType>
                                                                this->m_CurrentTerminal.c_lflag |= ECHO;
                                                            } else {
                                                                // ...Or, turn it off in AANSITerminal<class CharType, class StringType>
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
                            // Update the settings to AANSITerminal<class CharType, class StringType>
                            tcsetattr(fileno(stdin), TCSANOW, &this->m_CurrentTerminal);
                        }
                    #endif
                }
                virtual void         _loadTerminalSettings() {
                    #ifdef __linux__
                    // Get AANSITerminal<class CharType, class StringType> I/O settings
                    tcgetattr(fileno(stdin), &this->m_OriginalTerminal);
                    // Copy them
                    this->m_CurrentTerminal = this->m_OriginalTerminal;
                    #endif
                }
                virtual void         _sendCommand(const CharType code, const StringType data) {
                     this->Output << this->m_EscapeSequenceBegin << data << code;
                }
                virtual void         _sendCommand(const CharType code, const int data) {
                     this->Output << this->m_EscapeSequenceBegin << data << code;
                }
                virtual CharType     _translate(const CharType Char)  {
                    return (CharType)((this->IsTerminalAttributeOn(TerminalAttributes::ExtendedAscii)) ? 
                            ((Char < 255 && Char > 127) ? ASCIIToUTF8Chars[Char] : Char)
                            : Char);
                }
                virtual StringType   _translate(const StringType String)  {
                    StringType result;
                    for (CharType character : String) {
                        result.push_back(this->_translate(character));
                    }
                    return result;
                }

            };
        }

    }
#endif /* AANSITERMINAL_HPP */