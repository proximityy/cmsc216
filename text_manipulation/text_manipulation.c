/*Zachary Meyers
  UID 120279096 */

#include "text_manipulation.h"
#include <stdio.h>
#include <string.h>

/* Prototypes */
int right_align(const char *, char *, int);
int compact(char *, int *);

/**********************************************/
/* The program defines two different string */
/* modification functions, including a right-align  */
/* function and a function that removes spaces and */
/* indicates the total number of words in the string.  */
/***************************************************/

/*************************************************/
/* right_align takes in a constant source string,         */
/* a result string, and a length int variable, and places */
/* the source string into the result string using the */
/* appropriate length and aligned to the right. */
/******************************************/
int right_align(const char *src, char *result, int length) {
    int i, k = 0, j = 0, src_length = (int)strlen(src);

    /* Check for null parameters */
    if (src == NULL || result == NULL || strlen(src) == 0 || length < 1) {
        return FAILURE;
    } else {
        /* Determine the last character before trailing spaces */
        for (i = 0; i < src_length; i++) {
            if (src[i] != ' ') {
                k = i;
            }
        }
        /*  Check if result is too small to hold the string */
        if ((length < (k + 2)) || length > MAX_STR_LEN + 1) {
            return FAILURE;
        } else {
            /*  Add spaces in accordance with length variable */
            for (i = 0; i < length - (k + 2); i++) {
                result[i] = ' ';
            }
            /* Fill result with src string and add nullbyte */
            while (i < length) {
                result[i++] = src[j++];
            }
            result[length - 1] = '\0';
        }
    }
    return SUCCESS;
}

/*************************************************/
/* compact takes in a string and a pointer to a */
/* number, and removes all the spaces from the string. */
/* It also sets the int variable equal to the number */
/* of words present in the string. */
/******************************************/
int compact(char *arr, int *num) {
    int i, k, words = 0, arr_length = (int)strlen(arr), finished_word = 0;

    /* Check for null parameters */
    if (arr == NULL || arr_length == 0) {
        return FAILURE;
    }
    /* Loop through string until reaching a null byte */
    for (i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == ' ' || arr[i] == '\n' || arr[i] == '\t') {
            /* If space is found, shift the rest of string over */
            if (i > 0 && arr[i - 1] != ' ') {
                finished_word = 1;
            }
            for (k = i; k <= arr_length; k++) {
                arr[k] = arr[k + 1];
            }
            i--;
        } else {
            /* Increment word count after a new word is found */
            if (finished_word) {
                words++;
                finished_word--;
            }
            /* Check for first word */
            else if (i == 0) {
                words++;
            }
        }
    }
    /* Update num only if it's not a null pointer */
    if (num != NULL) {
        *num = words;
        return SUCCESS;
    }
    return FAILURE;
}
