/*
 * Simple Logger v0.1αß
 *
 * An unsophisticated Logger base class for quick commandline development.
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
#ifndef ALOGGER_HPP
#define ALOGGER_HPP
#include <stdio.h>
#include <iostream>
namespace Simple {
    namespace IO {
        enum LogLevel  {
             Trace   = 100
            ,Debug   = 200
            ,Info    = 300
            ,Warning = 400
            ,Error   = 500
            ,Fatal   = 600
        };

        template<typename T> struct OutputSelector;

        template<> struct OutputSelector<char> { static std::ostream &OutStream; };
        std::ostream &OutputSelector<char>::OutStream = std::cout;

        template<> struct OutputSelector<wchar_t> { static std::wostream &OutStream; };
        std::wostream &OutputSelector<wchar_t>::OutStream = std::wcout;


        template <typename CharType, class StringType>
        class ALogger {
            public:
                ALogger() = default;
                ~ALogger() = default;
                virtual void Write(StringType Message, LogLevel Level) = 0;
                virtual void Write(StringType Message) = 0;
                virtual StringType GetLogFileName() {
                    return this->m_LogFileName;
                }
                virtual bool IsFileNameDate() {
                    return this->IsFileNameDate();
                }
                virtual void SetLogFileInfo(const StringType DirectoryName, const StringType FileName) {
                    this->_LogFileName = FileName;
                    this->_LogDirectoryName = DirectoryName;
                    return &this;
                }
                virtual void SetLogFileInfo(const bool Yes) {
                    this->_IsFileNameDate = Yes;
                }
            protected:
                StringType   _LogDirectoryName
                            ,_LogFileName;
                LogLevel     _LogLevelDefault = LogLevel::Info;
                bool         _IsFileNameDate = true;
                std::basic_ostream<CharType> &_Output = OutputSelector<CharType>::OutStream;
                
        };
    }
}
#endif // ALOGGER_HPP