mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . $1 # $1 is got passing "-- -j" from the command line