CFLAGS+=-g -O0

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)

ifeq ($(OS),Windows_NT)
EXT=.exe
endif
EXES=$(SRCS:.c=$(EXT))

%$(EXT): %.o
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

OPTIM_LEVEL=0
CFLAGS+=-g
CFLAGS+=-Wall -Werror -pedantic
CFLAGS+=-O$(OPTIM_LEVEL)
CFLAGS+=$(CFLAGS_EXTRA)
LDLIBS+=-lm

all: $(SUBDIRS) $(EXES)

clean: $(SUBDIRS)
	rm -f $(OBJS) $(EXES)

cleaner: $(SUBDIRS) clean
	[ -z "$(DEPS)" ] || rm -f $(DEPS)
	rm -f core

# automatically generate dependency rules
%.d: %.c
		$(CC) $(CCFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.c=.o)" "$<"

# -MF  write the generated dependency rule to a file
# -MG  assume missing headers will be generated and don't stop with an error
# -MM  generate dependency rule for prerequisite, skipping system headers
# -MP  add phony target for each header to prevent errors when header is missing
# -MT  add a target to the generated dependency
-include $(DEPS)

# Specific rules
rotate$(EXT): LDLIBS+=-lm
rotate.o: CFLAGS+=-D_USE_MATH_DEFINES
