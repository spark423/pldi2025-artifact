CC = gcc

funcs = cos cosh exp exp2 exp10 log log2 log10 sin sinh

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -I../ -I../../include $^ -lm -lmpfr -lgmp -o $@

clean:
	rm -rf *.o $(funcs) *~ 
