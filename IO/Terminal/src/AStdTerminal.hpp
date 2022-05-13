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
#ifndef ATERMINAL_HPP
#define ATERMINAL_HPP
    #include <stdlib.h>
    #include <string>
    #include "TerminalInfo.hpp"

    namespace Simple {
        namespace IO {
             template <typename CharType, typename StringType>
             class AStdTerminal {
                 public:
                    AStdTerminal() = default;
                    virtual ~AStdTerminal() = default;
                    virtual void ClearScreen() = 0;
                    virtual void ClearLine()   = 0;
                    virtual void FlushOut()    = 0;
                    virtual void Print(const CharType Char) = 0;
                    virtual void Print(const StringType Format, ...) = 0;
                    virtual void Print(const CharType *Format, ...) = 0;
                    void VPrint(const StringType Format, va_list Args);
                    virtual void PrintLn(const CharType *Format, ...) =0;
                    virtual void PrintLn(const StringType Format, ...) = 0;
                    virtual int  GetChar(const int TimeOutMS = 0) = 0;
                    virtual StringType GetLine(const CharType Terminator, const int MaxLength = 0, const int TimeOutMS = 0) = 0;
                    virtual void GetMaxXY(int &X, int &Y) = 0;
                    virtual void GetXY(int &X, int &Y) = 0;
                    virtual void SetMaxXY(const int X, const int Y) = 0;
                    virtual void SetXY(const int X, const int Y, const bool AsEdit = true) = 0;
                    virtual void CursorMove(const int Value, const TerminalCursorMovement Movement) = 0;
                    virtual void SaveXY() = 0;
                    virtual void RestoreXY() = 0;
                    virtual void SetForegroundColour(const int ForegroundColour) = 0;
                    virtual void SetBackgroundColour(const int BackgroundColour) = 0;
                    virtual void SetTerminalAttribute(const TerminalAttributes Attribute, bool State) = 0;
                    virtual void SetConsoleColourMode(const TerminalColourModes Mode) = 0;
                    virtual TerminalColourModes GetConsoleColourMode() = 0;
                    virtual bool IsTerminalAttributeOn(const TerminalAttributes Attribute) = 0;
                protected:
                    const StringType EscapeSequenceBegin;
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
                    virtual void         _initialize(bool EchoOn) = 0;
                    virtual void         _updateTerminalSettings(TerminalAttributes Attribute, bool State, bool WriteSettingsNow = true) = 0;
                    virtual void         _loadTerminalSettings() = 0;
                    virtual StringType   _translate(const CharType Char) = 0;
                    virtual StringType   _translate(const StringType) = 0;
            };
        }

    }
#endif /* ATERMINAL_HPP */