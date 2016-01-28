

OPTS= -w
CFLAGS=
CC=gcc

OBJS=zlog.o ketama.o zmd5.o test_md5.o test_ktm.o

$(OBJS): %.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@


test_md5: test_md5.o ketama.o zlog.o zmd5.o
	gcc -o t ${OPTS} test_md5.o ketama.o zlog.o zmd5.o -lm

tk_objs= test_ktm.o ketama.o zlog.o zmd5.o

test_ktm: ${tk_objs}
	gcc -o t ${OPTS} ${tk_objs} -lm

# phony 表示即使有clean这个文件也会执行命令
.PHONY: clean
clean:
	-rm -f t *.o
