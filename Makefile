CC = /usr/local/bin/gcc-13 
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=gnu99 -I ./
SRCDIR = src
BUILDDIR = build
BINDIR = bin
SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))
EXECS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SRC))

all: check_gcc_version $(EXECS)

check_gcc_version:
	@if $(CC) --version | grep -q "clang version"; then \
		echo "Error: Clang detected. Please use GCC >= 13"; \
		exit 1; \
	fi

$(BINDIR)/%: $(BUILDDIR)/%.o
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(BINDIR)/*

.PHONY: all clean check_gcc_version

