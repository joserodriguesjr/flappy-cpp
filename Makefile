run:
	./pc/flappy

clean-pc:
	rm -rf pc/

build-pc-debug:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Desktop-Debug -S . -B pc && cmake --build pc

build-pc-release:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Desktop-Release -S . -B pc && cmake --build pc

clean-esp32:
	idf.py clean

fullclean-esp32:
	idf.py fullclean

build-esp32-debug:
	idf.py -DPLATFORM=Esp32 -DCMAKE_BUILD_TYPE=Esp32-Debug build 

build-esp32-release:
	idf.py -DPLATFORM=Esp32 -DCMAKE_BUILD_TYPE=Esp32-Release build 

build-pico:
	cmake -S platform/pico -B platform/pico/build && cmake --build platform/pico/build

_load-compile-commands: # If clangd cant find headers, run this command
	cp pc/compile_commands.json ./compile_commands.json