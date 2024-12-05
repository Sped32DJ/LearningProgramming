#ifndef ST7735_TEXT_H
#define ST7735_TEXT_H

#include "ST7735.h"
#include <avr/interrupt.h>

void DrawChar(short x, short y, short color, char currVal) {
  switch (currVal) {
  case '0': // TODO:
  case 0x0:
    break;
  case '1':
  case 0x1:
    for (short j = y; j < y + 20; j++) // Vertical Line
    {
      Pixel(x + 6, j, color);
      Pixel(x + 7, j, color);
    }

    for (short i = x; i < x + 12; i++) // Horizontal Line
    {
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
    for (short j = y; j < y + 20; j++) // Vertical Line
    {
      if (j < y + 11) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      } else if (j >= y + 11) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      }
    }

    for (short i = x; i < x + 12; i++) // Horizontal Line
    {
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
    for (short j = y; j < y + 21; j++) // Vertical Lines
    {
      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    for (short i = x; i < x + 12; i++) // Horizontal Lines
    {
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
  case '6': // FIX: Not working
  case 0x6:
    // vertical
    for (short j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      if (j > 10) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
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
  default:
    break;
  }
}

#endif // ST7735_TEXT_H
