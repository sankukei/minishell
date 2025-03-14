#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/math_functions.h"

static void test_add(void **state) {
    (void) state;
    assert_int_equal(add(2, 3), 5);
    assert_int_equal(add(-1, 1), 0);
    assert_int_equal(add(0, 0), 0);
}

static void test_subtract(void **state) {
    (void) state;
    assert_int_equal(subtract(5, 3), 2);
    assert_int_equal(subtract(0, 1), -1);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add),
        cmocka_unit_test(test_subtract),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

