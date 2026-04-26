CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -Wextra -g

SRCDIR = src

all: g-v1

g-v1.tab.c g-v1.tab.h: $(SRCDIR)/g-v1.y
	$(BISON) -d -o g-v1.tab.c $(SRCDIR)/g-v1.y

lex.yy.c: $(SRCDIR)/g-v1.l g-v1.tab.h
	$(FLEX) -o lex.yy.c $(SRCDIR)/g-v1.l

g-v1: g-v1.tab.c lex.yy.c $(SRCDIR)/ast.c $(SRCDIR)/symtable.c $(SRCDIR)/semantic.c $(SRCDIR)/codegen.c $(SRCDIR)/ast.h
	$(CC) $(CFLAGS) -I$(SRCDIR) -o g-v1 g-v1.tab.c lex.yy.c $(SRCDIR)/ast.c $(SRCDIR)/symtable.c $(SRCDIR)/semantic.c $(SRCDIR)/codegen.c

clean:
	rm -f g-v1.tab.c g-v1.tab.h lex.yy.c g-v1 g-v1.exe *.o
