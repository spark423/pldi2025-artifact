all: libm.a

CC = gcc

libmfiles = cosf coshf cospif expf exp2f exp10f logf log2f log10f sinf sinhf sinpif	\
	    cosf_fma coshf_fma cospif_fma expf_fma exp2f_fma exp10f_fma logf_fma log2f_fma log10f_fma sinf_fma sinhf_fma sinpif_fma	\
	    cosf_rz coshf_rz cospif_rz expf_rz exp2f_rz exp10f_rz logf_rz log2f_rz log10f_rz sinf_rz sinhf_rz sinpif_rz	\
	    rlibm_cosf rlibm_coshf rlibm_cospif rlibm_expf rlibm_exp2f rlibm_exp10f rlibm_logf rlibm_log2f rlibm_log10f rlibm_sinf rlibm_sinhf rlibm_sinpif \
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
