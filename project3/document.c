/*Zachary Meyers
  UID 120279096
  zmeyers3 */

#include "document.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define MAX_LINE_SIZE 1024

static int is_all_space(char *line);

/*****************************************************************/
/* The program allows the user access to a struct-based document */
/* management system, including functions such as initializing a */
/* document, adding paragraphs, and modifying existing text.     */
/*****************************************************************/

/******************************************/
/* load_file loads data from a provided file
into a provided document. */
/******************************************/
int load_file(Document *doc, const char *filename) {
    FILE *fptr;
    Paragraph new_p;
    Paragraph temp[MAX_PARAGRAPHS];
    static int curr_paragraph = -1;
    int curr_line = 0, i, k, swap_number = 0;
    char line[MAX_STR_SIZE + 1] = " ";
    char fixed_line[MAX_STR_SIZE + 1];

    curr_paragraph++;
    if (curr_paragraph != 0) {
        swap_number = curr_paragraph;
    }
    /* Check for preconditions */
    if (doc != NULL && filename != NULL &&
        doc->number_of_paragraphs < MAX_PARAGRAPHS) {
        fptr = fopen(filename, "r");
        if (fptr == NULL) {
            return FAILURE;
        }
        /* Initialize new paragraph */
        new_p.number_of_lines = 0;
        new_p.lines[0][0] = '\0';
        doc->paragraphs[curr_paragraph] = new_p;
        doc->number_of_paragraphs++;
        /* Read data line by line */
        while (fgets(line, MAX_STR_SIZE + 1, fptr) != NULL) {
            /* Check if we need a new paragraph */
            if (is_all_space(line) == SUCCESS) {
                curr_paragraph++;
                doc->number_of_paragraphs++;
                curr_line = 0;
            } else {
                /* Copy line to document */
                for (i = 0;
                     i < MAX_STR_SIZE + 1 && line[i] != '\n' && line[i] != '\0';
                     i++) {
                    fixed_line[i] = line[i];
                }
                fixed_line[i] = '\0';
                strcpy(doc->paragraphs[curr_paragraph].lines[curr_line],
                       fixed_line);
                doc->paragraphs[curr_paragraph].number_of_lines++;
                curr_line++;
            }
        }
        /* Swap the ordering if multiple files are provided */
        if (swap_number != 0) {
            for (i = 0; i < swap_number; i++) {
                temp[i] = doc->paragraphs[i];
            }
            while (i <= doc->number_of_paragraphs) {
                doc->paragraphs[i - swap_number] = doc->paragraphs[i];
                i++;
            }
            for (i = doc->number_of_paragraphs - swap_number, k = 0;
                 i < doc->number_of_paragraphs; i++) {
                doc->paragraphs[i] = temp[k++];
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* save_document prints the paragraphs
in the document to the provided file,
overwriting the file in the process. */
/******************************************/
int save_document(Document *doc, const char *filename) {
    FILE *fptr;
    int i, k;

    /* Checking for preconditions */
    if (doc != NULL && filename != NULL) {
        fptr = fopen(filename, "w");
        if (fptr == NULL) {
            return FAILURE;
        }
        /* Iterate through each line in each paragraph */
        for (i = 0; i < doc->number_of_paragraphs; i++) {
            for (k = 0; k < doc->paragraphs[i].number_of_lines; k++) {
                fputs(doc->paragraphs[i].lines[k], fptr);
                fprintf(fptr, "\n");
            }
            /* Print a newline after each paragraph */
            if (i < doc->number_of_paragraphs - 1) {
                fprintf(fptr, "\n");
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* init_document initializes a provided
document with a name and sets the number of
paragraphs to 0. */
/******************************************/
int init_document(Document *doc, const char *name) {
    /* Check for preconditions */
    if (doc != NULL && name != NULL && (int)strlen(name) <= MAX_STR_SIZE) {
        strcpy(doc->name, name);
        doc->number_of_paragraphs = 0;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* reset_document takes in a provided document
and sets its number of paragraphs to 0. */
/******************************************/
int reset_document(Document *doc) {
    /* Check for preconditions */
    if (doc != NULL) {
        doc->number_of_paragraphs = 0;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* print_document prints a provided document's
name, number of paragraphs, and iterates
through the document to print each paragraph. */
/******************************************/
int print_document(Document *doc) {
    int i, k;

    /* Check for preconditions */
    if (doc != NULL) {
        printf("Document name: \"%s\"\n", doc->name);
        printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
        /* Iterate through each paragraph */
        for (i = 0; i < doc->number_of_paragraphs; i++) {
            /* Print newline */
            if (i > 0 && doc->paragraphs[i - 1].number_of_lines > 0) {
                printf("\n");
            }
            /* Iterate through each line and print it out */
            for (k = 0; k < doc->paragraphs[i].number_of_lines; k++) {
                printf("%s\n", doc->paragraphs[i].lines[k]);
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* add_paragraph_after adds a new paragraph
to the document directly after the provided
paragraph number.  */
/******************************************/
int add_paragraph_after(Document *doc, int paragraph_number) {
    Paragraph new_p;
    int i;

    /* Check for preconditions */
    if (doc != NULL && doc->number_of_paragraphs < MAX_PARAGRAPHS &&
        paragraph_number <= doc->number_of_paragraphs) {
        new_p.number_of_lines = 0;
        /* If paragraph_number is 0, it's the first paragraph */
        if (paragraph_number == 0) {
            doc->paragraphs[0] = new_p;
        } else {
            /* Iterate through the document and shift paragraphs down by 1 */
            for (i = doc->number_of_paragraphs; i > paragraph_number; i--) {
                doc->paragraphs[i] = doc->paragraphs[i - 1];
            }
            /* Copy the new paragraph into appropriate position */
            doc->paragraphs[paragraph_number] = new_p;
        }
        doc->number_of_paragraphs++;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* add_line_after adds a new line to the
document in a provided paragraph, directly
after the provided line number.  */
/******************************************/
int add_line_after(Document *doc, int paragraph_number, int line_number,
                   const char *new_line) {
    int i;

    /* Check for preconditions */
    if (doc != NULL && paragraph_number <= doc->number_of_paragraphs &&
        doc->paragraphs[paragraph_number - 1].number_of_lines <
            MAX_PARAGRAPH_LINES &&
        line_number <= doc->paragraphs[paragraph_number - 1].number_of_lines &&
        new_line != NULL) {
        /* If line_number is 0, it's the first line */
        if (line_number == 0) {
            strcpy(doc->paragraphs[paragraph_number - 1].lines[0], new_line);
        } else {
            /* Iterate through the paragraph and shift lines down by 1 */
            for (i = doc->paragraphs[paragraph_number - 1].number_of_lines;
                 i > line_number; i--) {
                strcpy(doc->paragraphs[paragraph_number - 1].lines[i],
                       doc->paragraphs[paragraph_number - 1].lines[i - 1]);
            }
            /* Copy the new line into appropriate position */
            strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number],
                   new_line);
        }
        doc->paragraphs[paragraph_number - 1].number_of_lines++;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* get_number_lines_paragraph sets the
number_of_lines parameter equal to the total
number of lines in the specified paragraph.  */
/******************************************/
int get_number_lines_paragraph(Document *doc, int paragraph_number,
                               int *number_of_lines) {
    /* Check for preconditions */
    if (doc != NULL && number_of_lines != NULL &&
        paragraph_number <= doc->number_of_paragraphs) {
        *number_of_lines = doc->paragraphs[paragraph_number].number_of_lines;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* get_number_lines sets the number_of_lines
parameter equal to the total number
of lines in the document (iteratively).  */
/******************************************/
int get_number_lines(Document *doc, int *number_of_lines) {
    int count_lines = 0, i;

    /* Check for preconditions */
    if (doc != NULL) {
        /* Iterate through each paragraph to increment count_lines accordingly
         */
        for (i = 0; i < doc->number_of_paragraphs; i++) {
            count_lines += doc->paragraphs[i].number_of_lines;
        }
        *number_of_lines = count_lines;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* append_line adds a new line to the document
at the end of a specified paragraph, with a
provided string.  */
/******************************************/
int append_line(Document *doc, int paragraph_number, const char *new_line) {
    int *num_lines_in_paragraph;

    /* Check for preconditions */
    if (doc != NULL && paragraph_number <= doc->number_of_paragraphs &&
        doc->paragraphs[paragraph_number - 1].number_of_lines <
            MAX_PARAGRAPH_LINES &&
        new_line != NULL) {
        num_lines_in_paragraph =
            &doc->paragraphs[paragraph_number - 1].number_of_lines;
        /* Copy the new line into the end of specified paragraph */
        strcpy(doc->paragraphs[paragraph_number - 1]
                   .lines[*num_lines_in_paragraph],
               new_line);
        (*num_lines_in_paragraph)++;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* remove_line removes a specified line from
a specified paragraph in the document and shifts
all the proceeding lines down.  */
/******************************************/
int remove_line(Document *doc, int paragraph_number, int line_number) {
    int i;

    /* Check for preconditions */
    if (doc != NULL && paragraph_number <= doc->number_of_paragraphs &&
        line_number <= doc->paragraphs[paragraph_number - 1].number_of_lines) {
        /* Iterate through document and shift each line back by 1 */
        for (i = line_number - 1;
             i < doc->paragraphs[paragraph_number - 1].number_of_lines - 1;
             i++) {
            strcpy(doc->paragraphs[paragraph_number - 1].lines[i],
                   doc->paragraphs[paragraph_number - 1].lines[i + 1]);
        }
        doc->paragraphs[paragraph_number - 1].number_of_lines--;
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* load_document initializes a provided document
with paragraphs and lines using a provided
2D character array. */
/******************************************/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1],
                  int data_lines) {
    int curr_paragraph = 0, curr_line = 0, i;
    Paragraph new_p;

    /* Check for preconditions */
    if (doc != NULL && data != NULL && data_lines != 0) {
        new_p.number_of_lines = 0;
        new_p.lines[0][0] = '\0';
        doc->paragraphs[0] = new_p;
        doc->number_of_paragraphs++;
        /* Iterate through the data array */
        for (i = 0; i < data_lines; i++) {
            /* Handle an empty string by creating a new paragraph */
            if (strcmp(data[i], "") == 0) {
                curr_paragraph++;
                doc->number_of_paragraphs++;
                doc->paragraphs[curr_paragraph] = new_p;
                curr_line = 0;
            } else {
                /* Otherwise, append the string to end of current paragraph  */
                strcpy(doc->paragraphs[curr_paragraph].lines[curr_line],
                       data[i]);
                doc->paragraphs[curr_paragraph].number_of_lines++;
                curr_line++;
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* replace_text searches through all lines in
all paragraphs in the document for a provided
target string and replaces it with the provided
replacement string. */
/******************************************/
int replace_text(Document *doc, const char *target, const char *replacement) {
    int i, k, j, l, target_len, replacement_len, diff, paragraph_len, read_idx;
    char *start_ptr, *end_ptr, *iterate_ptr, *incr_ptr;

    /* Check for preconditions */
    if (doc != NULL && target != NULL && replacement != NULL) {
        target_len = strlen(target);
        replacement_len = strlen(replacement);
        diff = replacement_len - target_len;
        /* Iterate through each paragraph and line */
        for (i = 0; i < doc->number_of_paragraphs; i++) {
            for (k = 0; k < doc->paragraphs[i].number_of_lines; k++) {
                read_idx = 0;
                /* Continue checking a line while the target string still
                 * appears */
                while (strstr(&doc->paragraphs[i].lines[k][read_idx], target)) {
                    paragraph_len = (int)strlen(doc->paragraphs[i].lines[k]);
                    start_ptr =
                        strstr(&doc->paragraphs[i].lines[k][read_idx], target);
                    end_ptr = start_ptr + replacement_len;
                    read_idx = end_ptr - &doc->paragraphs[i].lines[k][0];
                    if (read_idx > MAX_STR_SIZE) {
                        read_idx = MAX_STR_SIZE;
                    }
                    /* Shift the line up in cases where the replacement string
                     * is longer than the target */
                    if (diff > 0) {
                        for (j = paragraph_len + diff - 1;
                             &doc->paragraphs[i].lines[k][j - diff] !=
                             start_ptr;
                             j--) {
                            doc->paragraphs[i].lines[k][j] =
                                doc->paragraphs[i].lines[k][j - diff];
                        }

                    } else if (diff < 0) {
                        /* Shift the line down in cases where the replacement
                         * string is shorter than the target */
                        incr_ptr = start_ptr + target_len - (diff * -1);
                        while (*incr_ptr != '\0') {
                            *incr_ptr = *(incr_ptr + (diff * -1));
                            incr_ptr++;
                        }
                    }

                    /* Fill the target area of the line with the replacement
                     * string */
                    for (iterate_ptr = start_ptr, l = 0; l < replacement_len;
                         iterate_ptr += 1, l++) {
                        *iterate_ptr = replacement[l];
                    }
                }
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* highlight_text searches through all lines in
all paragraphs in the document for a provided
target string and surrounds it with the
highlight marker (in this case, brackets). */
/******************************************/
int highlight_text(Document *doc, const char *target) {
    char replacement_text[MAX_STR_SIZE + 1];

    /* Check for preconditions */
    if (doc != NULL && target != NULL) {
        /* Create a new string with the target string surrounding by the
         * highlight text */
        strcpy(replacement_text, "");
        strcat(replacement_text, HIGHLIGHT_START_STR);
        strcat(replacement_text, target);
        strcat(replacement_text, HIGHLIGHT_END_STR);
        /* Call replace_text function with the new replacement string */
        replace_text(doc, target, replacement_text);
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* remove_text searches through all lines in
all paragraphs in the document for a provided
target string and deletes it, shifting the
remaining text accordingly. */
/******************************************/
int remove_text(Document *doc, const char *target) {
    /* Check for preconditions */
    if (doc != NULL && target != NULL) {
        replace_text(doc, target, "");
        return SUCCESS;
    }
    return FAILURE;
}

/******************************************/
/* is_all_space returns SUCCESS if a
character string contains only spaces. */
/******************************************/
static int is_all_space(char *line) {
    int i = 0;
    /* Iterate through each character in line */
    while (line[i] != '\0' && i < MAX_LINE_SIZE) {
        if (line[i] != ' ' && line[i] != '\n') {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}