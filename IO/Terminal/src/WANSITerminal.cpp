/*
 * Simple WANSITerminal v0.1αß
 *
 * An unsophisticated WANSITerminal class for quick commandline development.
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
#include "WANSITerminal.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <chrono>


#ifdef __linux__
    #include <sys/ioctl.h> 
    #include <unistd.h> 
#endif


namespace Simple {
    namespace IO {
        WANSITerminal::WANSITerminal(bool EchoOn, std::string SystemLocale) : AANSITerminal<wchar_t, std::wstring>::AANSITerminal(EchoOn, SystemLocale) {
        }
        WANSITerminal::~WANSITerminal() {
            
        }
    } // NS:IO

} // NS: Simple



