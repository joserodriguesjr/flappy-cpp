add_executable(flappy)

# pico_generate_pio_header(flappy ${CMAKE_CURRENT_LIST_DIR}/st7789_lcd.pio)

target_sources(flappy PRIVATE main.cpp st7789.c)
target_link_libraries(flappy PRIVATE pico_stdio pico_stdlib hardware_spi hardware_gpio)

pico_add_extra_outputs(flappy)

# add url via pico_set_program_url
# example_auto_set_url(flappy)
