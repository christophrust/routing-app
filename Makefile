##
# Project Title
#
# @file
# @version 0.1
.PHONY : build clean simple-test asio-test

build/osrm-batch-app: $(wildcard src/*.cpp) src/osrm_batch_app.hpp
	mkdir -p build && cd build && rm -rf * && cmake .. && cmake --build .

clean:
	rm -rf build

simple-test: build/osrm-batch-app
	LD_LIBRARY_PATH=/usr/local/lib/ ./build/osrm-batch-app /home/cgr/OSM/austria/austria.osrm

asio-server: src/asio-test-server.cpp
	cd src && g++ -o ../asio-server -std=c++14 -pthread -I -Wall asio-test-server.cpp

asio-client: src/asio-test-client.cpp
	cd src && g++ -o ../asio-client -std=c++14 -pthread -I -Wall asio-test-client.cpp

asio-test: asio-server asio-client
	./asio-server &
	./asio-client
# end
