CC = gcc

funcs = cosf coshf cospif expf exp2f exp10f logf log2f log10f sinf sinhf sinpif \
	cosf_rz coshf_rz cospif_rz expf_rz exp2f_rz exp10f_rz logf_rz log2f_rz log10f_rz sinf_rz sinhf_rz sinpif_rz

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -I../ -I../../helper -I../../include  $^ ../../libm/libm.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf *.o $(funcs) *~ 
