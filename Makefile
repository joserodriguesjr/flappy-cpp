# convert to sh

clean:
	rm -rf build/

build-debug:
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build && cmake --build build

build-release:
	cmake -DCMAKE_BUILD_TYPE=Release -S . -B build && cmake --build build

run:
	./build/app

test_core: # add -s to see successfull tests
	./build/core_tests

test_app: # add -s to see successfull tests
	./build/app_tests

_load-compile-commands: # If clangd cant find headers, run this command
	cp build/compile_commands.json ./compile_commands.json