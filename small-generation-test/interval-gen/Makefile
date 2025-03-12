CC = g++

FLAGS  = -lmpfr -lgmp

all: LogSmall-RLIBM  LogSmall-RI-Outputs LogSmall-RI-Input-Bounds

LogSmall-RLIBM: LogSmall.cpp
	$(CC) -O3 -frounding-math -I../../helper -I../../include LogSmall.cpp -o LogSmall-RLIBM $(FLAGS)

LogSmall-RI-Outputs: LogSmall.cpp
	$(CC) -O3 -frounding-math -DRNDZ -I../../helper -I../../include LogSmall.cpp -o LogSmall-RI-Outputs $(FLAGS)

LogSmall-RI-Input-Bounds: LogSmall.cpp
	$(CC) -O3 -frounding-math -DRNDZ -DMULTI -I../../helper -I../../include LogSmall.cpp -o LogSmall-RI-Input-Bounds $(FLAGS)

clean:
	rm -rf LogSmall-RLIBM LogSmall-RI-Outputs LogSmall-RI-Input-Bounds
