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

#include <filesystem>

namespace fs = std::filesystem;

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
        template <class CharType>
        class ALogger {
            public:
                using LogString = std::basic_string<CharType>;
                ALogger(const LogString FileName)  {
                    this->SetLogFileName(FileName);
                }
                ~ALogger() = default;
                virtual void Write(const LogString Message, LogLevel Level);
                virtual void Write(const LogString Message) {
                    this->Write(Message, this->_LogLevelDefault);
                }
                virtual void SetLogFileLocation(const LogString FileName) {
                    this->SetLogFileName(FileName);
                }
                virtual void SetLogFileName(const LogString FileName)  {
                    fs::path filePath(FileName);
                    if (fs::is_directory(filePath.parent_path())) {
                        // Nothing to see here. Just easier to read positives
                    } else {
                        fs::create_directory(filePath.parent_path());
                    }
                    this->_FilePath = filePath;
                }
                virtual void SetUseDateInFileName(const bool Yes) {
                    this->_UseDateInFileName = Yes;
                }
                virtual LogString GetLogFileLocation();
                virtual LogString GetLogDirectoryName();
                virtual LogString GetLogFileName();
                virtual bool UsingDateInFileName() {
                    return this->_UseDateInFileName;
                }
            protected:
                fs::path      _FilePath;
                LogLevel      _LogLevelMinimum = LogLevel::Debug
                             ,_LogLevelDefault = LogLevel::Info;
                bool          _UseDateInFileName = true;

                virtual tm _GetTimeStamp() {
                    auto timePointNow = std::chrono::system_clock::now();
                    std::time_t secondsFromEpochNow = std::chrono::system_clock::to_time_t(timePointNow);
                    tm result = *std::localtime(&secondsFromEpochNow);
                    return result;
                }
                
        };
    


    } // NS: IO
} // NS: Simple
#endif // ALOGGER_HPP