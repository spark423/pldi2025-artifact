CC = gcc

funcs = cosf coshf cospif expf exp2f exp10f logf log2f log10f sinf sinhf sinpif \
	cosf_rne coshf_rne cospif_rne expf_rne exp2f_rne exp10f_rne logf_rne log2f_rne log10f_rne sinf_rne sinhf_rne sinpif_rne

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -I../ -I../../helper -I../../include  $^ ../../libm/libm.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf *.o $(funcs) *~ 
