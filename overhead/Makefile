CC = gcc

funcs = ourlibm_cosf ourlibm_coshf ourlibm_cospif ourlibm_expf ourlibm_exp2f ourlibm_exp10f ourlibm_logf ourlibm_log2f ourlibm_log10f ourlibm_sinf ourlibm_sinhf ourlibm_sinpif \
	ourlibm_cosf_rz ourlibm_coshf_rz ourlibm_cospif_rz ourlibm_expf_rz ourlibm_exp2f_rz ourlibm_exp10f_rz ourlibm_logf_rz ourlibm_log2f_rz ourlibm_log10f_rz ourlibm_sinf_rz ourlibm_sinhf_rz ourlibm_sinpif_rz \
	rlibm_cosf rlibm_coshf rlibm_cospif rlibm_expf rlibm_exp2f rlibm_exp10f rlibm_logf rlibm_log2f rlibm_log10f rlibm_sinf rlibm_sinhf rlibm_sinpif

src = $(patsubst %, %.c, $(funcs))
obj = $(patsubst %, %, $(funcs))


all: $(obj)

%: %.c
	$(CC) -O3 -frounding-math -fsignaling-nans -I../include $^ ../libm/libm.a -lm -o $@

clean:
	rm -rf *.o $(funcs) *~ *.txt 
