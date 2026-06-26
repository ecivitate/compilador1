CC ?= gcc
FLEX ?= flex
BISON ?= bison

CFLAGS ?= -Wall -Wextra -g -std=gnu11
LDLIBS ?=

SRCDIR := src
BUILDDIR := build
PARSER := g-v2

ifeq ($(OS),Windows_NT)
TARGET := g-v2.exe
else
TARGET := g-v2
endif

CFILES := ast.c symtable.c semantic.c codegen.c
HDRS := $(addprefix $(SRCDIR)/,ast.h symtable.h semantic.h codegen.h)
OBJS := \
        $(BUILDDIR)/$(PARSER).tab.o \
        $(BUILDDIR)/lex.yy.o \
        $(addprefix $(BUILDDIR)/,$(CFILES:.c=.o))

.PHONY: all clean rebuild test run

all: $(TARGET)

$(BUILDDIR):
		mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(PARSER).tab.c $(BUILDDIR)/$(PARSER).tab.h: $(SRCDIR)/$(PARSER).y $(HDRS) | $(BUILDDIR)
		$(BISON) -d -o $(BUILDDIR)/$(PARSER).tab.c $(SRCDIR)/$(PARSER).y

$(BUILDDIR)/lex.yy.c: $(SRCDIR)/$(PARSER).l $(BUILDDIR)/$(PARSER).tab.h $(HDRS) | $(BUILDDIR)
		$(FLEX) -o $(BUILDDIR)/lex.yy.c $(SRCDIR)/$(PARSER).l

$(BUILDDIR)/$(PARSER).tab.o: $(BUILDDIR)/$(PARSER).tab.c $(BUILDDIR)/$(PARSER).tab.h $(HDRS)
		$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/lex.yy.o: $(BUILDDIR)/lex.yy.c $(BUILDDIR)/$(PARSER).tab.h $(HDRS)
		$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(HDRS) | $(BUILDDIR)
		$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

run: all
		./$(TARGET) $(FILE)

test: all
		bash ./test_run.sh ./$(TARGET)

clean:
		rm -rf $(BUILDDIR) g-v2 g-v2.exe
		find . -name '*.asm' -type f -delete 2>/dev/null || true

rebuild: clean all
