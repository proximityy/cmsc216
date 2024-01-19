/*Zachary Meyers
  UID 120279096
  zmeyers3 */

#include "calendar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************/
/* The program creates a simple calendar, allowing the user to
organize events by days, sort events, add, find, and remove events
and clear and delete the dynamically allocated calendar.     */
/*****************************************************************/

/******************************************/
/* init_calendar initializes a provided calendar
with its dynamically allocated parameters. */
/******************************************/
int init_calendar(const char *name, int days,
                  int (*compare_func)(const void *p1, const void *p2),
                  void (*clear_func)(void *), Calendar **calendar) {
    Calendar *new_calendar;

    /* Check for preconditions */
    if (days < 1 || name == NULL || calendar == NULL) {
        return FAILURE;
    }
    /* Allocate space for calendar, calendar name, and events array */
    new_calendar = malloc(sizeof(Calendar));
    if (new_calendar == NULL) {
        return FAILURE;
    }
    new_calendar->name = malloc(strlen(name) + 1);
    if (new_calendar->name == NULL) {
        return FAILURE;
    }
    strcpy(new_calendar->name, name);
    new_calendar->events = calloc(days, sizeof(Event *));
    if (new_calendar->events == NULL) {
        return FAILURE;
    }
    /* Initialize other calendar parameters */
    new_calendar->total_events = 0;
    new_calendar->days = days;
    new_calendar->comp_func = compare_func;
    new_calendar->free_info_func = clear_func;
    *calendar = new_calendar;
    return SUCCESS;
}

/******************************************/
/* print_calendar prints out calendar data,
including every event and event info. */
/******************************************/
int print_calendar(Calendar *calendar, FILE *stream, int print_fields) {
    int i;
    Event *e;

    /* Check for preconditions */
    if (calendar != NULL && stream != NULL) {
        if (print_fields) {
            /* Print out basic event info to stream */
            fprintf(stream, "Calendar's Name: \"%s\"\n", calendar->name);
            fprintf(stream, "Days: %d\n", calendar->days);
            fprintf(stream, "Total Events: %d\n", calendar->total_events);
            fprintf(stream, "\n");
        }
        /* Iterate through events array and print out info about each one */
        fprintf(stream, "**** Events ****\n");
        for (i = 0; i < calendar->days; i++) {
            if (calendar->total_events > 0) {
                fprintf(stream, "Day %d\n", i + 1);
            }
            e = calendar->events[i];
            /* Continue while linked list node (event) is not null */
            while (e != NULL) {
                fprintf(stream,
                        "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
                        e->name, e->start_time, e->duration_minutes);
                e = e->next;
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/*****************************************************/
/* add_event allocates memory for a new event, assigns
it parameters and places it in its corresponding
position in the events array. */
/*****************************************************/
int add_event(Calendar *calendar, const char *name, int start_time,
              int duration, void *info, int day) {
    Event *event, *curr, *prev = NULL;

    /* Check for preconditions */
    if (calendar != NULL && name != NULL && day >= 1 && day <= calendar->days &&
        start_time >= 0 && start_time <= 2400 && duration > 0 &&
        find_event(calendar, name, &event) == FAILURE) {
        /* Allocate space */
        event = malloc(sizeof(Event));
        if (event == NULL) {
            return FAILURE;
        }
        event->name = malloc(strlen(name) + 1);
        if (event->name == NULL) {
            return FAILURE;
        }
        /* Assign event parameters */
        strcpy(event->name, name);
        event->info = info;
        event->start_time = start_time;
        event->duration_minutes = duration;
        event->next = NULL;
        curr = calendar->events[day - 1];
        /* Iterate through linked list until the event is sorted accordingly */
        while (curr != NULL && calendar->comp_func(event, curr) > 0) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == NULL) {
            calendar->events[day - 1] = event;
            event->next = curr;
        } else {
            prev->next = event;
            event->next = curr;
        }
        /* Increment total_events */
        calendar->total_events++;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* find_event attempts to locate an event by
name and returns FAILURE if unable to do so. */
/******************************************/
int find_event(Calendar *calendar, const char *name, Event **event) {
    int i;

    /* Iterate through each day and call find_event_in_day */
    for (i = 1; i <= calendar->days; i++) {
        if (find_event_in_day(calendar, name, i, event) == SUCCESS) {
            return SUCCESS;
        }
    }
    return FAILURE;
}

/******************************************/
/* find_event_in_day iterates through a day's
linked list of events to determine if the
provided event name can be located. */
/******************************************/
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event) {
    Event *curr;

    /* Check for preconditions */
    if (calendar != NULL && name != NULL && day > 0 && day <= calendar->days) {
        curr = calendar->events[day - 1];
        /* Continue iteration while current node isn't null */
        while (curr != NULL) {
            /* Assign curr to *event if found */
            if (!(strcmp(curr->name, name))) {
                if (event != NULL) {
                    *event = curr;
                }
                return SUCCESS;
            }
            curr = curr->next;
        }
    }
    return FAILURE;
}

/******************************************/
/* remove_event removes a provided event and
frees the associated memory. */
/******************************************/
int remove_event(Calendar *calendar, const char *name) {
    Event *curr, *prev = NULL;
    int i;

    /* Check for preconditions */
    if (calendar != NULL && name != NULL &&
        find_event(calendar, name, &curr) == SUCCESS) {
        /* Iterate through each day */
        for (i = 0; i < calendar->days; i++) {
            curr = calendar->events[i];
            /* Iterate through each day's linked list */
            while (curr != NULL) {
                /* If found, update linked list */
                if (!(strcmp(curr->name, name))) {
                    if (prev == NULL) {
                        calendar->events[i] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }
                    /* Call free_info_func */
                    if (curr->info != NULL) {
                        calendar->free_info_func(curr->info);
                    }
                    /* Free event memory */
                    free(curr->name);
                    free(curr);
                    calendar->total_events--;
                    return SUCCESS;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return FAILURE;
}

/******************************************/
/* get_event_info returns the info parameter
associated with an event. */
/******************************************/
void *get_event_info(Calendar *calendar, const char *name) {
    Event *e;

    /* Check for preconditions */
    if (find_event(calendar, name, &e) == SUCCESS) {
        return (void *)e->info;
    }
    return NULL;
}

/******************************************/
/* clear_day removes all events from a provided
day using the remove_event function. */
/******************************************/
int clear_day(Calendar *calendar, int day) {
    /* Check for preconditions */
    if (calendar != NULL && day > 0 && day <= calendar->days) {
        /* Continue removing events from linked list until linked list head is
         * null */
        while (calendar->events[day - 1] != NULL) {
            remove_event(calendar, calendar->events[day - 1]->name);
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* clear_calendar removes all events in the
calendar using the clear_day function. */
/******************************************/
int clear_calendar(Calendar *calendar) {
    int i;

    /* Check for preconditions */
    if (calendar) {
        /* Iterate through each day */
        for (i = 0; i < calendar->days; i++) {
            clear_day(calendar, i + 1);
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* destroy_calendar removes all events in the
calendar and deallocates the calendar's memory. */
/******************************************/
int destroy_calendar(Calendar *calendar) {
    /* Check for preconditions */
    if (calendar) {
        clear_calendar(calendar);
        free(calendar->events);
        free(calendar->name);
        calendar->events = NULL;
        calendar->name = NULL;
        free(calendar);
        return SUCCESS;
    }
    return FAILURE;
}