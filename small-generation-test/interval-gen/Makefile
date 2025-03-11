CC = g++

FLAGS  = -lmpfr -lgmp

all:  LogSmall-RZ LogSmall-MULTI

LogSmall-RZ: LogSmall.cpp
	$(CC) -O3 -frounding-math -DRNDZ -I../../helper -I../../include LogSmall.cpp -o LogSmall-RZ $(FLAGS)

LogSmall-MULTI: LogSmall.cpp
	$(CC) -O3 -frounding-math -DRNDZ -DMULTI -I../../helper -I../../include LogSmall.cpp -o LogSmall-MULTI $(FLAGS)

clean:
	rm -rf *-RZ *-MULTI
