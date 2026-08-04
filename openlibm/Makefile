CFILES = common.c e_acos.c e_asin.c e_atan2.c e_exp.c e_fmod.c e_log.c \
	e_log10.c e_log2.c e_pow.c e_rem_pio2.c e_sqrt.c k_cos.c \
	k_rem_pio2.c k_sin.c k_tan.c s_atan.c s_ceil.c s_copysign.c \
	s_cos.c s_exp2.c s_expm1.c s_fabs.c s_floor.c s_fpclassify.c \
	s_frexp.c s_isfinite.c s_isinf.c s_isnan.c s_isnormal.c s_log1p.c \
	s_scalbn.c s_signbit.c s_sin.c s_tan.c
OFILES = $(CFILES:.c=.o)
VPATH = src
CFLAGS = $(BASE_CFLAGS) -std=c99 -fno-builtin -fno-strict-aliasing \
	-I../include -Iinclude -Iaarch64 -Isrc -DASSEMBLER -D__BSD_VISIBLE
LDFLAGS = -r

openlibm.o: $(OFILES)
	$(LD) $(LDFLAGS) $(OFILES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o 2> /dev/null || true
