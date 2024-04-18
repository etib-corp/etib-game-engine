mkdir -p build
cd build
cmake ..
cmake --build . $1 # $1 is got passing "-- -j" from the command line