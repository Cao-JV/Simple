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
            
             class ATerminal {
                 public:
                    ATerminal();
                    virtual ~ATerminal();
                    virtual void ClearScreen() = 0;
                    virtual void ClearLine() = 0;
                    virtual void Print(const wchar_t Char) = 0;
                    virtual void Print(const std::wstring Format, ...) = 0;
                    virtual void Print(const wchar_t *Format, ...) = 0;
                    void VPrint(const std::wstring Format, va_list Args);
                    virtual void PrintLn(const wchar_t *Format, ...) =0;
                    virtual void PrintLn(const std::wstring Format, ...) = 0;
                    virtual int  GetChar(const int TimeOutMS = 0) = 0;
                    virtual void GetMaxXY(int &X, int &Y) = 0;
                    virtual void GetXY(int &X, int &Y) = 0;
                    virtual void SetMaxXY(const int X, const int Y) = 0;
                    virtual void SetXY(const int X, const int Y) = 0;
                    virtual void SaveXY() = 0;
                    virtual void RestoreXY() = 0;
                    virtual void SetForegroundColour(const int ForegroundColour) = 0;
                    virtual void SetBackgroundColour(const int BackgroundColour) = 0;
                    virtual void SetBlink(bool Blink) = 0;
                    virtual void SetEcho(bool Echo) = 0;
                    virtual bool IsBlinkOn() = 0;
                    virtual bool IsEchoOn() = 0;
                    virtual bool IsExtendedASCIIOn() = 0;
                    virtual TerminalColourMode GetConsoleColourMode() = 0;
                    virtual void SetConsoleColourMode(const TerminalColourMode Mode) = 0;
                protected:
                    int                  m_SavedX
                                        ,m_SavedY
                                        ,m_CurrentX
                                        ,m_CurrentY
                                        ,m_MaxX
                                        ,m_MaxY
                                        ,m_ForegroundColour
                                        ,m_BackgroundColour;
                    bool                 m_IsExtendedASCIIOn= true
                                        ,m_IsBlinkOn        = false
                                        ,m_IsEchoOn         = false;
                    TerminalColourMode    m_ColourMode       = Modern;
                    virtual void Initialize() = 0;
                    virtual wchar_t Translate(const wchar_t Char) = 0;
                    virtual std::wstring Translate(const std::wstring) = 0;
            };
        }

    }
#endif /* ATERMINAL_HPP */