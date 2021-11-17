##
# Project Title
#
# @file
# @version 0.1
.PHONY : build clean simple-test

build/osrm-batch-app: $(wildcard src/*.cpp) src/osrm_batch_app.hpp
	mkdir -p build && cd build && rm -rf * && cmake .. && cmake --build .

clean:
	rm -rf build

simple-test: build/osrm-batch-app
	LD_LIBRARY_PATH=/usr/local/lib/ ./build/osrm-batch-app /home/cgr/OSM/austria/austria.osrm



# end
