/*
 * Simple Logger v0.1αß
 *
 * An unsophisticated Unicode Logger class for quick commandline development.
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
#ifndef WLOGGER_HPP
#define WLOGGER_HPP
#include <string>
#include "ALogger.hpp"

using std::wstring;
namespace Simple {
    namespace IO {

        class WLogger : public ALogger<wchar_t> {
            public:
                WLogger(const std::basic_string<wchar_t> FileName);
                ~WLogger();
        };
        
    } // NS: IO
} // NS: Simple
#endif // WLOGGER_HPP