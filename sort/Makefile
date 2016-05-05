
OPTS=-w
CFLAGS=-g -I../include
CC=gcc

$(OBJS): %.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

s_objs=gen_num.o test.o bubble_sort.o insert_sort.o selection_sort.o quick_sort.o merge_sort.o heap_sort.o

test: ${s_objs}
	gcc -o t ${OPTS} ${s_objs} -L../lib -lzlog


# phony 表示即使有clean这个文件也会执行命令
.PHONY: clean
clean:
	-rm -f t *.o
