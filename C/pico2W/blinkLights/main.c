#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

int main() {
  const int G_PIN = 0;
  gpi_init(G_PIN);
  gpio_set_dir(G_PIN, GPIO_OUT);
  bool flash = 0;

  while (1) {
    flash != flash;
    GPIO_PUT(G_PIN, flash);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, flash);
    sleep_ms(250);
  }
}
