CC ?= gcc
FLEX ?= flex
BISON ?= bison

CFLAGS ?= -Wall -Wextra -g -std=gnu11
LDLIBS ?=

SRCDIR = src
BUILDDIR = build

ifeq ($(OS),Windows_NT)
	TARGET = g-v1.exe
	DETECTED_OS = Windows
else
	TARGET = g-v1
	DETECTED_OS = Unix
endif

HDRS = \
	$(SRCDIR)/ast.h \
	$(SRCDIR)/symtable.h \
	$(SRCDIR)/semantic.h \
	$(SRCDIR)/codegen.h

OBJS = \
	$(BUILDDIR)/g-v1.tab.o \
	$(BUILDDIR)/lex.yy.o \
	$(BUILDDIR)/ast.o \
	$(BUILDDIR)/symtable.o \
	$(BUILDDIR)/semantic.o \
	$(BUILDDIR)/codegen.o

.PHONY: all clean rebuild test os

all: $(TARGET)

os:
	@echo "Sistema detectado: $(DETECTED_OS)"
	@echo "Executavel: $(TARGET)"

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/g-v1.tab.c $(BUILDDIR)/g-v1.tab.h: $(SRCDIR)/g-v1.y $(HDRS) | $(BUILDDIR)
	$(BISON) -d -o $(BUILDDIR)/g-v1.tab.c $(SRCDIR)/g-v1.y

$(BUILDDIR)/lex.yy.c: $(SRCDIR)/g-v1.l $(BUILDDIR)/g-v1.tab.h $(HDRS) | $(BUILDDIR)
	$(FLEX) -o $(BUILDDIR)/lex.yy.c $(SRCDIR)/g-v1.l

$(BUILDDIR)/g-v1.tab.o: $(BUILDDIR)/g-v1.tab.c $(BUILDDIR)/g-v1.tab.h $(HDRS)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/lex.yy.o: $(BUILDDIR)/lex.yy.c $(BUILDDIR)/g-v1.tab.h $(HDRS)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(HDRS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

clean:
	rm -rf $(BUILDDIR) g-v1 g-v1.exe
	rm -f *.asm
	rm -f tests/corretos/*.asm
	rm -f tests/errados/sintatico/*.asm
	rm -f tests/errados/semantico/*.asm

rebuild: clean all

test: all
	EXE=./$(TARGET) bash ./test_run.sh