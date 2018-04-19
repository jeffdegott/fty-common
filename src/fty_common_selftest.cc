/*  =========================================================================
    fty_common_selftest.c - run selftests

    Runs all selftests.

    -------------------------------------------------------------------------
    Copyright (C) 2014 - 2018 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
    =========================================================================
*/

#include "fty_common_classes.h"

#include <stdio.h>
#include <string.h>

typedef struct {
    const char *testname;           // test name, can be called from command line this way
    void (*test) (bool);            // function to run the test (or NULL for private tests)
    bool stable;                    // true if class is declared as stable
    bool pub;                       // true if class is declared as public
    const char *subtest;            // name of private subtest to run
} test_item_t;

static test_item_t
all_tests [] = {
#ifdef FTY_COMMON_BUILD_DRAFT_API
// Tests for draft public classes:
    { "fty_common_log_fty_log", fty_common_log_fty_log_test, false, true, NULL },
    { "fty_common_common_fty_commons", fty_common_common_fty_commons_test, false, true, NULL },
    { "fty_common_common_fty_uuid", fty_common_common_fty_uuid_test, false, true, NULL },
#endif // FTY_COMMON_BUILD_DRAFT_API
    {NULL, NULL, 0, 0, NULL}          //  Sentinel
};

//  -------------------------------------------------------------------------
//  Test whether a test is available.
//  Return a pointer to a test_item_t if available, NULL otherwise.
//

test_item_t *
test_available (const char *testname)
{
    test_item_t *item;
    for (item = all_tests; item->testname; item++) {
        if (strcmp (testname, item->testname) == 0)
            return item;
    }
    return NULL;
}

//  -------------------------------------------------------------------------
//  Run all tests.
//

static void
test_runall (bool verbose)
{
    test_item_t *item;
    printf ("Running fty-common selftests...\n");
    for (item = all_tests; item->testname; item++) {
        if (strcmp (item->testname, "private_classes") == 0)
            continue;
        if (!item->subtest)
            item->test (verbose);
#ifdef FTY_COMMON_BUILD_DRAFT_API // selftest is still in draft
        else
            fty_common_private_selftest (verbose, item->subtest);
#endif // FTY_COMMON_BUILD_DRAFT_API
    }

    printf ("Tests passed OK\n");
}

static void
test_list (void)
{
    test_item_t *item;
    puts ("Available tests:");
    for (item = all_tests; item->testname; item++)
        printf ("    %-40s - %s	%s\n",
            item->testname,
            item->stable ? "stable" : "draft",
            item->pub ? "public" : "private"
        );
}

static void
test_number (void)
{
    int n = 0;
    test_item_t *item;
    for (item = all_tests; item->testname; item++) {
        if (strcmp (item->testname, "private_classes") == 0)
            n++;
    }
    printf ("%d\n", n);
}

int
main (int argc, char **argv)
{
    bool verbose = false;
    test_item_t *test = 0;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (strcmp (argv [argn], "--help") == 0
        ||  strcmp (argv [argn], "-h") == 0) {
            puts ("fty_common_selftest.c [options] ...");
            puts ("  --verbose / -v         verbose test output");
            puts ("  --number / -n          report number of tests");
            puts ("  --list / -l            list all tests");
            puts ("  --test / -t [name]     run only test 'name'");
            puts ("  --continue / -c        continue on exception (on Windows)");
            return 0;
        }
        if (strcmp (argv [argn], "--verbose") == 0
        ||  strcmp (argv [argn], "-v") == 0)
            verbose = true;
        else
        if (strcmp (argv [argn], "--number") == 0
        ||  strcmp (argv [argn], "-n") == 0) {
            test_number ();
            return 0;
        }
        else
        if (strcmp (argv [argn], "--list") == 0
        ||  strcmp (argv [argn], "-l") == 0) {
            test_list ();
            return 0;
        }
        else
        if (strcmp (argv [argn], "--test") == 0
        ||  strcmp (argv [argn], "-t") == 0) {
            argn++;
            if (argn >= argc) {
                fprintf (stderr, "--test needs an argument\n");
                return 1;
            }
            test = test_available (argv [argn]);
            if (!test) {
                fprintf (stderr, "%s not valid, use --list to show tests\n", argv [argn]);
                return 1;
            }
        }
        else
        if (strcmp (argv [argn], "--continue") == 0
        ||  strcmp (argv [argn], "-c") == 0) {
#ifdef _MSC_VER
            //  When receiving an abort signal, only print to stderr (no dialog)
            _set_abort_behavior (0, _WRITE_ABORT_MSG);
#endif
        }
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }

    #ifdef NDEBUG
        printf(" !!! 'assert' macro is disabled, remove NDEBUG from your compilation definitions.\n");
        printf(" tests will be meaningless.\n");
    #endif //

    if (test) {
        printf ("Running fty-common test '%s'...\n", test->testname);
        if (!test->subtest)
            test->test (verbose);
#ifdef FTY_COMMON_BUILD_DRAFT_API // selftest is still in draft
        else
            fty_common_private_selftest (verbose, test->subtest);
#endif // FTY_COMMON_BUILD_DRAFT_API
    }
    else
        test_runall (verbose);

    return 0;
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
