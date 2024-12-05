#ifndef ST7735_TEXT_H
#define ST7735_TEXT_H

#include "ST7735.h"
#include <avr/interrupt.h>

void DrawChar(short x, short y, short color, char currVal) {
  switch (currVal) {
  case '0': // TODO:
    break;
  case '1':
    for (uint16_t j = y; j < y + 20; j++) // Vertical Line
    {
      Pixel(x + 6, j, color);
      Pixel(x + 7, j, color);
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Line
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
    for (uint16_t j = y; j < y + 20; j++) // Vertical Line
    {
      if (j < y + 11) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      } else if (j >= y + 11) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      }
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Line
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
    for (uint16_t j = y; j < y + 21; j++) // Vertical Lines
    {
      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Lines
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
    for (uint16_t j = y; j < y + 21; j++) // Vertical Lines
    {
      if (j < y + 11) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      }

      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Lines
    {
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);
    }

    break;
  case '5':
    for (uint16_t j = y; j < y + 20; j++) // Vertical Line
    {
      if (j < y + 11) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      } else if (j >= y + 11) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Line
    {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '6':
    for (uint16_t j = y; j < y + 21; j++) // Vertical Lines
    {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      if (j > 10) {
        Pixel(x + 10, j, color);
        Pixel(x + 11, j, color);
      }
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Lines
    {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '7':
    for (uint16_t j = y; j < y + 20; j++) // Vertical Line
    {
      Pixel(x + 11, j, color);
      Pixel(x + 12, j, color);
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Line
    {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
    }
    break;
  case 'A': // Draws an 'A'
    for (uint16_t j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }
    for (uint16_t i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);
    }
    break;
  case '8':
    for (uint16_t j = y; j < y + 20; j++) // Vertical Lines
    {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);

      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Lines
    {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case '9':
    for (uint16_t j = y; j < y + 20; j++) // Vertical Lines
    {
      if (j < y + 10) {
        Pixel(x, j, color);
        Pixel(x + 1, j, color);
      }

      Pixel(x + 10, j, color);
      Pixel(x + 11, j, color);
    }

    for (uint16_t i = x; i < x + 12; i++) // Horizontal Lines
    {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);

      Pixel(i, y + 10, color);
      Pixel(i, y + 11, color);

      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'B': // Draws a 'B'
    for (uint16_t j = y; j < y + 21; j++) {
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
    for (uint16_t i = x; i < x + 12; i++) {
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
  case 'C': // Draws a 'C'
    for (uint16_t j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
    }
    for (uint16_t i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'D': // Draws a 'D'
    for (uint16_t j = y; j < y + 20; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
      if (j > y + 1 && j < y + 19) {
        Pixel(x + 9, j, color);
        Pixel(x + 10, j, color);
      }
    }
    for (uint16_t i = x; i < x + 9; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'E': // Draws an 'E'
    for (uint16_t j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
    }
    for (uint16_t i = x; i < x + 12; i++) {
      Pixel(i, y, color);
      Pixel(i, y + 1, color);
      Pixel(i, y + 9, color);
      Pixel(i, y + 10, color);
      Pixel(i, y + 19, color);
      Pixel(i, y + 20, color);
    }
    break;
  case 'F': // Draws an 'F'
    for (uint16_t j = y; j < y + 21; j++) {
      Pixel(x, j, color);
      Pixel(x + 1, j, color);
    }
    for (uint16_t i = x; i < x + 12; i++) {
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
