DESKTOP_BUILD_DIR = platform/desktop/build
ESP32_BUILD_DIR = platform/esp32/build
PICO_BUILD_DIR = platform/pico/build

run:
	./$(DESKTOP_BUILD_DIR)/flappy

clean-desktop:
	rm -rf $(DESKTOP_BUILD_DIR)

build-desktop-debug:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Desktop-Debug -S . -B $(DESKTOP_BUILD_DIR) && cmake --build $(DESKTOP_BUILD_DIR)

build-desktop-release:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Desktop-Release -S . -B $(DESKTOP_BUILD_DIR) && cmake --build $(DESKTOP_BUILD_DIR)

clean-esp32:
	idf.py -B $(ESP32_BUILD_DIR) clean

fullclean-esp32:
	idf.py -B $(ESP32_BUILD_DIR) fullclean

build-esp32-debug:
	idf.py -B $(ESP32_BUILD_DIR) -DPLATFORM=Esp32 -DCMAKE_BUILD_TYPE=Esp32-Debug build 

build-esp32-release:
	idf.py -B $(ESP32_BUILD_DIR) -DPLATFORM=Esp32 -DCMAKE_BUILD_TYPE=Esp32-Release build 

build-pico:
	cmake -S platform/pico -B $(PICO_BUILD_DIR) && cmake --build $(PICO_BUILD_DIR)

_load-compile-commands: # If clangd cant find headers, run this command
	cp $(DESKTOP_BUILD_DIR)/compile_commands.json ./compile_commands.json