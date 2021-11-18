# routing-app

## Dependencies

``` sh
## install necessary dependencies
apt-get install wget git g++ cmake libboost-dev libboost-filesystem-dev libboost-thread-dev \
    libboost-system-dev libboost-regex-dev libxml2-dev libsparsehash-dev libbz2-dev \
    zlib1g-dev libzip-dev libgomp1 liblua5.3-dev \
    pkg-config libgdal-dev libboost-program-options-dev libboost-iostreams-dev \
    libboost-test-dev libtbb-dev libexpat1-dev

## download osrm source
wget https://github.com/Project-OSRM/osrm-backend/archive/v5.26.0.tar.gz
tar -xzf v5.26.0.tar.gz
mkdir -p osrm-backend-5.26.0/build

## build osrm
cd osrm-backend-5.26.0/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON && \
    cmake --build . && cmake --build . --target install
```


## Build routing-app

To build the application, run:
``` sh
git clone git@github.com:christophrust/routing-app.git

cd routing-app
make build/routing-app
```

## Run

If the build is successful and a OSM map has been prepared using `osrm-extract` and `osrm-contract`,
the application can be started via:

``` sh
./build/routing-app prepared-map.osrm 8080
```



## API


The communication with clients follows a very simple API:

The endpoint only accepts binary data. The first 16 bytes (size of one `size_t`) must hold
the size of the data body which directly follows in the stream. Hence, clients should implement something like

``` c++
// sending
boost::asio::write(socket, boost::asio::buffer(stream_size));
boost::asio::write(socket, boost::asio::buffer(data), ignored_error);
```

where `stream_size` is a `std::vector<size_t>` of length one and data the corresponding double data array.

The response is obtained by reading from the same connection, e.g.

``` c++
boost::asio::read(socket, boost::asio::buffer(data), ignored_error);
```
where `data` in the response must have the same length as in the sending request.

