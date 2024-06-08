// #include <stdio.h>
// #include <math.h>

// #include "hardware/pio.h"
// #include "hardware/gpio.h"
// #include "hardware/interp.h"

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "st7789.hpp"
#include <cstdlib>
// #include <stdlib.h>

// lcd configuration
const struct st7789_config lcd_config = {
    .spi = PICO_DEFAULT_SPI_INSTANCE,
    .gpio_din = 3,
    .gpio_clk = 2,
    .gpio_cs = 5,
    .gpio_dc = 1,
    .gpio_rst = 0,
    .gpio_bl = 4,
};

#define LCD_WIDTH 240
#define LCD_HEIGHT 320

uint16_t row_pixels[LCD_WIDTH];

int main() {
  // stdio_init_all();

  // // initialize the lcd
  // st7789_init(&lcd_config, lcd_width, lcd_height);

  // while (1) {
  //     // make screen black
  //     st7789_fill(0x0000);

  //     // wait 1 second
  //     sleep_ms(1000);

  //     // make screen white
  //     st7789_fill(0xffff);

  //     // wait 1 second
  //     sleep_ms(1000);
  // }

  // initialize the lcd
  st7789_init(&lcd_config, LCD_WIDTH, LCD_HEIGHT);

  // make screen black
  st7789_fill(0x0000);

  while (1) {
    // create a random y and color value
    int rand_y = rand() % LCD_HEIGHT;
    uint16_t rand_color = rand() % 0xffff;

    // move the cursor to the y position
    st7789_set_cursor(0, rand_y);

    // set the row pixels buffer to the color value
    for (int i = 0; i < LCD_WIDTH; i++) {
      row_pixels[i] = rand_color;
    }

    // write the row pixel values
    st7789_write(row_pixels, sizeof(row_pixels));
  }
}
