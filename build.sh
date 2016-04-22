#! /bin/sh -e
cd 'src'
$CXX -std=c++11 -O3 -W -Wall -Werror $CXXFLAGS mask.cpp -o mask.o -c
$CXX -std=c++11 -O3 -W -Wall -Werror $CXXFLAGS table.cpp -o table.o -c
$CXX -std=c++11 -O3 -W -Wall -Werror $CXXFLAGS vector.cpp -o vector.o -c
ar crs lsh.a mask.o table.o vector.o
cd '../test'
$CXX -std=c++11 -O3 -W -Wall -Werror $CXXFLAGS mask.cpp -o mask.o ../src/lsh.a
$CXX -std=c++11 -O3 -W -Wall -Werror $CXXFLAGS vector.cpp -o vector.o ../src/lsh.a
./mask.o
./vector.o
