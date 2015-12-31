

OPTS= -w

zlog.o: zlog.c zlog.h
	gcc ${OPTS} -c zlog.c

ketama.o: ketama.c
	gcc ${OPTS} -c ketama.c

test_md5.o: test_md5.c
	gcc ${OPTS} -c test_md5.c

zmd5.o: zmd5.c zmd5.h
	gcc ${OPTS} -c zmd5.c

test: test_md5.o ketama.o zlog.o zmd5.o
	gcc -o t ${OPTS} test_md5.o ketama.o zlog.o zmd5.o -lm

clean:
	rm -f *.o
