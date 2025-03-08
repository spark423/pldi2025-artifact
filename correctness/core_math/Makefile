CC = gcc

funcs = cr_cosf cr_coshf cr_cospif cr_expf cr_exp2f cr_exp10f cr_logf cr_log2f cr_log10f cr_sinf cr_sinhf cr_sinpif

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -I../ -I../../include  $^ ../../libm/libm.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf *.o $(funcs) *~ 
