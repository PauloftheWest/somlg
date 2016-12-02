#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "dialog.h"

#include <stdlib.h>

static void titleTest(void **state) {
    somlg_dialog *dialog = parseDialog("0|Hello!|\n");
    assert_string_equal(getMessage(dialog), "Hello!");
    freeDialog(dialog);
    free(dialog);
}

static void decorationTest(void **state) {
    somlg_dialog *dialog = parseDialog("0|Hello!\n");
    assert_int_equal(getDecorationId(dialog), 0);
    freeDialog(dialog);
    free(dialog);
}

static void numOptionsTest(void **state) {
    somlg_dialog *dialog = parseDialog("0|Hello!|\n");
    assert_int_equal(getNumOptions(dialog), 0);
    freeDialog(dialog);
    free(dialog);
}

static void optionsTest(void **state) {
    somlg_dialog *dialog = parseDialog("0|Hello!|Matthew|Mark|Luke|John\n");
    assert_int_equal(getNumOptions(dialog), 4);
    assert_string_equal(getOption(dialog, 0), "Matthew");
    assert_string_equal(getOption(dialog, 1), "Mark");
    assert_string_equal(getOption(dialog, 2), "Luke");
    assert_string_equal(getOption(dialog, 3), "John");
    freeDialog(dialog);
    free(dialog);
}

int main(void)  {
    const UnitTest tests[] = {
        unit_test(titleTest),
        unit_test(decorationTest),
        unit_test(numOptionsTest),
        unit_test(optionsTest),
    };
    return run_tests(tests);
}
