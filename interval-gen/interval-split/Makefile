CC = g++

FLAGS  = -lmpfr -lgmp

all: Interval-Split

Interval-Split: interval_split.cpp
	$(CC) -O3 -I../../helper -I../../include interval_split.cpp -o Interval-Split $(FLAGS)

clean:
	rm -rf Interval-Split *~
