#ifndef ST7735_TEXT_H
#define ST7735_TEXT_H

#include "ST7735.h"
#include <avr/interrupt.h>
short le;
short ri;

void DrawChar(short x, short y, short color, char currVal) {
  switch (currVal) {
  case '0': // TODO:
  case 0x0:
    // vertical
    for (short j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      Pixel(x + 11, j, color);
      Pixel(x + 10, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      // Pixel(i, y + 10, color);
      // Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '1':
  case 0x1:
    // vertical
    for (short j = y; j < y + 20; j++) {
      Pixel(x + 6, j, color);
      Pixel(x + 7, j, color);
    }

    // horizontal
    for (short i = x; i < x + 12; i++) {
      if (i < x + 8 && i > x + 2) {
        Pixel(i, y, color);
        Pixel(i, y + 1, color);
      }

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '2':
  case 0x2:
    // vertical
    for (short j = y; j < y + 20; j++) {
      if (j < y + 11) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      } else if (j >= y + 11) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      }
    }

    // horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }

    break;
  case '3':
  case 0x3:
    // vertical
    for (short j = y; j < y + 21; j++) {
      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    // horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '4':
  case 0x4:
    // vertical
    for (short j = y; j < y + 21; j++) {
      if (j < y + 11) {
        Pixel(x, j, color);

        Pixel(x + 1, j, color);
      }

      Pixel(x + 11, j, color);

      Pixel(x + 10, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y + 10, color);

      Pixel(i, y + 9, color);
    }

    break;
  case '5':
  case 0x5:
    // vertical
    for (short j = y; j < y + 20; j++) {
      if (j < y + 11) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      } else if (j >= y + 11) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '6':
  case 0x6:
    // vertical
    for (short j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      if (j > y + 10) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      // top
      // Pixel(i, y, color);
      // Pixel(i, y + 1, color);

      // middle
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);

      // bottom
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;

  case '7':
  case 0x7:
    // vertical
    for (short j = y; j < y + 20; j++) {
      Pixel(x + 11, j, color);
      Pixel(x + 12, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
    }
    break;
  case 'A':
  case 0xA:
    for (short j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);
    }
    break;
  case '8':
  case 0x8:
    // vertical
    for (short j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      Pixel(x + 11, j, color);
      Pixel(x + 10, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '9':
  case 0x9:
    // vertical
    for (short j = y; j < y + 20; j++) {
      if (j < y + 10) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      }

      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;

  case 'B':
  case 0xB:
    // vertical
    for (short j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
      if (j <= y + 10) {
        Pixel(x + 8, j, color);
        Pixel(x + 9, j, color);
      }
      if (j > y + 10) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
    }
    // horizontal
    for (short i = x; i < x + 12; i++) {
      if (i < x + 10) {
        Pixel(i, y, color);
        Pixel(i, y + 1, color);
      }
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'C':
  case 0xC:
    // vertical
    for (short j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
    }
    // horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'D':
  case 0xD:
    // Vertical
    for (short j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
      if (j > y + 1 && j < y + 19) {
        Pixel(x + 9, j, color);
        Pixel(x + 10, j, color);
      }
    }
    // Horizontal
    for (short i = x; i < x + 9; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'E':
  case 0xE:
    // Vertical
    for (short j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'F':
  case 0xF:
    // Vertical
    for (short j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
    }
    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);
    }
    break;
  case 'x':
    // vertical
    le = 0;
    ri = 0;
    for (short j = y; j < y + 12; j++) {
      Pixel(x + le, j, color);
      Pixel(x + 1 + le, j, color);
      ++le;

      Pixel(x + 11 - ri, j, color);
      Pixel(x + 10 - ri, j, color);
      ++ri;
    }
    break;
  case '%':
    // vertical
    le = 0;
    ri = 0;
    Box(x, y, 2, 2, color);
    Box(x + 10, y + 10, 2, 2, color);
    for (short j = y; j < y + 12; j++) {
      Pixel(x + 11 - ri, j, color);
      Pixel(x + 10 - ri, j, color);
      ++ri;
    }
    break;
  case ':':
    Box(x, y + 5, 2, 2, color);
    Box(x, y + 15, 2, 2, color);
    break;
  case 'P':
    for (short j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      if (j < y + 10) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      //    Pixel(i, y + 19, color);
      //    Pixel(i, y + 20, color);
    }
    break;
  case 'L':
    for (short j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      //    Pixel(x + 11, j, color);
      //    Pixel(x + 10, j, color);
    }

    // Horizontal
    for (short i = x; i < x + 12; i++) {
      //    Pixel(i, y, color);
      //    Pixel(i, y + 1, color);

      //    Pixel(i, y + 10, color);
      //    Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'Y':
    // Upper diagonal arms
    for (short j = 0; j < 6; j++) {
      Pixel(x + j, y + j, color); // Left diagonal arm
      Pixel(x + j + 1, y + j, color);

      Pixel(x + 10 - j, y + j, color); // Right diagonal arm
      Pixel(x + 10 - j - 1, y + j, color);
    }

    // Vertical stem
    for (short j = y + 5; j < y + 20; j++) {
      Pixel(x + 4, j, color);
      Pixel(x + 5, j, color);
      Pixel(x + 6, j, color);
    }
    break;
  default:
    break;
  }
}

#endif // ST7735_TEXT_H
