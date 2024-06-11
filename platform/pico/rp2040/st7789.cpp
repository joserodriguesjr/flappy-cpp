/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "st7789.hpp"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <cstdint>
#include <cstring>
#include <string.h>

/**
 * @brief command data type definition
 */
#define ST7789_CMD 0  /**< command type */
#define ST7789_DATA 1 /**< data type */

/**
 * @brief chip command definition
 */
#define ST7789_CMD_NOP 0x00     /**< no operation command */
#define ST7789_CMD_SWRESET 0x01 /**< software reset command */
#define ST7789_CMD_SLPIN 0x10   /**< sleep in command */
#define ST7789_CMD_SLPOUT 0x11  /**< sleep out command */
#define ST7789_CMD_PTLON 0x12   /**< partial mode on command */
#define ST7789_CMD_NORON 0x13   /**< normal display mode on command */
#define ST7789_CMD_INVOFF 0x20  /**< display inversion off command */
#define ST7789_CMD_INVON 0x21   /**< display inversion on command */
#define ST7789_CMD_GAMSET 0x26  /**< display inversion set command */
#define ST7789_CMD_DISPOFF 0x28 /**< display off command */
#define ST7789_CMD_DISPON 0x29  /**< display on command */
#define ST7789_CMD_CASET 0x2A   /**< column address set command */
#define ST7789_CMD_RASET 0x2B   /**< row address set command */
#define ST7789_CMD_RAMWR 0x2C   /**< memory write command */
#define ST7789_CMD_PTLAR 0x30   /**< partial start/end address set command */
#define ST7789_CMD_VSCRDEF 0x33 /**< vertical scrolling definition command */
#define ST7789_CMD_TEOFF 0x34   /**< tearing effect line off command */
#define ST7789_CMD_TEON 0x35    /**< tearing effect line on command */
#define ST7789_CMD_MADCTL 0x36  /**< memory data access control command */
#define ST7789_CMD_VSCRSADD                                                    \
  0x37                          /**< vertical scrolling start address command */
#define ST7789_CMD_IDMOFF 0x38  /**< idle mode off command */
#define ST7789_CMD_IDMON 0x39   /**< idle mode on command */
#define ST7789_CMD_COLMOD 0x3A  /**< interface pixel format command */
#define ST7789_CMD_RAMWRC 0x3C  /**< memory write continue command */
#define ST7789_CMD_TESCAN 0x44  /**< set tear scanline command */
#define ST7789_CMD_WRDISBV 0x51 /**< write display brightness command */
#define ST7789_CMD_WRCTRLD 0x53 /**< write CTRL display command */
#define ST7789_CMD_WRCACE                                                      \
  0x55 /**< write content adaptive brightness control and color enhancement    \
          command */
#define ST7789_CMD_WRCABCMB 0x5E /**< write CABC minimum brightness command */
#define ST7789_CMD_RAMCTRL 0xB0  /**< ram control command */
#define ST7789_CMD_RGBCTRL 0xB1  /**< rgb control command */
#define ST7789_CMD_PORCTRL 0xB2  /**< porch control command */
#define ST7789_CMD_FRCTRL1 0xB3  /**< frame rate control 1 command */
#define ST7789_CMD_PARCTRL 0xB5  /**< partial mode control command */
#define ST7789_CMD_GCTRL 0xB7    /**< gate control command */
#define ST7789_CMD_GTADJ 0xB8    /**< gate on timing adjustment command */
#define ST7789_CMD_DGMEN 0xBA    /**< digital gamma enable command */
#define ST7789_CMD_VCOMS 0xBB    /**< vcoms setting command */
#define ST7789_CMD_LCMCTRL 0xC0  /**< lcm control command */
#define ST7789_CMD_IDSET 0xC1    /**< id setting command */
#define ST7789_CMD_VDVVRHEN 0xC2 /**< vdv and vrh command enable command */
#define ST7789_CMD_VRHS 0xC3     /**< vrh set command */
#define ST7789_CMD_VDVSET 0xC4   /**< vdv setting command */
#define ST7789_CMD_VCMOFSET 0xC5 /**< vcoms offset set command */
#define ST7789_CMD_FRCTR2 0xC6   /**< fr control 2 command */
#define ST7789_CMD_CABCCTRL 0xC7 /**< cabc control command */
#define ST7789_CMD_REGSEL1 0xC8  /**< register value selection1 command */
#define ST7789_CMD_REGSEL2 0xCA  /**< register value selection2 command */
#define ST7789_CMD_PWMFRSEL 0xCC /**< pwm frequency selection command */
#define ST7789_CMD_PWCTRL1 0xD0  /**< power control 1 command */
#define ST7789_CMD_VAPVANEN 0xD2 /**< enable vap/van signal output command */
#define ST7789_CMD_CMD2EN 0xDF   /**< command 2 enable command */
#define ST7789_CMD_PVGAMCTRL                                                   \
  0xE0 /**< positive voltage gamma control command                             \
        */
