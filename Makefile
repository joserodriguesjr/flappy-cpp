clean:
	rm -rf desktop/

run:
	./desktop/flappy

build-debug:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Debug -S . -B desktop && cmake --build desktop

build-release:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Release -S . -B desktop && cmake --build desktop

build-esp32:
	idf.py build

clean-esp32:
	idf.py fullclean

_load-compile-commands: # If clangd cant find headers, run this command
	cp desktop/compile_commands.json ./compile_commands.json