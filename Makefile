all: test test_wrapper

test: test.o local_shared_lib.so
	$(CC) test.o local_shared_lib.so -o test -ldl

test_wrapper: test_wrapper.o
	$(CC) test_wrapper.o -o test_wrapper -ldl

%.o: %.c
	$(CC)  $(CFLAGS) -c -o $@ $<

local_shared_lib.so: local_shared_lib.o
	$(CC) -shared -Wl,-soname,local_shared_lib.so -o local_shared_lib.so local_shared_lib.o

clean:
	rm -f test test_wrapper local_shared_lib.o test.o local_shared_lib.so
