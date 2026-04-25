CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -Wextra -g

all: g-v1

g-v1.tab.c g-v1.tab.h: g-v1.y
	$(BISON) -d g-v1.y

lex.yy.c: g-v1.l g-v1.tab.h
	$(FLEX) g-v1.l

g-v1: g-v1.tab.c lex.yy.c
	$(CC) $(CFLAGS) -o g-v1 g-v1.tab.c lex.yy.c -lfl

clean:
	rm -f g-v1.tab.c g-v1.tab.h lex.yy.c g-v1