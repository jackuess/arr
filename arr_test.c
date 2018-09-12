#include <stdalign.h>
#include <stdint.h>

#include "arr.h"
#include "vendor/scut/scut.h"

void test_arr_append(struct TestResult *tr) {
    char *string = arrnew(0, sizeof(string[0]));
    char *c = NULL;

    c = ARRAPPEND(&string);
    c[0] = 'F';
    c = ARRAPPEND(&string);
    c[0] = 'O';
    c = ARRAPPEND(&string);
    c[0] = 'O';
    ASSERT_EQ(tr, string[2], 'O');
    c[0] = 'o';
    c = ARRAPPEND(&string);
    c[0] = 'O';
    c = ARRAPPEND(&string);
    c[0] = '\0';
    ASSERT_STR_EQ(tr, string, "FOoO");
    ASSERT_EQ(tr, arrlen(string), 5);

    arrfree(string);
}

void test_arr_extend(struct TestResult *tr) {
    char *string = arrnew(0, sizeof(*string));
    char *source = "foobar";
    char *c;

    c = ARRAPPEND(&string);
    c[0] = source[1];
    char *extension = ARREXTEND(&string, 7);
    strncpy(extension, source, 7);
    ASSERT_STR_EQ(tr, string, "ofoobar");
    ASSERT_EQ(tr, arrlen(string), 8);

    arrfree(string);
}

struct Foo {
    int a;
    int b;
};

void foo_init(struct Foo *foo, int a, int b) {
    foo->a = a;
    foo->b = b;
}

void test_arr_append_struct(struct TestResult *tr) {
    struct Foo *foo = arrnew(0, sizeof(struct Foo));

    foo_init(ARRAPPEND(&foo), 5, 6);
    ASSERT_EQ(tr, foo[0].a, 5);
    ASSERT_EQ(tr, foo[0].b, 6);

    struct Foo *appendage = ARRAPPEND(&foo);
    appendage->a = 7;
    appendage->b = 8;
    ASSERT_EQ(tr, foo[1].a, 7);
    ASSERT_EQ(tr, foo[1].b, 8);
    ASSERT_EQ(tr, arrlen(foo), 2);

    arrfree(foo);
}

void test_arr_memory_alignment(struct TestResult *tr) {
    long double *foo = arrnew(0, sizeof foo[0]);
    ASSERT_EQ(tr, (uintptr_t)(const void *)foo % alignof(foo[0]), 0);
    ARRAPPEND(&foo);
    foo[0] = 2.2;
    ASSERT_EQ(tr, foo[0], 2.2);
    ASSERT_EQ(tr, arrlen(foo), 1);
    arrfree(foo);
}

void test_arr_initial_len(struct TestResult *tr) {
    int *foo = arrnew(5, sizeof foo[0]);

    ASSERT_EQ(tr, arrlen(foo), 5);
    foo[0] = 1;
    foo[1] = 2;
    foo[2] = 3;
    foo[3] = 4;
    foo[4] = 5;
    ASSERT_EQ(tr, arrlen(foo), 5);

    arrfree(foo);
}
