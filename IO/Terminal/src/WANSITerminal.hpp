/*
 * Simple WANSITerminal v0.1αß
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
#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "TerminalInfo.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#ifdef __linux__
    #include <termios.h>
#endif
using std::wstring;
    namespace Simple {
        namespace IO {
            const std::wstring EscapeSequenceBegin = L"\u001b[";

            /**
             * @brief
             *
             */
            class WANSITerminal   {
                public:
                    WANSITerminal(bool EchoOn = true, std::string SystemLocale = "en_US.utf8");
                    ~WANSITerminal();
                    virtual void    ClearScreen();
                    virtual void    ClearLine();
                    virtual void    FlushOut();
                    virtual void    Print(const wchar_t Char);
                    virtual void    Print(const wstring Format, ...);
                    virtual void    Print(const wchar_t *Format, ...);
                    virtual void    VPrint(const wstring Format, va_list Args);
                    virtual void    PrintLn(const wchar_t *Format, ...);
                    virtual void    PrintLn(const wstring Format, ...);
                    virtual int     GetChar(const int TimeOutMS = 0);
                    virtual wstring GetLine(const int MaxLength = 0, const wchar_t Terminator = L'\n', const int TimeOutMS = 0);
                    virtual void    GetMaxXY(int &X, int &Y);
                    virtual void    GetXY(int &X, int &Y);
                    virtual void    SetMaxXY(const int X, const int Y);
                    virtual void    SetXY(const int X, const int Y, const bool AsEdit = true);
                    virtual void    CursorMove(const int Value, const TerminalCursorMovement Movement);
                    virtual void    SaveXY();
                    virtual void    RestoreXY();
                    virtual void    SetForegroundColour(const int ForegroundColour);
                    virtual void    SetBackgroundColour(const int BackgroundColour);
                    virtual void    SetConsoleColourMode(const TerminalColourModes Mode);
                    virtual void    SetTerminalAttribute(const TerminalAttributes Attribute, bool State);
                    virtual TerminalColourModes GetConsoleColourMode();
                    virtual bool    IsTerminalAttributeOn(const TerminalAttributes Attribute);

                protected:
                    #ifdef __linux__
                        struct termios  m_OriginalTerminal
                                       ,m_CurrentTerminal;
                    #endif
                    int                  m_SavedX
                                        ,m_SavedY
                                        ,m_CurrentX
                                        ,m_CurrentY
                                        ,m_MaxX
                                        ,m_MaxY
                                        ,m_ForegroundColour   = 7
                                        ,m_BackgroundColour   = 0;
                    TerminalColourModes  m_ColourMode        = TerminalColourModes::Modern;
                    TerminalAttributes   m_TerminalAttributes = TerminalAttributes::Echo | TerminalAttributes::ExtendedAscii;
                    virtual void _initialize(bool EchoOn);
                    virtual void _updateTerminalSettings(TerminalAttributes Attribute, bool State, bool WriteSettingsNow = true);
                    virtual void _loadTerminalSettings();
                    virtual void _sendCommand(const char code, const std::wstring data);
                    virtual wchar_t _translate(const wchar_t Char);
                    virtual std::wstring _translate(const std::wstring);

                    const std::wstring   m_NumberFaces        = L"0123456789ABCDEF";
            };
        }
    }
#endif // TERMINAL_HPP