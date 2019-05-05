
# Installing and using library 

Clone library
```git clone https://github.com/TomasSeniut/HPBB.git```

Create build directories
~~~
mkdir HPBB/build
mkdir HPBB/HPBB/build
~~~

Build and install library locally
~~~
cd HPBB/HPBB/build
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ../
make
make install
~~~

Building examples
~~~
cd examples/TravelingSalesman
mkdir build
cd build 
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ../
make
~~~


Running example
~~~
mpirun -np 2 TravelingSalesman ../../tsp_data/tsp_20.out
~~~