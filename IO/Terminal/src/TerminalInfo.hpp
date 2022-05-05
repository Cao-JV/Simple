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
 * of this software and associated documentation files (the 'Software'), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
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
    enum class TerminalCursorMovement {
       Up         = 'A'
      ,Down       = 'B'
      ,Right      = 'C'
      ,Left       = 'D'
      ,NextLine   = 'E'
      ,PrevLine   = 'F'
      ,SetRow     = 'G'
      ,ScrollUp   = 'S'
      ,ScrollDown = 'T'

    };
    enum class TerminalAttributes {
       None          = 0
      ,ExtendedAscii = 1
      ,Echo          = 2
      ,Blink         = 4
      ,Cursor        = 8
      ,LineBuffer    = 16
    };

  inline TerminalAttributes operator|(TerminalAttributes a, TerminalAttributes b)
  {
      return static_cast<TerminalAttributes>(static_cast<int>(a) | static_cast<int>(b));
  }
  inline TerminalAttributes operator&(TerminalAttributes a, TerminalAttributes b)
  {
      return static_cast<TerminalAttributes>(static_cast<int>(a) & static_cast<int>(b));
  }
  inline TerminalAttributes operator~(TerminalAttributes a)
  {
      return static_cast<TerminalAttributes>(~static_cast<int>(a));
  }
  inline TerminalAttributes operator^(TerminalAttributes a, TerminalAttributes b)
  {
      return static_cast<TerminalAttributes>(static_cast<int>(a) ^ static_cast<int>(b));
  }

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
          ,Red        = 1
          ,DarkGreen  = 2
          ,Brown      = 3
          ,Navy       = 4
          ,Purple     = 5
          ,Teal       = 6
          ,LiteGrey   = 7
          ,DarkGrey   = 8
          ,Pink       = 9
          ,Chartreuse = 10
          ,Yellow     = 11
          ,Blue       = 12
          ,Magenta    = 13
          ,Aqua       = 14
          ,White      = 15
      };
      enum class TerminalColourModes {
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
      L'\u0000'
      /**
        * @brief 1 - Start Heading
        */
      ,L'\u0001'
      /**
       * @brief  2 - Start Text
       */
      ,L'\u0002'
      /**
      * @brief   3 - End Text
      */
      ,L'\u0003'
      /**
      * @brief   4 - End Transmission
      */
      ,L'\u0004'
      /**
      * @brief   5 - Enquire
      */
      ,L'\u0005'
      /**
      * @brief   6 - ACK
      */
      ,L'\u0006'
      /**
      * @brief   7 - Bell
      */
      ,L'\u0007'
      /**
      * @brief   8 - BackSpace
      */
      ,L'\u0008'
      /**
      * @brief   9 - Tab
      */
      ,L'\u0009'
      /**
      * @brief   10 - Line Feed
      */
      ,L'\u000a'
      /**
      * @brief   11 - Vert Tab
      */
      ,L'\u000b'
      /**
      * @brief   12 - Form Feed
      */
      ,L'\u000c'
      /**
      * @brief   13 - Carriage Return
      */
      ,L'\u000d'
      /**
      * @brief   14 - Shift Out <<
      */
      ,L'\u000e'
      /**
      * @brief   15 - Shift In >>
      */
      ,L'\u000f'
      /**
      * @brief   16 - Datalink Escape
      */
      ,L'\u0010'
      /**
      * @brief   17 - Dev Control 1
      */
      ,L'\u0011'
      /**
      * @brief   18 - Dev Control 2
      */
      ,L'\u0012'
      /**
      * @brief   19 - Dev Control 3
      */
      ,L'\u0013'
      /**
      * @brief   20 - Dev Control 4
      */
      ,L'\u0014'
      /**
      * @brief   21 - -ACK
      */
      ,L'\u0015'
      /**
      * @brief   22 - Sync. Idle
      */
      ,L'\u0016'
      /**
      * @brief   23 - End Transmission Block
      */
      ,L'\u0017'
      /**
      * @brief   24 - Cancel
      */
      ,L'\u0018'
      /**
      * @brief   25 - End Medium
      */
      ,L'\u0019'
      /**
      * @brief   26 - Substitution
      */
      ,L'\u001a'
      /**
      * @brief   27 - Escape
      */
      ,L'\u001b'
      /**
      * @brief   28 - File Separator
      */
      ,L'\u001c'
      /**
      * @brief   29 - Group Separator
      */
      ,L'\u001d'
      /**
      * @brief   30 - Record Separator
      */
      ,L'\u001e'
      /**
      * @brief   31 - Unit Separator
      */
      ,L'\u001f'
      /**
      * @brief   32 - Space
      */
      ,L'\u0020'
      /**
  * @brief 33 - !
  */
  ,L'\u0021'
  /**
  * @brief 34 - "
  */
  ,L'\u0022'
  /**
  * @brief 35 - #
  */
  ,L'\u0023'
  /**
  * @brief 36 - $
  */
  ,L'\u0024'
  /**
  * @brief 37 - %
  */
  ,L'\u0025'
  /**
  * @brief 38 - &
  */
  ,L'\u0026'
  /**
  * @brief 39 - '
  */
  ,L'\u0027'
  /**
  * @brief 40 - (
  */
  ,L'\u0028'
  /**
  * @brief 41 - )
  */
  ,L'\u0029'
  /**
  * @brief 42 - *
  */
  ,L'\u002A'
  /**
  * @brief 43 - +
  */
  ,L'\u002B'
  /**
  * @brief 44 - ,
  */
  ,L'\u002C'
  /**
  * @brief 45 - -
  */
  ,L'\u002D'
  /**
  * @brief 46 - .
  */
  ,L'\u002E'
  /**
  * @brief 47 - /
  */
  ,L'\u002F'
  /**
  * @brief 48 - 0
  */
  ,L'\u0030'
  /**
  * @brief 49 - 1
  */
  ,L'\u0031'
  /**
  * @brief 50 - 2
  */
  ,L'\u0032'
  /**
  * @brief 51 - 3
  */
  ,L'\u0033'
  /**
  * @brief 52 - 4
  */
  ,L'\u0034'
  /**
  * @brief 53 - 5
  */
  ,L'\u0035'
  /**
  * @brief 54 - 6
  */
  ,L'\u0036'
  /**
  * @brief 55 - 7
  */
  ,L'\u0037'
  /**
  * @brief 56 - 8
  */
  ,L'\u0038'
  /**
  * @brief 57 - 9
  */
  ,L'\u0039'
  /**
  * @brief 58 - :
  */
  ,L'\u003A'
  /**
  * @brief 59 - ;
  */
  ,L'\u003B'
  /**
  * @brief 60 - <
  */
  ,L'\u003C'
  /**
  * @brief 61 - =
  */
  ,L'\u003D'
  /**
  * @brief 62 - >
  */
  ,L'\u003E'
  /**
  * @brief 63 - ?
  */
  ,L'\u003F'
  /**
  * @brief 64 - @
  */
  ,L'\u0040'
  /**
  * @brief 65 - A
  */
  ,L'\u0041'
  /**
  * @brief 66 - B
  */
  ,L'\u0042'
  /**
  * @brief 67 - C
  */
  ,L'\u0043'
  /**
  * @brief 68 - D
  */
  ,L'\u0044'
  /**
  * @brief 69 - E
  */
  ,L'\u0045'
  /**
  * @brief 70 - F
  */
  ,L'\u0046'
  /**
  * @brief 71 - G
  */
  ,L'\u0047'
  /**
  * @brief 72 - H
  */
  ,L'\u0048'
  /**
  * @brief 73 - I
  */
  ,L'\u0049'
  /**
  * @brief 74 - J
  */
  ,L'\u004A'
  /**
  * @brief 75 - K
  */
  ,L'\u004B'
  /**
  * @brief 76 - L
  */
  ,L'\u004C'
  /**
  * @brief 77 - M
  */
  ,L'\u004D'
  /**
  * @brief 78 - N
  */
  ,L'\u004E'
  /**
  * @brief 79 - O
  */
  ,L'\u004F'
  /**
  * @brief 80 - P
  */
  ,L'\u0050'
  /**
  * @brief 81 - Q
  */
  ,L'\u0051'
  /**
  * @brief 82 - R
  */
  ,L'\u0052'
  /**
  * @brief 83 - S
  */
  ,L'\u0053'
  /**
  * @brief 84 - T
  */
  ,L'\u0054'
  /**
  * @brief 85 - U
  */
  ,L'\u0055'
  /**
  * @brief 86 - V
  */
  ,L'\u0056'
  /**
  * @brief 87 - W
  */
  ,L'\u0057'
  /**
  * @brief 88 - X
  */
  ,L'\u0058'
  /**
  * @brief 89 - Y
  */
  ,L'\u0059'
  /**
  * @brief 90 - Z
  */
  ,L'\u005A'
  /**
  * @brief 91 - [
  */
  ,L'\u005B'
  /**
  * @brief 92 - \
  */
  ,L'\u005C'
  /**
  * @brief 93 - ]
  */
  ,L'\u005D'
  /**
  * @brief 94 - ^
  */
  ,L'\u005E'
  /**
  * @brief 95 - _
  */
  ,L'\u005F'
  /**
  * @brief 96 - `
  */
  ,L'\u0060'
  /**
  * @brief 97 - a
  */
  ,L'\u0061'
  /**
  * @brief 98 - b
  */
  ,L'\u0062'
  /**
  * @brief 99 - c
  */
  ,L'\u0063'
  /**
  * @brief 100 - d
  */
  ,L'\u0064'
  /**
  * @brief 101 - e
  */
  ,L'\u0065'
  /**
  * @brief 102 - f
  */
  ,L'\u0066'
  /**
  * @brief 103 - g
  */
  ,L'\u0067'
  /**
  * @brief 104 - h
  */
  ,L'\u0068'
  /**
  * @brief 105 - i
  */
  ,L'\u0069'
  /**
  * @brief 106 - j
  */
  ,L'\u006A'
  /**
  * @brief 107 - k
  */
  ,L'\u006B'
  /**
  * @brief 108 - l
  */
  ,L'\u006C'
  /**
  * @brief 109 - m
  */
  ,L'\u006D'
  /**
  * @brief 110 - n
  */
  ,L'\u006E'
  /**
  * @brief 111 - o
  */
  ,L'\u006F'
  /**
  * @brief 112 - p
  */
  ,L'\u0070'
  /**
  * @brief 113 - q
  */
  ,L'\u0071'
  /**
  * @brief 114 - r
  */
  ,L'\u0072'
  /**
  * @brief 115 - s
  */
  ,L'\u0073'
  /**
  * @brief 116 - t
  */
  ,L'\u0074'
  /**
  * @brief 117 - u
  */
  ,L'\u0075'
  /**
  * @brief 118 - v
  */
  ,L'\u0076'
  /**
  * @brief 119 - w
  */
  ,L'\u0077'
  /**
  * @brief 120 - x
  */
  ,L'\u0078'
  /**
  * @brief 121 - y
  */
  ,L'\u0079'
  /**
  * @brief 122 - z
  */
  ,L'\u007A'
  /**
  * @brief 123 - {
  */
  ,L'\u007B'
  /**
  * @brief 124 - |
  */
  ,L'\u007C'
  /**
  * @brief 125 - }
  */
  ,L'\u007D'
  /**
  * @brief 126 - ~
  */
  ,L'\u007E'
  /**
  * @brief 127 - 
  */
  ,L'\u007F'
  /**
  * @brief 128 - Ç
  */
  ,L'\u00C7'
  /**
  * @brief 129 - ü
  */
  ,L'\u00FC'
  /**
  * @brief 130 - é
  */
  ,L'\u00E9'
  /**
  * @brief 131 - â
  */
  ,L'\u00E2'
  /**
  * @brief 132 - ä
  */
  ,L'\u00E4'
  /**
  * @brief 133 - à
  */
  ,L'\u00E0'
  /**
  * @brief 134 - å
  */
  ,L'\u00E5'
  /**
  * @brief 135 - ç
  */
  ,L'\u00E7'
  /**
  * @brief 136 - ê
  */
  ,L'\u00EA'
  /**
  * @brief 137 - ë
  */
  ,L'\u00EB'
  /**
  * @brief 138 - è
  */
  ,L'\u00E8'
  /**
  * @brief 139 - ï
  */
  ,L'\u00EF'
  /**
  * @brief 140 - î
  */
  ,L'\u00EE'
  /**
  * @brief 141 - ì
  */
  ,L'\u00EC'
  /**
  * @brief 142 - Ä
  */
  ,L'\u00C4'
  /**
  * @brief 143 - Å
  */
  ,L'\u00C5'
  /**
  * @brief 144 - É
  */
  ,L'\u00C9'
  /**
  * @brief 145 - æ
  */
  ,L'\u00E6'
  /**
  * @brief 146 - Æ
  */
  ,L'\u00C6'
  /**
  * @brief 147 - ô
  */
  ,L'\u00F4'
  /**
  * @brief 148 - ö
  */
  ,L'\u00F6'
  /**
  * @brief 149 - ò
  */
  ,L'\u00F2'
  /**
  * @brief 150 - û
  */
  ,L'\u00FB'
  /**
  * @brief 151 - ù
  */
  ,L'\u00F9'
  /**
  * @brief 152 - ÿ
  */
  ,L'\u00FF'
  /**
  * @brief 153 - Ö
  */
  ,L'\u00D6'
  /**
  * @brief 154 - Ü
  */
  ,L'\u00DC'
  /**
  * @brief 155 - ¢
  */
  ,L'\u00A2'
  /**
  * @brief 156 - £
  */
  ,L'\u00A3'
  /**
  * @brief 157 - ¥
  */
  ,L'\u00A5'
  /**
  * @brief 158 - ₧
  */
  ,L'\u20A7'
  /**
  * @brief 159 - ƒ
  */
  ,L'\u0192'
  /**
  * @brief 160 - á
  */
  ,L'\u00E1'
  /**
  * @brief 161 - í
  */
  ,L'\u00ED'
  /**
  * @brief 162 - ó
  */
  ,L'\u00F3'
  /**
  * @brief 163 - ú
  */
  ,L'\u00FA'
  /**
  * @brief 164 - ñ
  */
  ,L'\u00F1'
  /**
  * @brief 165 - Ñ
  */
  ,L'\u00D1'
  /**
  * @brief 166 - ª
  */
  ,L'\u00AA'
  /**
  * @brief 167 - º
  */
  ,L'\u00BA'
  /**
  * @brief 168 - ¿
  */
  ,L'\u00BF'
  /**
  * @brief 169 - ⌐
  */
  ,L'\u2310'
  /**
  * @brief 170 - ¬
  */
  ,L'\u00AC'
  /**
  * @brief 171 - ½
  */
  ,L'\u00BD'
  /**
  * @brief 172 - ¼
  */
  ,L'\u00BC'
  /**
  * @brief 173 - ¡
  */
  ,L'\u00A1'
  /**
  * @brief 174 - «
  */
  ,L'\u00AB'
  /**
  * @brief 175 - »
  */
  ,L'\u00BB'
  /**
  * @brief 176 - ░
  */
  ,L'\u2591'
  /**
  * @brief 177 - ▒
  */
  ,L'\u2592'
  /**
  * @brief 178 - ▓
  */
  ,L'\u2593'
  /**
  * @brief 179 - │
  */
  ,L'\u2502'
  /**
  * @brief 180 - ┤
  */
  ,L'\u2524'
  /**
  * @brief 181 - ╡
  */
  ,L'\u2561'
  /**
  * @brief 182 - ╢
  */
  ,L'\u2562'
  /**
  * @brief 183 - ╖
  */
  ,L'\u2556'
  /**
  * @brief 184 - ╕
  */
  ,L'\u2555'
  /**
  * @brief 185 - ╣
  */
  ,L'\u2563'
  /**
  * @brief 186 - ║
  */
  ,L'\u2551'
  /**
  * @brief 187 - ╗
  */
  ,L'\u2557'
  /**
  * @brief 188 - ╝
  */
  ,L'\u255D'
  /**
  * @brief 189 - ╜
  */
  ,L'\u255C'
  /**
  * @brief 190 - ╛
  */
  ,L'\u255B'
  /**
  * @brief 191 - ┐
  */
  ,L'\u2510'
  /**
  * @brief 192 - └
  */
  ,L'\u2514'
  /**
  * @brief 193 - ┴
  */
  ,L'\u2534'
  /**
  * @brief 194 - ┬
  */
  ,L'\u252C'
  /**
  * @brief 195 - ├
  */
  ,L'\u251C'
  /**
  * @brief 196 - ─
  */
  ,L'\u2500'
  /**
  * @brief 197 - ┼
  */
  ,L'\u253C'
  /**
  * @brief 198 - ╞
  */
  ,L'\u255E'
  /**
  * @brief 199 - ╟
  */
  ,L'\u255F'
  /**
  * @brief 200 - ╚
  */
  ,L'\u255A'
  /**
  * @brief 201 - ╔
  */
  ,L'\u2554'
  /**
  * @brief 202 - ╩
  */
  ,L'\u2569'
  /**
  * @brief 203 - ╦
  */
  ,L'\u2566'
  /**
  * @brief 204 - ╠
  */
  ,L'\u2560'
  /**
  * @brief 205 - ═
  */
  ,L'\u2550'
  /**
  * @brief 206 - ╬
  */
  ,L'\u256C'
  /**
  * @brief 207 - ╧
  */
  ,L'\u2567'
  /**
  * @brief 208 - ╨
  */
  ,L'\u2568'
  /**
  * @brief 209 - ╤
  */
  ,L'\u2564'
  /**
  * @brief 210 - ╥
  */
  ,L'\u2565'
  /**
  * @brief 211 - ╙
  */
  ,L'\u2559'
  /**
  * @brief 212 - ╘
  */
  ,L'\u2558'
  /**
  * @brief 213 - ╒
  */
  ,L'\u2552'
  /**
  * @brief 214 - ╓
  */
  ,L'\u2553'
  /**
  * @brief 215 - ╫
  */
  ,L'\u256B'
  /**
  * @brief 216 - ╪
  */
  ,L'\u256A'
  /**
  * @brief 217 - ┘
  */
  ,L'\u2518'
  /**
  * @brief 218 - ┌
  */
  ,L'\u250C'
  /**
  * @brief 219 - █
  */
  ,L'\u2588'
  /**
  * @brief 220 - ▄
  */
  ,L'\u2584'
  /**
  * @brief 221 - ▌
  */
  ,L'\u258C'
  /**
  * @brief 222 - ▐
  */
  ,L'\u2590'
  /**
  * @brief 223 - ▀
  */
  ,L'\u2580'
  /**
  * @brief 224 - α
  */
  ,L'\u03B1'
  /**
  * @brief 225 - ß
  */
  ,L'\u00DF'
  /**
  * @brief 226 - Γ
  */
  ,L'\u0393'
  /**
  * @brief 227 - π
  */
  ,L'\u03C0'
  /**
  * @brief 228 - Σ
  */
  ,L'\u03A3'
  /**
  * @brief 229 - σ
  */
  ,L'\u03C3'
  /**
  * @brief 230 - µ
  */
  ,L'\u00B5'
  /**
  * @brief 231 - τ
  */
  ,L'\u03C4'
  /**
  * @brief 232 - Φ
  */
  ,L'\u03A6'
  /**
  * @brief 233 - Θ
  */
  ,L'\u0398'
  /**
  * @brief 234 - Ω
  */
  ,L'\u03A9'
  /**
  * @brief 235 - δ
  */
  ,L'\u03B4'
  /**
  * @brief 236 - ∞
  */
  ,L'\u221E'
  /**
  * @brief 237 - φ
  */
  ,L'\u03C6'
  /**
  * @brief 238 - ε
  */
  ,L'\u03B5'
  /**
  * @brief 239 - ∩
  */
  ,L'\u2229'
  /**
  * @brief 240 - ≡
  */
  ,L'\u2261'
  /**
  * @brief 241 - ±
  */
  ,L'\u00B1'
  /**
  * @brief 242 - ≥
  */
  ,L'\u2265'
  /**
  * @brief 243 - ≤
  */
  ,L'\u2264'
  /**
  * @brief 244 - ⌠
  */
  ,L'\u2320'
  /**
  * @brief 245 - ⌡
  */
  ,L'\u2321'
  /**
  * @brief 246 - ÷
  */
  ,L'\u00F7'
  /**
  * @brief 247 - ≈
  */
  ,L'\u2248'
  /**
  * @brief 248 - °
  */
  ,L'\u00B0'
  /**
  * @brief 249 - ∙
  */
  ,L'\u2219'
  /**
  * @brief 250 - ·
  */
  ,L'\u00B7'
  /**
  * @brief 251 - √
  */
  ,L'\u221A'
  /**
  * @brief 252 - ⁿ
  */
  ,L'\u207F'
  /**
  * @brief 253 - ²
  */
  ,L'\u00B2'
  /**
  * @brief 254 - ■
  */
  ,L'\u25A0'
  /**
  * @brief 255 -  
  */
  ,L'\u00A0'

      };
  /*
      static const wchar_t lowASCIISymbols[256] = {
          L'\u2007, L'\u263A, L'\u263B, L'\u2665, L'\u2666, L'\u2663, L'\u2660, L'\u2022,
          L'\u25D8, L'\u25CB, L'\u25D9, L'\u2642, L'\u2640, L'\u266A, L'\u266B, L'\u263C,
          L'\u25B6, L'\u25C0, L'\u2195, L'\u203C, L'\u00B6, L'\u00A7, L'\u25AC, L'\u21A8,
          L'\u2191, L'\u2193, L'\u2192, L'\u2190, L'\u221F, L'\u2194, L'\u25B2, L'\u25BC, 
      };
      */
    } // NS: IO
  } // NS: SIMPLE
#endif // TERMINALNFO_HPP