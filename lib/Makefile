TESTS=test_heap test_sort
CFLAGS= -O2 -Wall -Wextra
LIBS=

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

default: test
test: $(TESTS)
	@for test in $(TESTS); do\
		./$$test;\
	done

test_heap: test_heap.c heap.o basics.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

test_sort: test_sort.c sort.o heap.o basics.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

