CC = gcc
CFLAGS = -pedantic -std=c11 -O3 -fstrict-aliasing -fsanitize=undefined
CFLAGS += -Werror -Wextra -Wall -Wconversion -Wno-sign-conversion -Wstrict-aliasing
DEBUG = 1

ifeq ($(DEBUG), 1)
	CFLAGS += -g
else
	CFLAGS += -DNDEBUG
endif

MEMCHECK = valgrind

SOURCES = arr.c
TEST_SOURCES = vendor/scut/scut.c unittest.c arr_test.c

bin/test: $(SOURCES) $(TEST_SOURCES)
	$(CC) $(CFLAGS) -lcurl -lmxml $(SOURCES) $(TEST_SOURCES) -o$@

.PHONY: test
test: bin/test
	$<

.PHONY: memcheck
memcheck: bin/test
	$(MEMCHECK) $<

.PHONY: indent
indent:
	clang-format -i -style=file *.h *.c
