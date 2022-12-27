/*
 * Simple ANSI Terminal v0.1αß
 *
 * An unsophisticated Terminal class for quick commandline development.
 * This Is the standard terminal UTF8 version - using non-wide characters.
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
#include "AStdTerminal.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#ifdef __linux__
    #include <termios.h>
#endif
using std::string;
    namespace Simple {
        namespace IO {

            /**
             * @brief
             *
             */
            class ANSITerminal : AStdTerminal<char, string>  {
                public:
                    ANSITerminal(bool EchoOn = true, std::string SystemLocale = "en_US.utf8");
                    ~ANSITerminal();
                    virtual void    ClearScreen();
                    virtual void    ClearLine();
                    virtual void    FlushOut();
                    virtual void    Print(const char Char);
                    virtual void    Print(const string Format, ...);
                    virtual void    Print(const char *Format, ...);
                    virtual void    VPrint(const string Format, va_list Args);
                    virtual void    PrintLn(const char *Format, ...);
                    virtual void    PrintLn(const string Format, ...);
                    virtual int     GetChar(const int TimeOutMS = 0);
                    virtual string GetLine(const char Terminator = '\n', const int MaxLength = 0,  const int TimeOutMS = 0);
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
                    const std::string EscapeSequenceBegin = "\u001b[";
                    #ifdef __linux__
                        struct termios  m_OriginalTerminal
                                       ,m_CurrentTerminal;
                    #endif
                    virtual void _initialize(bool EchoOn);
                    virtual void _updateTerminalSettings(TerminalAttributes Attribute, bool State, bool WriteSettingsNow = true);
                    virtual void _loadTerminalSettings();
                    virtual void _sendCommand(const char code, const std::string data);
                    virtual std::string _translate(const char Char);
                    virtual std::string _translate(const std::string);
            };
        }
    }
#endif // TERMINAL_HPP