#define ST7789_CMD_NVGAMCTRL                                                   \
  0xE1 /**< negative voltage gamma control command                             \
        */
#define ST7789_CMD_DGMLUTR                                                     \
  0xE2 /**< digital gamma look-up table for red command */
#define ST7789_CMD_DGMLUTB                                                     \
  0xE3 /**< digital gamma look-up table for blue command */
#define ST7789_CMD_GATECTRL 0xE4 /**< gate control command */
#define ST7789_CMD_SPI2EN 0xE7   /**< spi2 command */
#define ST7789_CMD_PWCTRL2 0xE8  /**< power control 2 command */
#define ST7789_CMD_EQCTRL 0xE9   /**< equalize time control command */
#define ST7789_CMD_PROMCTRL 0xEC /**< program control command */
#define ST7789_CMD_PROMEN 0xFA   /**< program mode enable command */
#define ST7789_CMD_NVMSET 0xFC   /**< nvm setting command */
#define ST7789_CMD_PROMACT 0xFE  /**< program action command */

static struct st7789_config st7789_cfg;
static uint16_t st7789_width;
static uint16_t st7789_height;
static bool st7789_data_mode = false;

static void st7789_cmd(uint8_t cmd, const uint8_t *data, size_t len) {
  if (st7789_cfg.gpio_cs > -1) {
    spi_set_format(st7789_cfg.spi, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
  } else {
    spi_set_format(st7789_cfg.spi, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
  }
  st7789_data_mode = false;

  sleep_us(1);
  if (st7789_cfg.gpio_cs > -1) {
    gpio_put(st7789_cfg.gpio_cs, 0);
  }
  gpio_put(st7789_cfg.gpio_dc, 0);
  sleep_us(1);

  spi_write_blocking(st7789_cfg.spi, &cmd, sizeof(cmd));

  if (len) {
    sleep_us(1);
    gpio_put(st7789_cfg.gpio_dc, 1);
    sleep_us(1);

    spi_write_blocking(st7789_cfg.spi, data, len);
  }

  sleep_us(1);
  if (st7789_cfg.gpio_cs > -1) {
    gpio_put(st7789_cfg.gpio_cs, 1);
  }
  gpio_put(st7789_cfg.gpio_dc, 1);
  sleep_us(1);
}

void st7789_caset(uint16_t xs, uint16_t xe) {
  uint8_t data[] = {
      static_cast<uint8_t>(xs >> 8),
      static_cast<uint8_t>(xs & 0xff),
      static_cast<uint8_t>(xe >> 8),
      static_cast<uint8_t>(xe & 0xff),
  };

  // CASET (2Ah): Column Address Set
  st7789_cmd(ST7789_CMD_CASET, data, sizeof(data));
}

void st7789_raset(uint16_t ys, uint16_t ye) {
  uint8_t data[] = {
      static_cast<uint8_t>(ys >> 8),
      static_cast<uint8_t>(ys & 0xff),
      static_cast<uint8_t>(ye >> 8),
      static_cast<uint8_t>(ye & 0xff),
  };

  // RASET (2Bh): Row Address Set
  st7789_cmd(ST7789_CMD_RASET, data, sizeof(data));
}

void st7789_init(const struct st7789_config *config, uint16_t width,
                 uint16_t height) {
  memcpy(&st7789_cfg, config, sizeof(st7789_cfg));
  st7789_width = width;
  st7789_height = height;

  spi_init(st7789_cfg.spi, 125 * 1000 * 1000);
  if (st7789_cfg.gpio_cs > -1) {
    spi_set_format(st7789_cfg.spi, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
  } else {
    spi_set_format(st7789_cfg.spi, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
  }

  gpio_set_function(st7789_cfg.gpio_din, GPIO_FUNC_SPI);
  gpio_set_function(st7789_cfg.gpio_clk, GPIO_FUNC_SPI);

  if (st7789_cfg.gpio_cs > -1) {
    gpio_init(st7789_cfg.gpio_cs);
  }
  gpio_init(st7789_cfg.gpio_dc);
  gpio_init(st7789_cfg.gpio_rst);
  gpio_init(st7789_cfg.gpio_bl);

  if (st7789_cfg.gpio_cs > -1) {
    gpio_set_dir(st7789_cfg.gpio_cs, GPIO_OUT);
  }
  gpio_set_dir(st7789_cfg.gpio_dc, GPIO_OUT);
  gpio_set_dir(st7789_cfg.gpio_rst, GPIO_OUT);
  gpio_set_dir(st7789_cfg.gpio_bl, GPIO_OUT);

  if (st7789_cfg.gpio_cs > -1) {
    gpio_put(st7789_cfg.gpio_cs, 1);
  }
  gpio_put(st7789_cfg.gpio_dc, 1);
  gpio_put(st7789_cfg.gpio_rst, 1);
  sleep_ms(100);

  // SWRESET (01h): Software Reset
  st7789_cmd(ST7789_CMD_SWRESET, NULL, 0);
  sleep_ms(150);

  // SLPOUT (11h): Sleep Out
  st7789_cmd(ST7789_CMD_SLPOUT, NULL, 0);
  sleep_ms(50);

  // COLMOD (3Ah): Interface Pixel Format
  // - RGB interface color format     = 65K of RGB interface
  // - Control interface color format = 16bit/pixel
  uint8_t data1[] = {0x55};
  st7789_cmd(ST7789_CMD_COLMOD, data1, 1);
  sleep_ms(10);

  // MADCTL (36h): Memory Data Access Control
  // - Page Address Order            = Top to Bottom
  // - Column Address Order          = Left to Right
  // - Page/Column Order             = Normal Mode
  // - Line Address Order            = LCD Refresh Top to Bottom
  // - RGB/BGR Order                 = RGB
  // - Display Data Latch Data Order = LCD Refresh Left to Right
  uint8_t data2[] = {0x00};
  st7789_cmd(ST7789_CMD_MADCTL, data2, 1);

  st7789_caset(0, width);
  st7789_raset(0, height);

  // INVON (21h): Display Inversion On
  st7789_cmd(ST7789_CMD_INVON, NULL, 0);
  sleep_ms(10);

  // NORON (13h): Normal Display Mode On
  st7789_cmd(ST7789_CMD_NORON, NULL, 0);
  sleep_ms(10);

  // DISPON (29h): Display On
  st7789_cmd(ST7789_CMD_DISPON, NULL, 0);
  sleep_ms(10);

  gpio_put(st7789_cfg.gpio_bl, 1);
}

void st7789_ramwr() {
  sleep_us(1);
  if (st7789_cfg.gpio_cs > -1) {
    gpio_put(st7789_cfg.gpio_cs, 0);
  }
  gpio_put(st7789_cfg.gpio_dc, 0);
  sleep_us(1);

  // RAMWR (2Ch): Memory Write
  uint8_t cmd = ST7789_CMD_RAMWR;
  spi_write_blocking(st7789_cfg.spi, &cmd, sizeof(cmd));

  sleep_us(1);
  if (st7789_cfg.gpio_cs > -1) {
    gpio_put(st7789_cfg.gpio_cs, 0);
  }
  gpio_put(st7789_cfg.gpio_dc, 1);
  sleep_us(1);
}

void st7789_write(const uint16_t *data, size_t len) {
  if (!st7789_data_mode) {
    st7789_ramwr();

    if (st7789_cfg.gpio_cs > -1) {
      spi_set_format(st7789_cfg.spi, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    } else {
      spi_set_format(st7789_cfg.spi, 16, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
    }

    st7789_data_mode = true;
  }

  // spi_write_blocking(st7789_cfg.spi, data, len);
  spi_write16_blocking(st7789_cfg.spi, data, len / 2);
}

// void st7789_fill(uint8_t pixel) {
//   int num_pixels = st7789_width * st7789_height;

//   st7789_set_cursor(0, 0, st7789_width, st7789_height);

//   for (int i = 0; i < num_pixels; i++) {
//     st7789_write(&pixel, sizeof(pixel));
//   }
// }
// void st7789_fill(uint8_t color) {
//   uint8_t data[st7789_width * st7789_height * 2];
//   for (int i = 0; i < st7789_width * st7789_height * 2; i += 2) {
//     data[i] = color;     // High byte of color
//     data[i + 1] = color; // Low byte of color
//   }

//   st7789_set_cursor(0, 0, st7789_width - 1, st7789_height - 1);
//   st7789_write(data, sizeof(data));
// }

void st7789_set_cursor(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) {
  st7789_caset(xs, xe);
  st7789_raset(ys, ye);
}

uint16_t back_buffer[240 * 320];

void st7789_draw_sprite(uint16_t x, uint16_t y, const uint16_t *sprite_data,
                        uint16_t sprite_width, uint16_t sprite_height) {
  // Draw the sprite onto the back buffer
  for (int j = 0; j < sprite_height; ++j) {
    for (int i = 0; i < sprite_width; ++i) {
      // Place the pixel from the sprite directly into the back buffer
      back_buffer[(y + j) * st7789_width + (x + i)] =
          sprite_data[j * sprite_width + i];
    }
  }
}

void st7789_update_display(uint16_t x, uint16_t y, const uint16_t *sprite_data,
                           uint16_t sprite_width, uint16_t sprite_height) {
  // Clear the back buffer (example: fill with black)
  memset(back_buffer, 0x0000, sizeof(back_buffer));

  // st7789_fill(BLACK);
  st7789_draw_sprite(x, y, sprite_data, sprite_width, sprite_height);

  // Write the entire back buffer to the display
  st7789_set_cursor(0, 0, st7789_width - 1, st7789_height - 1);
  st7789_write(back_buffer, sizeof(back_buffer));
}