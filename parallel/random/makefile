# git root directory

ROOTDIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))/

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  OS := linux
else ifeq ($(UNAME), Darwin)
  OS := mac
endif

ifeq (, $(shell which jemalloc-config))
JEMALLOC =
else
JEMALLOCLD = $(shell jemalloc-config --libdir)
JEMALLOC = -L$(JEMALLOCLD) -ljemalloc
endif

# Always compile with LONG (note that timings on small graphs may be a bit
# faster w/o this flag).
INTT = -DLONG

ifdef EDGELONG
INTE = -DEDGELONG
endif

OPT = -O3 -DNDEBUG
#OPT = -O2 -g

CFLAGS = \
	-U_FORTIFY_SOURCE \
	'-D__DATE__="redacted"' \
	'-D__TIMESTAMP__="redacted"' \
	'-D__TIME__="redacted"' \
	-fno-omit-frame-pointer \
	-fstack-protector \
	-fPIC \
	-Wall \
	-Wextra \
	-Wcast-qual \
	-Wno-builtin-macro-redefined \
	-Wno-unused-parameter \
	-Wpointer-arith \
	-Wvla \
	-std=c++17 \
	-march=native \
	-mcx16 \
	$(OPT) \
	$(INTT) \
	$(INTE) \
	$(CONCEPTS) \
	-DAMORTIZEDPD \
	-DUSEMALLOC
# Add GCC-specific and Clang-specific flags
ifeq ($(OS), linux)
  CFLAGS += \
	-Wno-free-nonheap-object \
	-Wunused-but-set-parameter
else ifeq ($(OS), mac)
  CFLAGS += \
	-Wself-assign \
	-Wthread-safety
endif

OMPFLAGS = -DPARLAY_OPENMP -fopenmp
CILKFLAGS = -DPARLAY_CILK -fopencilk
HGFLAGS = -pthread
SERIALFLAGS = -DPARLAY_SEQUENTIAL

# CILK:= 1

# CC = /home/sualehasif/code/opencilk/opencilk-project/build/bin/clang++
# PFLAGS = $(CILKFLAGS)
# LFLAGS = -lcilkrts

ifdef CLANG
CC = clang++
PFLAGS = $(CILKFLAGS)
else ifdef CILK
CC = /home/sualehasif/code/opencilk/opencilk-project/build/bin/clang++
PFLAGS = $(CILKFLAGS)
LFLAGS = -fopencilk
else ifdef OPENMP
CC = g++
PFLAGS = $(OMPFLAGS)
LFLAGS = -fopenmp
else ifdef HOMEGROWN
CC = g++
PFLAGS = $(HGFLAGS)
else ifdef SERIAL
CC = g++
PFLAGS = $(SERIALFLAGS)
else # default is homegrown
CC = g++
PFLAGS = $(HGFLAGS)
endif

ifeq ($(OS), linux)
  LINKER_START_GROUP := -Wl,--start-group
  LINKER_END_GROUP := -Wl,--end-group
else ifeq ($(OS), mac)
  # macOS's default linker doesn't use the --start-group and --end-group flags.
  LINKER_START_GROUP :=
  LINKER_END_GROUP :=
endif


# ----------------------------------------------------------------------------------------------------------


ALL= metagraph

INCLUDE_DIRS = -I$(ROOTDIR) -I$(ROOTDIR)external/parlaylib/include/

.DEFAULT_GOAL := all

all: $(ALL)

LIGRA_OBJS = $(wildcard $(ROOTDIR)bin/gbbs/*.a)
LIGRA_ENCODING_OBJS = $(wildcard $(ROOTDIR)bin/gbbs/encodings/*.a)

ALL_OBJS = $(LIGRA_OBJS) $(LIGRA_ENCODING_OBJS) $(OTHER_OBJS)

LIGRA_OBJS_CLEAN = $(wildcard $(ROOTDIR)bin/gbbs/*.o)
LIGRA_ENCODING_OBJS_CLEAN = $(wildcard $(ROOTDIR)bin/gbbs/encodings/*.o)

ALL_OBJS_CLEAN = $(LIGRA_OBJS_CLEAN) $(LIGRA_ENCODING_OBJS_CLEAN) $(OTHER_OBJS_CLEAN)

#comma = ,
#ALL_OBJS_SUBST = $(subst |, ,$(addprefix -Wl$(comma)--start-lib|, $(addsuffix |-Wl$(comma)--end-lib, $(ALL_OBJS))))

other : $(OTHER)

gbbs :
	make -C $(ROOTDIR)gbbs/

gbbs_encodings :
	make -C $(ROOTDIR)gbbs/encodings/

% : %.cc gbbs gbbs_encodings other
	$(CC) $(INCLUDE_DIRS) $(OTHERFLAGS) $(CFLAGS) $(PFLAGS) -o $@ $< $(LINKER_START_GROUP) $(ALL_OBJS) $(LINKER_END_GROUP) -pthread $(LFLAGS)
#-Wl,--whole-archive -lpthread -Wl,--no-whole-archive -Wl,-S -Wl,-no-as-needed -Wl,-z,relro,-z,now -lstdc++ -fuse-ld=gold

.PHONY : clean

clean :
	rm -f *.o $(ALL) $(ALL_OBJS) $(ALL_OBJS_CLEAN)