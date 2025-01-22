#include "pico/stdlib.h"
#include <stdio.h>

int main() {
  setup_default_uart();
  printf("hello, world\n");
  return 0;
}
