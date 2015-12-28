

zlog.o: zlog.c zlog.h
	gcc -c zlog.c

ketama.o: ketama.c
	gcc -c ketama.c

test.o: test.c
	gcc -c test.c

test: test.o ketama.o zlog.o
	gcc -o t test.o ketama.o zlog.o

