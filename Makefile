##
# Project Title
#
# @file
# @version 0.1
.PHONY : build clean simple-test asio-test

build/routing_app: $(wildcard src/*.cpp) src/routing_app.hpp
	mkdir -p build && cd build && rm -rf * && cmake .. && cmake --build .

clean:
	rm -rf build

simple-test: build/routing-app
	./build/routing-app /home/cgr/OSM/austria/austria.osrm 8081

# end
