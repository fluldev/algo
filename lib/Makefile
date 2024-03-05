TESTS=test_sort
CFLAGS= -O2 -Wall -Wextra
LIBS=

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

default: test
test: $(TESTS)
	@for test in $(TESTS); do\
		./$$test;\
	done

test_sort: test_sort.c sort.o heap.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

