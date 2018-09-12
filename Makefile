CC = gcc
CFLAGS = -pedantic -std=c11 -O3 -fstrict-aliasing -fsanitize=undefined
CFLAGS += -Werror -Wextra -Wall -Wconversion -Wno-sign-conversion -Wstrict-aliasing
DEBUG = 1

ifeq ($(DEBUG), 1)
	CFLAGS += -g
else
	CFLAGS += -DNDEBUG
endif

SOURCES = arr.c
TEST_SOURCES = vendor/scut/scut.c unittest.c arr_test.c

.PHONY: test
test:
	$(CC) $(CFLAGS) -lcurl -lmxml $(SOURCES) $(TEST_SOURCES) -o$@
	valgrind ./$@

.PHONY: indent
indent:
	clang-format -i -style=file *.h *.c
