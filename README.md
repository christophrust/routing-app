# osrm-batch-app

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


## Build osrm-batch-app

``` sh
git clone git@github.com:christophrust/osrm-batch-app.git

cd osrm-batch-app
make build
```



## API
