##
# Project Title
#
# @file
# @version 0.1
build:
	mkdir -p build && cd build && rm -rf * && cmake .. && cmake --build .

clean:
	rm -rf build


simple-test: build
	LD_LIBRARY_PATH=/usr/local/lib/ ./build/osrm-batch-app /home/cgr/OSM/austria/austria.osrm



# end
