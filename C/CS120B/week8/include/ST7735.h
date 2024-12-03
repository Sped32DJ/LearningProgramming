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
const unsigned int MAX_Y = 129; // Screen height

// Hardware Reset
void HardwareReset() {
  PORTD &= 0xFE; // setResetPinToLow
  _delay_ms(200);
  PORTD |= 0x01; // setResetPinToHigh
  _delay_ms(200);
}

// Invoke CASET
void columnSet(void) {
  Send_Command(0x2A);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(MAX_X);
}

// Invoke RASET
void rowSet(void) {
  Send_Command(0x2B);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(0x00);
  Send_Data(MAX_Y);
}

// Function to set the address window
void setAddrWindow(int x0, int y0, int x1, int y1) {
  Send_Command(0x2A); // CASET (Column Address Set)
  Send_Data(0x00);    // High byte of x0
  Send_Data(x0);      // Low byte of x0
  Send_Data(0x00);    // High byte of x1
  Send_Data(x1);      // Low byte of x1

  Send_Command(0x2B); // RASET (Row Address Set)
  Send_Data(0x00);    // High byte of y0
  Send_Data(y0);      // Low byte of y0
  Send_Data(0x00);    // High byte of y1
  Send_Data(y1);      // Low byte of y1

  Send_Command(0x2C); // RAMWR (Memory Write)
}

// Initialize ST7735
void ST7735_init(void) {
  HardwareReset();
  Send_Command(0x01); // Software reset
  _delay_ms(150);
  Send_Command(0x11); // Sleep out
  _delay_ms(200);
  Send_Command(0x3A); // Set color mode
  Send_Data(0x05);    // 16-bit color
  _delay_ms(10);
  Send_Command(0x29); // Display on
  _delay_ms(200);
}

// Function to send 16-bit color data and clear the screen with that color
// White - 0xFFFF
void Clear_Screen_With_Color(int color) {
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

// Personally written functions
void Screen(short color) {
  AddressBox(0, 0, 127, 127);
  for (int i = 0; i < 128 * 128; i++) {
    Send_Data(color >> 8);
    Send_Data(color & 0xFF);
  }
}

#endif // ST7735_H
