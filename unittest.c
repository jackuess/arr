#include "vendor/scut/scut.h"

void test_arr_append(struct TestResult *tr);
void test_arr_extend(struct TestResult *tr);
void test_arr_append_struct(struct TestResult *tr);
void test_arr_memory_alignment(struct TestResult *tr);
void test_arr_initial_len(struct TestResult *tr);

int main() {
    void (*test_functions[])(struct TestResult *) = {&test_arr_append,
                                                     &test_arr_extend,
                                                     &test_arr_append_struct,
                                                     &test_arr_memory_alignment,
                                                     &test_arr_initial_len};

    struct TestResult *tr =
        t_run(sizeof test_functions / sizeof test_functions[0], test_functions);
    tr_print(tr);

    _Bool success = tr_success(tr);
    tr_free(tr);
    return success ? 0 : 1;
}
