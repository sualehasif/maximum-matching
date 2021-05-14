# git root directory
ROOTDIR = $(strip $(shell git rev-parse --show-cdup))/parallel/

include $(ROOTDIR)makefile.variables

ALL= metagraph

include $(ROOTDIR)benchmarks/makefile.benchmarks

