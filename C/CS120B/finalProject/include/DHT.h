#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#ifndef DHT_H
#define DHT_H

#define DHT_PIN PC3
#define DHT_DDR DDRC
#define DHT_PORT PORTC
#define DHT_PINC PINC

void DHT_Request() {
  DHT_DDR |= (1 << DHT_PIN);
  DHT_PORT &= ~(1 << DHT_PIN);
  _delay_ms(20);
  DHT_PORT |= (1 << DHT_PIN);
  _delay_us(40);
  DHT_DDR &= ~(1 << DHT_PIN);
}

short DHT_WaitForResponse() {
  _delay_us(40);
  // wait for low
  if (!(DHT_PINC & (1 << DHT_PIN))) {
    _delay_us(80);
    // wait for high
    if (DHT_PINC & (1 << DHT_PIN)) {
      _delay_us(80);
      return 1;
    }
  }
  return 0; // response failed
}

short DHT_ReadByte() {
  short byte = 0;
  for (short i = 0; i < 8; ++i) {
    // wait for high
    while (!(DHT_PINC & (1 << DHT_PIN)))
      ;
    _delay_us(30);
    if (DHT_PINC & (1 << DHT_PIN)) {
      byte |= (1 << (7 - i)); // read 1
    }
    // wait for low
    while (DHT_PINC & (1 << DHT_PIN))
      ;
  }
  return byte;
}

short humidity, temperature;
void updateTempHum() {
  short humidity_int, humidity_dec, temp_int, temp_dec, checksum;
  DHT_Request();
  if (DHT_WaitForResponse()) {
    humidity = DHT_ReadByte();
    humidity_dec = DHT_ReadByte();
    temp_int = DHT_ReadByte();
    temp_dec = DHT_ReadByte();
    checksum = DHT_ReadByte();
    if (checksum == (humidity_int + humidity_dec + temp_int + temp_dec)) {

      temperature = temp_int;
      humidity = humidity_int;
    }
  }
}

short DHT_read(int pin, float *temperature, float *humidity);

#endif
