gcc -c cs.cpp
gcc -c mains.cpp
gcc -o server cs.o mains.o
./server