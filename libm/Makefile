all: libm.a

CC = gcc

libmfiles = cosf coshf cospif expf exp2f exp10f logf log2f log10f sinf sinhf sinpif	\
	    cosf_fma coshf_fma cospif_fma expf_fma exp2f_fma exp10f_fma logf_fma log2f_fma log10f_fma sinf_fma sinhf_fma sinpif_fma	\
	    cosf_rz coshf_rz cospif_rz expf_rz exp2f_rz exp10f_rz logf_rz log2f_rz log10f_rz sinf_rz sinhf_rz sinpif_rz	\
	    cosf_og coshf_og cospif_og expf_og exp2f_og exp10f_og logf_og log2f_og log10f_og sinf_og sinhf_og sinpif_og \
	    cr_cosf cr_coshf cr_cospif cr_expf cr_exp2f cr_exp10f cr_logf cr_log2f cr_log10f cr_sinf cr_sinhf cr_sinpif

libmsrcdir = .
libmobjdir = obj

libmsrc = $(patsubst %, $(libmsrcdir)/%.c, $(libmfiles))
libmobj = $(patsubst %, $(libmobjdir)/%.o, $(libmfiles))

$(libmobjdir)/%.o: $(libmsrcdir)/%.c
	@mkdir -p $(libmobjdir)
	$(CC) -O3 -march=native -frounding-math -fsignaling-nans -I../include -W -Wall -c $^  -o $@

libm.a: $(libmobj)
	ar rc $@ $^

clean:
	rm -rf  obj *~ libm.a
