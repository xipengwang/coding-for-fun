.SUFFIXES:
.SUFFIXES:	.cc .o .h

export CFLAGS_STD := -std=c++11 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE \
		-D_REENTRANT -Wall -Wno-unused-parameter -Wno-unused-variable \
		-Wno-format-zero-length -pthread -fPIC -Werror \
		-Wredundant-decls \
		-I.
export LDFLAGS_STD := -lpthread

MAKE := $(MAKE) --no-print-directory

CC = echo "$@" && g++
LD = echo "[$(notdir $@)]" && g++
AR = echo "[$(notdir $@)]" && ar

BIN_PATH = /home/april/C/bin
SRCS = $(shell ls *.cc)
OBJS = $(SRCS:%.cc=%.o)
TARGET = $(BIN_PATH)/qsort_cxx

all: $(TARGET)
	@/bin/true

$(TARGET): $(OBJS)
	@$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.cc %.h
	@$(CC) $(CFLAGS) -o $@ -c $(realpath $<) || exit 1

%.o: %.cc
	@$(CC) $(CFLAGS) -o $@ -c $(realpath $<) || exit 1

clean:
	@rm -fr $(TARGET) $(OBJS)
