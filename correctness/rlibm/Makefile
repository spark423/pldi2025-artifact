CC = gcc

funcs = cosf coshf cospif expf exp2f exp10f logf log2f log10f sinf sinhf sinpif \
	cosf_rz coshf_rz cospif_rz expf_rz exp2f_rz exp10f_rz logf_rz log2f_rz log10f_rz sinf_rz sinhf_rz sinpif_rz \
	cosf_og coshf_og cospif_og expf_og exp2f_og exp10f_og logf_og log2f_og log10f_og sinf_og sinhf_og sinpif_og

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -I../ -I../../include  $^ ../../libm/libm.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf *.o $(funcs) *~ 
