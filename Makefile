run:
	./desktop/flappy

clean-pc:
	rm -rf desktop/

build-pc-debug:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Desktop-Debug -S . -B desktop && cmake --build desktop

build-pc-release:
	cmake -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Desktop-Release -S . -B desktop && cmake --build desktop

clean-esp32:
	idf.py clean

fullclean-esp32:
	idf.py fullclean

build-esp32-debug:
	idf.py DPLATFORM=Esp32 -DCMAKE_BUILD_TYPE=Esp32-Debug build 

build-esp32-release:
	idf.py DPLATFORM=Esp32 -DCMAKE_BUILD_TYPE=Esp32-Release build 

_load-compile-commands: # If clangd cant find headers, run this command
	cp desktop/compile_commands.json ./compile_commands.json