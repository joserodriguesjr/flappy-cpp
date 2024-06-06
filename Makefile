clean:
	rm -rf build/

build-debug:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Debug -S . -B build && cmake --build build

build-release:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Release -S . -B build && cmake --build build

build-esp32:
	idf.py build

clean-esp32:
	idf.py fullclean

run:
	./build/flappy

_load-compile-commands: # If clangd cant find headers, run this command
	cp build/compile_commands.json ./compile_commands.json