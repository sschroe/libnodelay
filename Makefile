
LIB_CFLAGS += -O2 -Wall -fPIC -shared -Wl,--no-as-needed -ldl

all: libnodelay.c
	$(CC) $(LIB_CFLAGS) $(CFLAGS) -o libnodelay.so libnodelay.c

32: libnodelay.c
	$(CC) -m32 $(LIB_CFLAGS) $(CFLAGS) -o libnodelay32.so libnodelay.c

64: libnodelay.c
	$(CC) -m64 $(LIB_CFLAGS) $(CFLAGS) -o libnodelay64.so libnodelay.c

test: libnodelay.c test.c
	$(CC) -O2 -Wall -o test test.c

clean:
	rm *.so test
