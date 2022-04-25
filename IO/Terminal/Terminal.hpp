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
#ifndef TERMINAL_HPP
#define TERMINAL_HPP
    #include "ATerminal.hpp"
#ifdef __linux__
    #include <termios.h>
#endif
    namespace Simple {
        namespace IO {
            const std::string EscapeSequenceBegin = "\u001b[";

            /**
             * @brief 
             * 
             */
            class Terminal : ATerminal  {
                 public:
                Terminal(bool EchoOn = true, std::string SystemLocale = "en_US.utf8");
                ~Terminal();
                virtual void ClearScreen();
                virtual void ClearLine();
                virtual void Print(const wchar_t Char);
                virtual void Print(const std::wstring Format, ...);
                virtual void Print(const wchar_t *Format, ...);
                void VPrint(const std::wstring Format, va_list Args);
                virtual void PrintLn(const wchar_t *Format, ...);
                virtual void PrintLn(const std::wstring Format, ...);
                virtual int  GetChar(const int TimeOutMS = 0);
                virtual void GetMaxXY(int &X, int &Y);
                virtual void GetXY(int &X, int &Y);
                virtual void SetMaxXY(const int X, const int Y);
                virtual void SetXY(const int X, const int Y);
                virtual void SaveXY();
                virtual void RestoreXY();
                virtual void SetForegroundColour(const int ForegroundColour);
                virtual void SetBackgroundColour(const int BackgroundColour);
                virtual void SetConsoleColourMode(TerminalColourMode Mode);
                virtual void SetBlink(bool Blink);
                virtual void SetEcho(bool Echo);
                virtual void SetExtendedASCII(bool ExtendedASCII);
                virtual bool IsBlinkOn();
                virtual bool IsEchoOn();
                virtual bool IsExtendedASCIIOn();
                virtual TerminalColourMode GetConsoleColourMode();

                protected:
                    #ifdef __linux__
                        struct termios m_OriginalTerminal
                                        ,m_CurrentTerminal;
                        void UpdateTerminalSettings();
                    #endif
                    virtual void Initialize();
                    virtual void SendCommand(const char code, const std::wstring data);
                    virtual wchar_t Translate(const wchar_t Char);
                    virtual std::wstring Translate(const std::wstring);
                    std::wstring IntToString(unsigned int Value, int NumberBase);
                    const std::wstring   m_NumberFaces        = L"0123456789ABCDEF";
            };
        }
    }
#endif // TERMINAL_HPP