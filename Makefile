CFLAGS+=-g -O0
all: identity scale rotate translate apply

identity: io.h m4f.h v3f.h
scale: io.h m4f.h v3f.h
rotate: io.h m4f.h v3f.h
translate: io.h m4f.h v3f.h
apply: io.h m4f.h v3f.h

rotate: LDLIBS+=-lm
rotate: CFLAGS+=-D_USE_MATH_DEFINES
