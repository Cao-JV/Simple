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
    int x = 0
       ,y = 0;
    // File to open   
    //string ansi_file = argv[1];
    // Open the filestream
    //std::ifstream ifs(ansi_file);
    // Write the string to stream
    //std::string content( (std::istreambuf_iterator<char>(ifs) ),
    //                     (std::istreambuf_iterator<char>()    ) );
    // Instantiate Terminal
    
    Terminal console(false,  "");
    console.ClearScreen();
    console.SetXY(1,1);
    console.SetForegroundColour(7);
    console.SetBackgroundColour(0);
    console.SetMaxXY(200, 80);
    console.Print(L"Welcome to SimpleConsole...\nTerminal set to 100 columns by 80 rows\n");
    console.Print(L"Extended (8bit)ANSI/Extended (8bit)ASCII Test:\n");
    console.Print(L"Foreground:\n");
    for (int index = 0; index < 16; index++) {
        for (int offset = 0; offset < 16; offset++) {
            int code = index * 16 + offset;
            console.Print(L"\u001b[38;5;%im%c ", code, code);
        }   
    }
    console.Print(L"\nPress a key to continue...");
    console.GetChar();
    console.Print(L"Background:\n");
    for (int index = 0; index < 16; index++) {
        for (int offset = 0; offset < 16; offset++) {
            int code = index * 16 + offset;
            console.Print(L"\u001b[48;5;%im%c ", code, code);
        }   
    }
    console.SetForegroundColour(7);
    console.SetBackgroundColour(0);
    console.Print(L"\nPress a key to continue...");
    console.GetChar();
    console.Print(L"\nLegacy ANSI (3bit)\n");
    console.SetConsoleColourMode(Simple::IO::TerminalColourModes::Legacy) ;
    console.Print(L"Foreground\n");
    for (int foreIndex = 0; foreIndex < 16; foreIndex++)  {
        console.SetForegroundColour(foreIndex);
        if (foreIndex < 10) { console.Print(L' '); }
        console.Print(L"%i ", foreIndex);
    }
    console.SetForegroundColour(7);
    console.SetBackgroundColour(0);
    console.Print(L"\nPress a key to continue...");
    console.GetChar();
    console.Print(L"\nBackground:\n");
    for (int backIndex  = 0; backIndex < 16; backIndex++) {
        console.SetBackgroundColour(backIndex);
        if (backIndex < 10) { console.Print(L' '); }
        console.Print(L"%i ", backIndex);
    }
    console.SetForegroundColour(7);
    console.SetBackgroundColour(0);
    console.Print(L"\nPress a key to continue...");
    console.GetChar();
    wcout << endl;
    console.GetMaxXY(x, y);
    console.Print(L"Your Terminal is %i columns by %i rows\n", x,y);
    console.Print(L"\nPress a key to continue...");
    console.GetChar();
    console.CursorMove(5, Simple::IO::TerminalCursorMovement::Right);
    console.Print(L"Cursor has been moved right 5\nInput 1 Char (No cursor):");
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, false);
    console.GetChar(10);
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, true);
    console.CursorMove(8, Simple::IO::TerminalCursorMovement::Up);
    console.Print(L"Cursor has been moved up 8\nInput String 10 chars, enter terminated (Cursor):");
    wstring result = console.GetLine(10);
    console.Print(L"\nYou said %s!", result.c_str());
    int colour = 6;
    console.SetXY(1,1);
    console.Print(L"Looping colour test...\n");
    console.SetTerminalAttribute(Simple::IO::TerminalAttributes::Cursor, false);
    for (int loops = 0; loops < 10000; loops++) {
        console.SetXY(1,2);
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
    console.SetXY(1, 24);
    console.Print(L"Setting Console to 80 columns by 25 rows");
    //  console.SetMaxXY(80, 25);
    console.Print(L"Hex: %x", 28);
    console.GetXY(x, y);
    console.Print(L"\n[%i, %i]GoodBye!\n", x, y);
   /*
    for (unsigned char ch : content) {
        console.Print((wchar_t)ch);
        usleep(300);
    }
    */

}