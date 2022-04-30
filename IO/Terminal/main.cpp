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
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include<iostream>
#include <string>

#include "Terminal.hpp"

using std::wcout;
using std::endl;
using std::string;
using Simple::IO::Terminal;
using Simple::IO::ASCIIToUTF8Chars;
/*
 * 
 */
int main(int argc, char** argv) {
    // Need to set this so basic IO works!
    std::setlocale(LC_ALL, "en_US.utf8"); 
    // File to open   
    string ansi_file = argv[1];
    // Open the filestream
    std::ifstream ifs(ansi_file);
    // Write the string to stream
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
    // Instantiate Terminal
    
    Terminal console(false,  "");
    console.ClearScreen();
    for (int index = 0; index < 16; index++) {
        for (int offset = 0; offset < 16; offset++) {
            int code = index * 16 + offset;
            console.Print(L"\u001b[38;5;%im%c", code, code);
        }   
    }
    console.SetConsoleColourMode(Simple::IO::TerminalColourModes::Legacy) ;
    console.Print(L'\n');
    for (int backIndex  = 0; backIndex < 16; backIndex++) {
        console.SetBackgroundColour(backIndex);
        for (int foreIndex = 0; foreIndex < 16; foreIndex++)  {
            console.SetForegroundColour(foreIndex);
            console.Print(L"%i\t", foreIndex);
        }
    }
    wcout << endl;
    console.CursorMove(2, Simple::IO::TerminalCursorMovement::ScrollUp);
    // console.SetXY(1,5);
    console.Print(L"Input:");
    for (int index = 0; index < 80; index++) {
        console.Print((wchar_t)196);
    }
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, false);
    console.GetChar(10);
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, true);
    console.CursorMove(8, Simple::IO::TerminalCursorMovement::Up);
    console.Print(L"Input:");
    wstring result = console.GetLine(10);
    console.Print(result);
    int colour = 6;
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, false);
    for (int loops = 0; loops < 10000; loops++) {
        console.SetXY(1,1);
        console.SetForegroundColour(colour);
        console.Print(L"Hello");
        if (colour == 6) {
            colour = 10;
        } else {
            colour = 6;
        }
        usleep(50);
    }
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, true);
   /*
    for (unsigned char ch : content) {
        console.Print((wchar_t)ch);
        usleep(300);
    }
    */

}