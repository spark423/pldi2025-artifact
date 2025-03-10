CC = g++

FLAGS  = -lmpfr -lgmp

all:  Log2Small-RZ Log2Small-MULTI

Log2Small-RZ: Log2Small.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../../helper -I../../include Log2Small.cpp -o Log2Small-RZ $(FLAGS)

Log2Small-MULTI: Log2Small.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../../helper -I../../include Log2Small.cpp -o Log2Small-MULTI $(FLAGS)

clean:
	rm -rf *-RZ *-MULTI
