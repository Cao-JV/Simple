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
#ifndef TERMINALINFO_HPP
#define TERMINALINFO_HPP

namespace Simple {
  namespace IO {
    /**
     * @brief Used to Clear a scoped area (Screen or Line) data
     */
    enum TerminalClear {
        /**
         * @brief Clears from current location to the End of the requested scope
         */
          ToEnd = 0
          /**
          * @brief Clears from current location to the Start of the requested scope
          */
        ,ToBegin = 1
        /**
         * @brief Clears the entire requested scope
         */
        ,Entire = 2
    };

    /**
     * @brief Standard oldschool terminal colour list to standardize - use with colour changing methods....
     * @todo Make a modern list as well
     */
    enum LegacyTerminalColours  {
         Black      = 0
        ,Navy       = 1
        ,DarkGreen  = 2
        ,Teal       = 3
        ,Red        = 4
        ,Purple     = 5
        ,Brown      = 6
        ,LiteGrey   = 7
        ,DarkGrey   = 8
        ,Blue       = 9
        ,Chartreuse = 10
        ,Aqua       = 11
        ,Pink       = 12
        ,Magenta    = 13
        ,Yellow     = 14
        ,White      = 15
    };

     enum TerminalColourMode {
       Modern = 10
      ,Legacy = 100
      ,None   = 0
    };
    /**
     * @brief Array of Unicode characters, using index to map the original ASCII & Extended ASCII
     * @todo replace with something that doesn't require occupying 128 bytes it doesn't need
     */
    static const wchar_t ASCIIToUTF8Chars[256] = {
    /**
     * @brief  0 - NULL
     */
    0x0000
    /**
      * @brief 1 - Start Heading
      */
    ,0x0001
    /**
     * @brief  2 - Start Text
     */
    ,0x0002
    /**
    * @brief   3 - START OF TEXT
    */
    ,0x0003
    /**
    * @brief   4 - END OF TEXT
    */
    ,0x0004
    /**
    * @brief   5 - END OF TRANSMISSION
    */
    ,0x0005
    /**
    * @brief   6 - ENQUIRY
    */
    ,0x0006
    /**
    * @brief   7 - ACKNOWLEDGE
    */
    ,0x0007
    /**
    * @brief   8 - BELL
    */
    ,0x0008
    /**
    * @brief   9 - BACKSPACE
    */
    ,0x0009
    /**
    * @brief   10 - HORIZONTAL TABULATION
    */
    ,0x000a
    /**
    * @brief   11 - LINE FEED
    */
    ,0x000b
    /**
    * @brief   12 - VERTICAL TABULATION
    */
    ,0x000c
    /**
    * @brief   13 - FORM FEED
    */
    ,0x000d
    /**
    * @brief   14 - CARRIAGE RETURN
    */
    ,0x000e
    /**
    * @brief   15 - SHIFT OUT
    */
    ,0x000f
    /**
    * @brief   16 - SHIFT IN
    */
    ,0x0010
    /**
    * @brief   17 - DATA LINK ESCAPE
    */
    ,0x0011
    /**
    * @brief   18 - DEVICE CONTROL ONE
    */
    ,0x0012
    /**
    * @brief   19 - DEVICE CONTROL TWO
    */
    ,0x0013
    /**
    * @brief   20 - DEVICE CONTROL THREE
    */
    ,0x0014
    /**
    * @brief   21 - DEVICE CONTROL FOUR
    */
    ,0x0015
    /**
    * @brief   22 - NEGATIVE ACKNOWLEDGE
    */
    ,0x0016
    /**
    * @brief   23 - SYNCHRONOUS IDLE
    */
    ,0x0017
    /**
    * @brief   24- END OF TRANSMISSION BLOCK
    */
    ,0x0018
    /**
    * @brief   25 - CANCEL
    */
    ,0x0019
    /**
    * @brief   26 - END OF MEDIUM
    */
    ,0x001a
    /**
    * @brief   27 - SUBSTITUTE
    */
    ,0x001b
    /**
    * @brief   28 - ESCAPE
    */
    ,0x001c
    /**
    * @brief   29 - FILE SEPARATOR
    */
    ,0x001d
    /**
    * @brief   30 - GROUP SEPARATOR
    */
    ,0x001e
    /**
    * @brief   31 - RECORD SEPARATOR
    */
    ,0x001f
    /**
    * @brief   32 - UNIT SEPARATOR
    */
    ,0x0020
    /**
    * @brief   33 - SPACE
    */
    ,0x0021
    /**
    * @brief   34 - EXCLAMATION MARK
    */
    ,0x0022
    /**
    * @brief   35 - QUOTATION MARK
    */
    ,0x0023
    /**
    * @brief   36 - NUMBER SIGN
    */
    /**
    * @brief   37 - DOLLAR SIGN
    */
    ,0x0024
    /**
    * @brief   38 - PERCENT SIGN
    */
    ,0x0025
    /**
    * @brief   39 - AMPERSAND
    */
    ,0x0026
    /**
    * @brief   40 - APOSTROPHE
    */
    ,0x0027
    /**
    * @brief   41 - LEFT PARENTHESIS
    */
    ,0x0028
    /**
    * @brief   42 - RIGHT PARENTHESIS
    */
    ,0x0029
    /**
    * @brief   43 - ASTERISK
    */
    ,0x002a
    /**
    * @brief   44 - PLUS SIGN
    */
    ,0x002b
    /**
    * @brief   45 - COMMA
    */
    ,0x002c
    /**
    * @brief   46 - HYPHEN-MINUS
    */
    ,0x002d
    /**
    * @brief   47 - FULL STOP
    */
    ,0x002e
    /**
    * @brief   48 - SOLIDUS
    */
    ,0x002f
    /**
    * @brief   49 - DIGIT ZERO
    */
    ,0x0030
    /**
    * @brief   50 - DIGIT ONE
    */
    ,0x0031
    /**
    * @brief   51 - DIGIT TWO
    */
    ,0x0032
    /**
    * @brief   52 - DIGIT THREE
    */
    ,0x0033
    /**
    * @brief   53 - DIGIT FOUR
    */
    ,0x0034
    /**
    * @brief   54 - DIGIT FIVE
    */
    ,0x0035
    /**
    * @brief   55 - DIGIT SIX
    */
    ,0x0036
    /**
    * @brief   56 - DIGIT SEVEN
    */
    ,0x0037
    /**
    * @brief   57 - DIGIT EIGHT
    */
    ,0x0038
    /**
    * @brief   58 - DIGIT NINE
    */
    ,0x0039
    /**
    * @brief   59 - COLON
    */
    ,0x003a
    /**
    * @brief   60 - SEMICOLON
    */
    ,0x003b
    /**
    * @brief   61 - LESS-THAN SIGN
    */
    ,0x003c
    /**
    * @brief   62 - EQUALS SIGN
    */
    ,0x003d
    /**
    * @brief   63 - GREATER-THAN SIGN
    */
    ,0x003e
    /**
    * @brief   64 - QUESTION MARK
    */
    ,0x003f
    /**
    * @brief   65 - COMMERCIAL AT
    */
    ,0x0040
    /**
    * @brief   66 - LATIN CAPITAL LETTER A
    */
    ,0x0041
    /**
    * @brief   67 - LATIN CAPITAL LETTER B
    */
    ,0x0042
    /**
    * @brief   68 - LATIN CAPITAL LETTER C
    */
    ,0x0043
    /**
    * @brief   69 - LATIN CAPITAL LETTER D
    */
    ,0x0044
    /**
    * @brief   70 - LATIN CAPITAL LETTER E
    */
    ,0x0045
    /**
    * @brief   71 - LATIN CAPITAL LETTER F
    */
    ,0x0046
    /**
    * @brief   72 - LATIN CAPITAL LETTER G
    */
    ,0x0047
    /**
    * @brief   73 - LATIN CAPITAL LETTER H
    */
    ,0x0048
    /**
    * @brief   74 - LATIN CAPITAL LETTER I
    */
    ,0x0049
    /**
    * @brief   75 - LATIN CAPITAL LETTER J
    */
    ,0x004a
    /**
    * @brief   76 - LATIN CAPITAL LETTER K
    */
    ,0x004b
    /**
    * @brief   77 - LATIN CAPITAL LETTER L
    */
    ,0x004c
    /**
    * @brief   78 - LATIN CAPITAL LETTER M
    */
    ,0x004d
    /**
    * @brief   79 - LATIN CAPITAL LETTER N
    */
    ,0x004e
    /**
    * @brief   80 - LATIN CAPITAL LETTER O
    */
    ,0x004f
    /**
    * @brief   81 - LATIN CAPITAL LETTER P
    */
    ,0x0050
    /**
    * @brief   82 - LATIN CAPITAL LETTER Q
    */
    ,0x0051
    /**
    * @brief   83 - LATIN CAPITAL LETTER R
    */
    ,0x0052
    /**
    * @brief   84 - LATIN CAPITAL LETTER S
    */
    ,0x0053
    /**
    * @brief   85 - LATIN CAPITAL LETTER T
    */
    ,0x0054
    /**
    * @brief   86 - LATIN CAPITAL LETTER U
    */
    ,0x0055
    /**
    * @brief   87 - LATIN CAPITAL LETTER V
    */
    ,0x0056
    /**
    * @brief   88 - LATIN CAPITAL LETTER W
    */
    ,0x0057
    /**
    * @brief   89 - LATIN CAPITAL LETTER X
    */
    ,0x0058
    /**
    * @brief   90 - LATIN CAPITAL LETTER Y
    */
    ,0x0059
    /**
    * @brief   91 - LATIN CAPITAL LETTER Z
    */
    ,0x005a
    /**
    * @brief   92 - LEFT SQUARE BRACKET
    */
    ,0x005b
    /**
    * @brief   93 - REVERSE SOLIDUS
    */
    ,0x005c
    /**
    * @brief   94 - RIGHT SQUARE BRACKET
    */
    ,0x005d
    /**
    * @brief   95 - CIRCUMFLEX ACCENT
    */
    ,0x005e
    /**
    * @brief   96 - LOW LINE
    */
    ,0x005f
    /**
    * @brief   97 - GRAVE ACCENT
    */
    ,0x0060
    /**
    * @brief   - LATIN SMALL LETTER A
    */
    ,0x0061
    /**
    * @brief   - LATIN SMALL LETTER B
    */
    ,0x0062
    /**
    * @brief   - LATIN SMALL LETTER C
    */
    ,0x0063
    /**
    * @brief   - LATIN SMALL LETTER D
    */
    ,0x0064
    /**
    * @brief   - LATIN SMALL LETTER E
    */
    ,0x0065
    /**
    * @brief   - LATIN SMALL LETTER F
    */
    ,0x0066
    /**
    * @brief   - LATIN SMALL LETTER G
    */
    ,0x0067
    /**
    * @brief   - LATIN SMALL LETTER H
    */
    ,0x0068
    /**
    * @brief   - LATIN SMALL LETTER I
    */
    ,0x0069
    /**
    * @brief   - LATIN SMALL LETTER J
    */
    ,0x006a
    /**
    * @brief   - LATIN SMALL LETTER K
    */
    ,0x006b
    /**
    * @brief   - LATIN SMALL LETTER L
    */
    ,0x006c
    /**
    * @brief   - LATIN SMALL LETTER M
    */
    ,0x006d
    /**
    * @brief   - LATIN SMALL LETTER N
    */
    ,0x006e
    /**
    * @brief   - LATIN SMALL LETTER O
    */
    ,0x006f
    /**
    * @brief   - LATIN SMALL LETTER P
    */
    ,0x0070
    /**
    * @brief   - LATIN SMALL LETTER Q
    */
    ,0x0071
    /**
    * @brief   - LATIN SMALL LETTER R
    */
    ,0x0072
    /**
    * @brief   - LATIN SMALL LETTER S
    */
    ,0x0073
    /**
    * @brief   - LATIN SMALL LETTER T
    */
    ,0x0074
    /**
    * @brief   - LATIN SMALL LETTER U
    */
    ,0x0075
    /**
    * @brief   - LATIN SMALL LETTER V
    */
    ,0x0076
    /**
    * @brief   - LATIN SMALL LETTER W
    */
    ,0x0077
    /**
    * @brief   - LATIN SMALL LETTER X
    */
    ,0x0078
    /**
    * @brief   - LATIN SMALL LETTER Y
    */
    ,0x0079
    /**
    * @brief   - LATIN SMALL LETTER Z
    */
    ,0x007a
    /**
    * @brief   - LEFT CURLY BRACKET
    */
    ,0x007b
    /**
    * @brief   - VERTICAL LINE
    */
    ,0x007c
    /**
    * @brief   - RIGHT CURLY BRACKET
    */
    ,0x007d
    /**
    * @brief   - TILDE
    */
    ,0x007e
    /**
    * @brief   - DELETE
    */
    ,0x007f
    /**
    * @brief   - LATIN CAPITAL LETTER C WITH CEDILLA
    */
    ,0x00c7
    /**
    * @brief   - LATIN SMALL LETTER U WITH DIAERESIS
    */
    ,0x00fc
    /**
    * @brief   - LATIN SMALL LETTER E WITH ACUTE
    */
    ,0x00e9
    /**
    * @brief   - LATIN SMALL LETTER A WITH CIRCUMFLEX
    */
    ,0x00e2
    /**
    * @brief   - LATIN SMALL LETTER A WITH DIAERESIS
    */
    ,0x00e4
    /**
    * @brief   - LATIN SMALL LETTER A WITH GRAVE
    */
    ,0x00e0
    /**
    * @brief   - LATIN SMALL LETTER A WITH RING ABOVE
    */
    ,0x00e5
    /**
    * @brief   - LATIN SMALL LETTER C WITH CEDILLA
    */
    ,0x00e7
    /**
    * @brief   - LATIN SMALL LETTER E WITH CIRCUMFLEX
    */
    ,0x00ea
    /**
    * @brief   - LATIN SMALL LETTER E WITH DIAERESIS
    */
    ,0x00eb
    /**
    * @brief   - LATIN SMALL LETTER E WITH GRAVE
    */
    ,0x00e8
    /**
    * @brief   - LATIN SMALL LETTER I WITH DIAERESIS
    */
    ,0x00ef
    /**
    * @brief   - LATIN SMALL LETTER I WITH CIRCUMFLEX
    */
    ,0x00ee
    /**
    * @brief   - LATIN SMALL LETTER I WITH GRAVE
    */
    ,0x00ec
    /**
    * @brief   - LATIN CAPITAL LETTER A WITH DIAERESIS
    */
    ,0x00c4
    /**
    * @brief   - LATIN CAPITAL LETTER A WITH RING ABOVE
    */
    ,0x00c5
    /**
    * @brief   - LATIN CAPITAL LETTER E WITH ACUTE
    */
    ,0x00c9
    /**
    * @brief   - LATIN SMALL LIGATURE AE
    */
    ,0x00e6
    /**
    * @brief   - LATIN CAPITAL LIGATURE AE
    */
    ,0x00c6
    /**
    * @brief   - LATIN SMALL LETTER O WITH CIRCUMFLEX
    */
    ,0x00f4
    /**
    * @brief   - LATIN SMALL LETTER O WITH DIAERESIS
    */
    ,0x00f6
    /**
    * @brief   - LATIN SMALL LETTER O WITH GRAVE
    */
    ,0x00f2
    /**
    * @brief   - LATIN SMALL LETTER U WITH CIRCUMFLEX
    */
    ,0x00fb
    /**
    * @brief   - LATIN SMALL LETTER U WITH GRAVE
    */
    ,0x00f9
    /**
    * @brief   - LATIN SMALL LETTER Y WITH DIAERESIS
    */
    ,0x00ff
    /**
    * @brief   - LATIN CAPITAL LETTER O WITH DIAERESIS
    */
    ,0x00d6
    /**
    * @brief   - LATIN CAPITAL LETTER U WITH DIAERESIS
    */
    ,0x00dc
    /**
    * @brief   - CENT SIGN
    */
    ,0x00a2
    /**
    * @brief   - POUND SIGN
    */
    ,0x00a3
    /**
    * @brief   - YEN SIGN
    */
    ,0x00a5
    /**
    * @brief   - PESETA SIGN
    */
    ,0x20a7
    /**
    * @brief   - LATIN SMALL LETTER F WITH HOOK
    */
    ,0x0192
    /**
    * @brief   - LATIN SMALL LETTER A WITH ACUTE
    */
    ,0x00e1
    /**
    * @brief   - LATIN SMALL LETTER I WITH ACUTE
    */
    ,0x00ed
    /**
    * @brief   - LATIN SMALL LETTER O WITH ACUTE
    */
    ,0x00f3
    /**
    * @brief   - LATIN SMALL LETTER U WITH ACUTE
    */
    ,0x00fa
    /**
    * @brief   - LATIN SMALL LETTER N WITH TILDE
    */
    ,0x00f1
    /**
    * @brief   - LATIN CAPITAL LETTER N WITH TILDE
    */
    ,0x00d1
    /**
    * @brief   - FEMININE ORDINAL INDICATOR
    */
    ,0x00aa
    /**
    * @brief   - MASCULINE ORDINAL INDICATOR
    */
    ,0x00ba
    /**
    * @brief   - INVERTED QUESTION MARK
    */
    ,0x00bf
    /**
    * @brief   - REVERSED NOT SIGN
    */
    ,0x2310
    /**
    * @brief   - NOT SIGN
    */
    ,0x00ac
    /**
    * @brief   - VULGAR FRACTION ONE HALF
    */
    ,0x00bd
    /**
    * @brief   - VULGAR FRACTION ONE QUARTER
    */
    ,0x00bc
    /**
    * @brief   - INVERTED EXCLAMATION MARK
    */
    ,0x00a1
    /**
    * @brief   - LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
    */
    ,0x00ab
    /**
    * @brief   - RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    */
    ,0x00bb
    /**
    * @brief   - LIGHT SHADE
    */
    ,0x2591
    /**
    * @brief   - MEDIUM SHADE
    */
    ,0x2592
    /**
    * @brief   - DARK SHADE
    */
    ,0x2593
    /**
    * @brief   - BOX DRAWINGS LIGHT VERTICAL
    */
    ,0x2502
    /**
    * @brief   - BOX DRAWINGS LIGHT VERTICAL AND LEFT
    */
    ,0x2524
    /**
    * @brief   - BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE
    */
    ,0x2561
    /**
    * @brief   - BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE
    */
    ,0x2562
    /**
    * @brief   - BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE
    */
    ,0x2556
    /**
    * @brief   - BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE
    */
    ,0x2555
    /**
    * @brief   - BOX DRAWINGS DOUBLE VERTICAL AND LEFT
    */
    ,0x2563
    /**
    * @brief   - BOX DRAWINGS DOUBLE VERTICAL
    */
    ,0x2551
    /**
    * @brief   - BOX DRAWINGS DOUBLE DOWN AND LEFT
    */
    ,0x2557
    /**
    * @brief   - BOX DRAWINGS DOUBLE UP AND LEFT
    */
    ,0x255d
    /**
    * @brief   - BOX DRAWINGS UP DOUBLE AND LEFT SINGLE
    */
    ,0x255c
    /**
    * @brief   - BOX DRAWINGS UP SINGLE AND LEFT DOUBLE
    */
    ,0x255b
    /**
    * @brief   - BOX DRAWINGS LIGHT DOWN AND LEFT
    */
    ,0x2510
    /**
    * @brief   - BOX DRAWINGS LIGHT UP AND RIGHT
    */
    ,0x2514
    /**
    * @brief   - BOX DRAWINGS LIGHT UP AND HORIZONTAL
    */
    ,0x2534
    /**
    * @brief   - BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    */
    ,0x252c
    /**
    * @brief   - BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    */
    ,0x251c
    /**
    * @brief   - BOX DRAWINGS LIGHT HORIZONTAL
    */
    ,0x2500
    /**
    * @brief   - BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    */
    ,0x253c
    /**
    * @brief   - BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE
    */
    ,0x255e
    /**
    * @brief   - BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE
    */
    ,0x255f
    /**
    * @brief   - BOX DRAWINGS DOUBLE UP AND RIGHT
    */
    ,0x255a
    /**
    * @brief   - BOX DRAWINGS DOUBLE DOWN AND RIGHT
    */
    ,0x2554
    /**
    * @brief   - BOX DRAWINGS DOUBLE UP AND HORIZONTAL
    */
    ,0x2569
    /**
    * @brief   - BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL
    */
    ,0x2566
    /**
    * @brief   - BOX DRAWINGS DOUBLE VERTICAL AND RIGHT
    */
    ,0x2560
    /**
    * @brief   - BOX DRAWINGS DOUBLE HORIZONTAL
    */
    ,0x2550
    /**
    * @brief   - BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL
    */
    ,0x256c
    /**
    * @brief   - BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE
    */
    ,0x2567
    /**
    * @brief   - BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE
    */
    ,0x2568
    /**
    * @brief   - BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE
    */
    ,0x2564
    /**
    * @brief   - BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE
    */
    ,0x2565
    /**
    * @brief   - BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE
    */
    ,0x2559
    /**
    * @brief   - BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE
    */
    ,0x2558
    /**
    * @brief   - BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE
    */
    ,0x2552
    /**
    * @brief   - BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE
    */
    ,0x2553
    /**
    * @brief   - BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE
    */
    ,0x256b
    /**
    * @brief   - BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE
    */
    ,0x256a
    /**
    * @brief   - BOX DRAWINGS LIGHT UP AND LEFT
    */
    ,0x2518
    /**
    * @brief   - BOX DRAWINGS LIGHT DOWN AND RIGHT
    */
    ,0x250c
    /**
    * @brief   - FULL BLOCK
    */
    ,0x2588
    /**
    * @brief   - LOWER HALF BLOCK
    */
    ,0x2584
    /**
    * @brief   - LEFT HALF BLOCK
    */
    ,0x258c
    /**
    * @brief   - RIGHT HALF BLOCK
    */
    ,0x2590
    /**
    * @brief   - UPPER HALF BLOCK
    */
    ,0x2580
    /**
    * @brief   - GREEK SMALL LETTER ALPHA
    */
    ,0x03b1
    /**
    * @brief   - LATIN SMALL LETTER SHARP S
    */
    ,0x00df
    /**
    * @brief   - GREEK CAPITAL LETTER GAMMA
    */
    ,0x0393
    /**
    * @brief   - GREEK SMALL LETTER PI
    */
    ,0x03c0
    /**
    * @brief   - GREEK CAPITAL LETTER SIGMA
    */
    ,0x03a3
    /**
    * @brief   - GREEK SMALL LETTER SIGMA
    */
    ,0x03c3
    /**
    * @brief   - MICRO SIGN
    */
    ,0x00b5
    /**
    * @brief   - GREEK SMALL LETTER TAU
    */
    ,0x03c4
    /**
    * @brief   - GREEK CAPITAL LETTER PHI
    */
    ,0x03a6
    /**
    * @brief   - GREEK CAPITAL LETTER THETA
    */
    ,0x0398
    /**
    * @brief   - GREEK CAPITAL LETTER OMEGA
    */
    ,0x03a9
    /**
    * @brief   - GREEK SMALL LETTER DELTA
    */
    ,0x03b4
    /**
    * @brief   - INFINITY
    */
    ,0x221e
    /**
    * @brief   - GREEK SMALL LETTER PHI
    */
    ,0x03c6
    /**
    * @brief   - GREEK SMALL LETTER EPSILON
    */
    ,0x03b5
    /**
    * @brief   - INTERSECTION
    */
    ,0x2229
    /**
    * @brief   - IDENTICAL TO
    */
    ,0x2261
    /**
    * @brief   - PLUS-MINUS SIGN
    */
    ,0x00b1
    /**
    * @brief   - GREATER-THAN OR EQUAL TO
    */
    ,0x2265
    /**
    * @brief   - LESS-THAN OR EQUAL TO
    */
    ,0x2264
    /**
    * @brief   - TOP HALF INTEGRAL
    */
    ,0x2320
    /**
    * @brief   - BOTTOM HALF INTEGRAL
    */
    ,0x2321
    /**
    * @brief   - DIVISION SIGN
    */
    ,0x00f7
    /**
    * @brief   - ALMOST EQUAL TO
    */
    ,0x2248
    /**
    * @brief   - DEGREE SIGN
    */
    ,0x00b0
    /**
    * @brief   - BULLET OPERATOR
    */
    ,0x2219
    /**
    * @brief   - MIDDLE DOT
    */
    ,0x00b7
    /**
    * @brief   - SQUARE ROOT
    */
    ,0x221a
    /**
    * @brief   - SUPERSCRIPT LATIN SMALL LETTER N
    */
    ,0x207f
    /**
    * @brief   - SUPERSCRIPT TWO
    */
    ,0x00b2
    /**
    * @brief   - BLACK SQUARE
    */
    ,0x25a0
    /**
    * @brief   - NO-BREAK SPACE
    */
    ,0x00a0
    };

    static const wchar_t lowASCIISymbols[256] = {
        0x2007, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022,
        0x25D8, 0x25CB, 0x25D9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
        0x25B6, 0x25C0, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8,
        0x2191, 0x2193, 0x2192, 0x2190, 0x221F, 0x2194, 0x25B2, 0x25BC, 
    };
  } // NS: IO
} // NS: SIMPLE
#endif // TERMINALNFO_HPP