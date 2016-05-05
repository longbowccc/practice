
OPTS=-w
CFLAGS=-g -I../include
CC=gcc

$(OBJS): %.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

s_objs=tree.o tree_node.o test.o

test: ${s_objs}
	gcc -o t ${OPTS} ${s_objs} -L../lib -lzlog


# phony 表示即使有clean这个文件也会执行命令
.PHONY: clean
clean:
	-rm -f t *.o
