SECTIONS=basics sort heap order_stat

CFLAGS=-O2 -Wall -Wextra
LIBS=

TESTS=$(foreach sect,$(SECTIONS),test_$(sect))
OBJS=$(foreach sect,$(SECTIONS),$(sect).o)

default: test
test: $(TESTS)
	@for test in $(TESTS); do\
		./$$test;\
	done

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

test_%: test_%.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

test_basics: 

