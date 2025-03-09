CC = gcc

funcs = cosf coshf cospif expf exp2f exp10f logf log2f log10f sinf sinhf sinpif

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -I../ -I../../include  $^ ../../libm/libm.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf *.o $(funcs) *~ 
