CC = g++

funcNames = Log2Small

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../../helper/ -I../../include $^ -lm -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
