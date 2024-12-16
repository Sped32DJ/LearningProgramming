#ifndef ST7735_H
#define ST7735_H

#include "helper.h"
#include "spiAVR.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h> // Include delay header

// TODO: Fix these definitions to be accurate
#define SWRESET 0x01 // Software reset
#define SLPOUT 0x11  // Sleep out & booster on
#define INVON 0x21
#define DISPON 0x29 // Display On
#define CASET 0x2A  // Column address set
#define RASET 0x2B  // Row address set
#define RAMWR 0x2C  // Memory write
#define COLMOD 0x3A // Interface pixel format

const unsigned int MAX_X = 129; // Screen width
const unsigned int MAX_Y = 130; // Screen height

// Send Command Macro (A0 pin)
void Send_Command(unsigned char cmd) {
  PORTB = SetBit(PORTB, 2, 0); // Command mode; CS = 0
  PORTB = SetBit(PORTB, 1, 0); // Command mode; A0 = 0
  SPI_SEND(cmd);
  PORTB = SetBit(PORTB, 2, 1); // Command mode; CS = 1
}

// Send Data Macro
void Send_Data(unsigned char cmd) {
  PORTB = SetBit(PORTB, 2, 0); // Command mode; CS = 0
  PORTB = SetBit(PORTB, 1, 1); // Data mode; A0 = 1
  SPI_SEND(cmd);
  PORTB = SetBit(PORTB, 2, 1); // Command mode; CS = 1
}

// Hardware Reset
void HardwareReset() {
  PORTB = SetBit(PORTB, 0, 0); // RESET pin
  _delay_ms(200);
  PORTB = SetBit(PORTB, 0, 1);
  _delay_ms(200);
}

// Invoke CASET
void columnSet(void) {
  Send_Command(CASET);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(MAX_X);
}

// Invoke RASET
void rowSet(void) {
  Send_Command(RASET);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(MAX_Y);
}

// Function to set the address window
void setAddrWindow(int x0, int y0, int x1, int y1) {
  Send_Command(CASET); // CASET (Column Address Set)
  Send_Data(0x00);     // High byte of x0
  Send_Data(x0);       // Low byte of x0
  Send_Data(0x00);     // High byte of x1
  Send_Data(x1);       // Low byte of x1

  Send_Command(RASET); // RASET (Row Address Set)
  Send_Data(0x00);     // High byte of y0
  Send_Data(y0);       // Low byte of y0
  Send_Data(0x00);     // High byte of y1
  Send_Data(y1);       // Low byte of y1

  Send_Command(0x2C); // RAMWR (Memory Write)
}

// Initialize ST7735
void ST7735_init(void) {
  HardwareReset();
  Send_Command(SWRESET); // Software reset
  _delay_ms(150);
  Send_Command(SLPOUT); // Sleep out
  _delay_ms(200);
  Send_Command(COLMOD); // Set color mode
  Send_Data(0x05);      // 16-bit color. TODO: 12-bit
  _delay_ms(10);
  Send_Command(DISPON); // Display on
  _delay_ms(200);
}

// Function to send 16-bit color data and clear the screen with that color
// Common Colors in RGB565:
// White - 0xFFFF
// Red -   0xF800
// Orange - 0xFC00
// Yellow - 0xFFE0
// Green - 0x07E0
// Cyan -  0x07FF
// Blue -  0x001F
// Purple - 0xF81F
// Magenta - 0xF81F
void Screen(int color) {
  // Set the address window to the full screen
  setAddrWindow(0, 0, MAX_X, MAX_Y);

  // Fill the screen with the specified color
  for (unsigned int i = 0; i < MAX_X * MAX_Y; i++) {
    Send_Data(color >> 8);   // Send high byte
    Send_Data(color & 0xFF); // Send low byte
  }
}

void AddressBox(short Xi, short Yi, short Xf, short Yf) {
  Send_Command(CASET);
  Send_Data(Xi >> 8);   // High 8 bits of initial X
  Send_Data(Xi & 0xFF); // Low 8 bits of initial X
  Send_Data(Xf >> 8);   // High 8 bits of ending X
  Send_Data(Xf & 0xFF); // Low 8 bits of ending X
  Send_Command(RASET);
  Send_Data(Yi >> 8);   // High 8 bits of initial Y
  Send_Data(Yi & 0xFF); // Low 8 bits of initial Y
  Send_Data(Yf >> 8);   // High 8 bits of ending Y
  Send_Data(Yf & 0xFF); // Low 8 bits of ending Y
  Send_Command(RAMWR);
}

void Pixel(short x, short y, short color) {
  AddressBox(x, y, x, y);
  Send_Data(color >> 8);
  Send_Data(color & 0xFF);
}

void Box(short x, short y, short w, short h, short color) {
  for (int i = 0; i < w; i++) {
    Pixel(x + i, y, color);
    Pixel(x + i, y + h - 1, color);
  }

  for (int i = 0; i < h; i++) {
    Pixel(x, y + i, color);
    Pixel(x + w - 1, y + i, color);
  }
}
void fillBox(short x, short y, short w, short h, short color) {
  for (int i = 0; i < w; i++) {   // Iterate over the width
    for (int j = 0; j < h; j++) { // Iterate over the height
      Pixel(x + i, y + j, color); // Set the color of each pixel
    }
  }
}

#endif // ST7735_H
