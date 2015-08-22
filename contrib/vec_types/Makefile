# contrib/vec_types/Makefile

MODULE_big = vec_types
OBJS = vset128.o vset256.o vset512.o
PGFILEDESC = "vec_types - aligned vector types"


ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/vec_types
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif

vset128.o: aset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DALIGNOF_VEC=16 -DVEC_PREFIX=Vec128 -DALLOC_MINBITS=4 \
		-DALLOCSET_NUM_FREELISTS=10 -c -o $@ $<

vset256.o: aset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DALIGNOF_VEC=32 -DVEC_PREFIX=Vec256 -DALLOC_MINBITS=5 \
		-DALLOCSET_NUM_FREELISTS=9 -c -o $@ $<

vset512.o: aset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DALIGNOF_VEC=64 -DVEC_PREFIX=Vec512 -DALLOC_MINBITS=6 \
		-DALLOCSET_NUM_FREELISTS=8 -c -o $@ $<
		
aset.o: aset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
