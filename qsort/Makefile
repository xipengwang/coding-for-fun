.SUFFIXES:
.SUFFIXES:	.c .o .h

export CFLAGS_STD := -std=gnu99 -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE \
		-D_REENTRANT -Wall -Wno-unused-parameter -Wno-unused-variable \
		-Wno-format-zero-length -pthread -fPIC -Werror \
		-Wredundant-decls \
		-I.
export LDFLAGS_STD := -lpthread

MAKE := $(MAKE) --no-print-directory

CC = echo "$@" && clang
LD = echo "[$(notdir $@)]" && clang
AR = echo "[$(notdir $@)]" && ar

BIN_PATH = /home/april/c_cxx/bin
SRCS = $(shell ls *.c)
OBJS = $(SRCS:%.c=%.o)
TARGET = $(BIN_PATH)/qsort

all: $(TARGET)
	@/bin/true

$(TARGET): $(OBJS)
	@$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	@$(CC) $(CFLAGS) -o $@ -c $(realpath $<) || exit 1

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $(realpath $<) || exit 1

clean:
	@rm -fr $(TARGET) $(OBJS)
