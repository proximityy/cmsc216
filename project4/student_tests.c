#include "calendar.h"
#include "event.h"
#include "my_memory_checker_216.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
    return ((Event *)ptr1)->duration_minutes -
           ((Event *)ptr2)->duration_minutes;
}

static void clear_info(void *str) { str = NULL; }

/* FUNCTION SPECIFIC TESTS 1-10 */
/* EDGE CASE TESTS 11-14 */

/* This test checks the init_calendar function by initiating a
 * calendar and printing it */
static int test1() {
    int days = 7;
    Calendar *calendar;

    if (init_calendar("Test1", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/* This test checks the print_calendar function by initiating
 * a calendar and printing it */
static int test2() {
    int days = 7;
    Calendar *calendar;

    if (init_calendar("Test2", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/* This test checks the add_event function by adding an event
 * to a calendar and making sure the name is as expected */
static int test3() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";

    if (init_calendar("Test3", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (!(strcmp(calendar->events[0]->name, name))) {
                return destroy_calendar(calendar);
            }
        }
    }

    return FAILURE;
}

/* This test checks the find_event function by creating two
 * events and attempting to find one of them, then printing the found event
 * out*/
static int test4() {
    int days = 7;
    Calendar *calendar;
    Event *e;
    const char *name = "Golfing";
    const char *name_2 = "Skiing";

    if (init_calendar("Test4", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (add_event(calendar, name_2, 1200, 120, NULL, 3) == SUCCESS) {
                if (find_event(calendar, name_2, &e) == SUCCESS) {
                    if (strcmp(e->name, name_2) == SUCCESS) {
                        return destroy_calendar(calendar);
                    }
                }
            }
        }
    }

    return FAILURE;
}

/* This test checks the find_event_by_day function by creating
 * an event and trying to find it on the wrong day, then checking the output*/
static int test5() {
    int days = 7;
    Calendar *calendar;
    Event *e;
    const char *name = "Golfing";
    const char *name_2 = "Skiing";

    if (init_calendar("Test5", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (add_event(calendar, name_2, 1200, 120, NULL, 3) == SUCCESS) {
                if (find_event_in_day(calendar, name_2, 1, &e) == FAILURE) {
                    return destroy_calendar(calendar);
                }
            }
        }
    }

    return FAILURE;
}

/* This test checks the remove_event by adding an event,
 * removing it, then ensuring it can no longer be found */
static int test6() {
    int days = 7;
    Calendar *calendar;
    Event *e;
    const char *name = "Golfing";

    if (init_calendar("Test6", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (remove_event(calendar, name) == SUCCESS) {
                if (find_event(calendar, name, &e) == FAILURE) {
                    return destroy_calendar(calendar);
                }
            }
        }
    }
    return FAILURE;
}

/* This test checks the get_event_info function by calling it
 * on an event with a string and ensuring the function return value is as
 * expected */
static int test7() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";
    const char *event_info = "Let's Go Golfing!";

    if (init_calendar("Test7", days, comp_minutes, clear_info, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, (void *)event_info, 1) ==
            SUCCESS) {
            if (!strcmp((char *)get_event_info(calendar, name), event_info)) {
                return destroy_calendar(calendar);
            }
        }
    }
    return FAILURE;
}

/* This test checks the clear_day function by adding multiple
 * events to one day, calling the function, and trying to find each of the
 * events that were originally added to the day */
static int test8() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";
    const char *name_2 = "Swimming";
    const char *name_3 = "Diving";

    if (init_calendar("Test8", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 3) == SUCCESS) {
            if (add_event(calendar, name_2, 1200, 120, NULL, 3) == SUCCESS) {
                if (add_event(calendar, name_3, 1200, 120, NULL, 3) ==
                    SUCCESS) {
                    if (clear_day(calendar, 3) == SUCCESS) {
                        if (find_event_in_day(calendar, name, 3, NULL) ==
                            FAILURE) {
                            if (find_event_in_day(calendar, name_2, 3, NULL) ==
                                FAILURE) {
                                if (find_event_in_day(calendar, name_3, 3,
                                                      NULL) == FAILURE) {
                                    return destroy_calendar(calendar);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("bad\n");
    return FAILURE;
}

/* This test checks the clear_calendar function by clearing a
 * calendar after adding events and verifying that the events can no longer be
 * found */
static int test9() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";
    const char *name_2 = "Studying";

    if (init_calendar("Test9", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (add_event(calendar, name_2, 1200, 120, NULL, 2) == SUCCESS) {
                if (clear_calendar(calendar) == SUCCESS) {
                    if (find_event(calendar, name, NULL) == FAILURE) {
                        if (find_event(calendar, name_2, NULL) == FAILURE) {
                            return destroy_calendar(calendar);
                        }
                    }
                }
            }
        }
    }
    return FAILURE;
}

/* This test checks the destroy_calendar function by calling the function and
 * verifying that success is returned, indicating all the FREE commands were
 * run. */
static int test10() {
    int days = 7;
    Calendar *calendar;
    const char *calendar_name = "Test10";
    const char *name = "Golfing";
    const char *name_2 = "Studying";

    if (init_calendar(calendar_name, days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (add_event(calendar, name_2, 1200, 120, NULL, 2) == SUCCESS) {
                if (destroy_calendar(calendar) == SUCCESS) {
                    return SUCCESS;
                }
            }
        }
    }
    return FAILURE;
}

/* This test checks the case of trying to add two events with the same name. The
 * test ensures that failure is returned from the second add_event call.*/
static int test11() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";
    const char *same_name = "Golfing";

    if (init_calendar("Test11", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 1) == SUCCESS) {
            if (add_event(calendar, same_name, 1200, 120, NULL, 3) == FAILURE) {
                print_calendar(calendar, stdout, 0);
                return destroy_calendar(calendar);
            }
        }
    }
    return FAILURE;
}

/* This test checks that add_event, clear_day, and find_event_in_day reject day
 * inputs that are either too low or too high. */
static int test12() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";

    if (init_calendar("Test12", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 0) == FAILURE) {
            if (add_event(calendar, name, 1200, 120, NULL, days + 1) ==
                FAILURE) {
                if (find_event_in_day(calendar, name, 0, NULL) == FAILURE) {
                    if (find_event_in_day(calendar, name, days + 1, NULL) ==
                        FAILURE) {
                        if (clear_day(calendar, 0) == FAILURE) {
                            if (clear_day(calendar, days + 1) == FAILURE) {
                                return destroy_calendar(calendar);
                            }
                        }
                    }
                }
            }
        }
    }
    return FAILURE;
}

/* This test checks that trying to run find_event when name is NULL returns
 * FAILURE. */
static int test13() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";

    if (init_calendar("Test13", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 0) == FAILURE) {
            if (find_event(calendar, NULL, NULL) == FAILURE) {
                return destroy_calendar(calendar);
            }
        }
    }
    return FAILURE;
}

/* This test checks verifies that removing an event that doesn't exist results
 * in FAILURE. */
static int test14() {
    int days = 7;
    Calendar *calendar;
    const char *name = "Golfing";

    if (init_calendar("Test14", days, comp_minutes, NULL, &calendar) ==
        SUCCESS) {
        if (add_event(calendar, name, 1200, 120, NULL, 0) == FAILURE) {
            if (remove_event(calendar, "Skiing") == FAILURE) {
                return destroy_calendar(calendar);
            }
        }
    }
    return FAILURE;
}

int main() {
    int result = SUCCESS;

    /***** Starting memory checking *****/
    start_memory_check();
    /***** Starting memory checking *****/

    if (test1() == FAILURE)
        result = FAILURE;
    if (test2() == FAILURE)
        result = FAILURE;
    if (test3() == FAILURE)
        result = FAILURE;
    if (test4() == FAILURE)
        result = FAILURE;
    if (test5() == FAILURE)
        result = FAILURE;
    if (test6() == FAILURE)
        result = FAILURE;
    if (test7() == FAILURE)
        result = FAILURE;
    if (test8() == FAILURE)
        result = FAILURE;
    if (test9() == FAILURE)
        result = FAILURE;
    if (test10() == FAILURE)
        result = FAILURE;
    if (test11() == FAILURE)
        result = FAILURE;
    if (test12() == FAILURE)
        result = FAILURE;
    if (test13() == FAILURE)
        result = FAILURE;
    if (test14() == FAILURE)
        result = FAILURE;

    /****** Gathering memory checking info *****/
    stop_memory_check();
    /****** Gathering memory checking info *****/

    if (result == FAILURE) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
