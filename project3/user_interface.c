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
#define USER_QUIT -2
#define INVALID_CMD -3

static int execute_command(Document *doc, char *line, char *command);
static int is_all_space(char *line);

/*********************************************************/
/* The program creates a user interface that allows access
to document.c's functions while providing input validation
for each command. */
/********************************************************/

/*********************************************/
/* main reads data from either stdin or from
the user-provided file and calls execute_command
to validate/execute each command. */
/*********************************************/
int main(int argc, char *argv[]) {
    Document doc;
    FILE *input;
    char line[MAX_LINE_SIZE], command[MAX_STR_SIZE + 1], is_comment;
    int i, k, result;

    /* Determine whether data is read from stdin or file */
    if (argc > 2) {
        printf("Usage: user_interface\nUsage: user_interface <filename>\n");
        return EX_USAGE;
    }
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "%s cannot be opened.\n", argv[1]);
            return EX_OSERR;
        }
    } else {
        input = stdin;
    }
    strcpy(doc.name, "main_document");
    doc.number_of_paragraphs = 0;
    if (argc == 1) {
        fprintf(stdout, "> ");
    }
    /* Continue while more data is available */
    while (fgets(line, MAX_LINE_SIZE, input)) {
        /* Check the first character to see if it's a comment */
        sscanf(line, " %c", &is_comment);
        if (is_comment != '#' && is_all_space(line) == FAILURE) {
            /* Reset command */
            for (i = 0; i < MAX_STR_SIZE; i++) {
                command[i] = 0;
            }
            /* Capture the command name */
            for (i = 0, k = 0;
                 i < MAX_STR_SIZE &&
                 ((line[i] != ' ' && line[i] != '\n' && line[i] != '\0') ||
                  is_all_space(command) == SUCCESS);
                 i++) {
                if (line[i] != ' ') {
                    command[k++] = line[i];
                }
            }
            command[i] = '\0';
            /* Call execute_command and process output */
            result = execute_command(&doc, line, command);
            if (result == FAILURE) {
                fprintf(stdout, "%s failed\n", command);
            } else if (result == INVALID_CMD) {
                fprintf(stdout, "Invalid Command\n");
            } else if (result == USER_QUIT) {
                return SUCCESS;
            }
        }
        if (argc == 1) {
            fprintf(stdout, "> ");
        }
    }
    return SUCCESS;
}

/*************************************************/
/* execute_command validates each user-provided
line to ensure it meets the correct parameters
and calls the corresponding function in document.c */
/*************************************************/
static int execute_command(Document *doc, char *line, char *command) {
    int input1, input2, result, i, j = 0, k = 0;
    char input3[MAX_STR_SIZE + 1] = " ", input4[MAX_STR_SIZE + 1] = " ",
                               excess[MAX_STR_SIZE + 1];

    /* Check is the inputted command is equal to any recognized command using
     * sscanf. Not writing comments for each sscanf statement since it is very
     * repetitive. */
    if (!strcmp(command, "add_paragraph_after")) {
        result = sscanf(line, " %s %d %s", command, &input1, excess);
        if (result != 2 || input1 < 0) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        return add_paragraph_after(doc, input1);
    } else if (!strcmp(command, "add_line_after")) {
        result = sscanf(line, " %s %d %d", command, &input1, &input2);
        if (result != 3 || input1 < 1 || input2 < 0) {
            return INVALID_CMD;
        }
        /* Iterate through line until an asterisk is found */
        for (i = 0; i < MAX_LINE_SIZE && line[i] != '*'; i++) {
        }
        /* Check that asterisk is present */
        if (i >= MAX_LINE_SIZE) {
            return INVALID_CMD;
        }
        /* Copy the line over to input3 variable */
        while (i < MAX_LINE_SIZE && line[i] != '\0' && line[i] != '\n') {
            input3[j++] = line[i++];
        }
        input3[j] = '\0';
        /* Function call if command is successful */
        return add_line_after(doc, input1, input2, input3 + 1);
    } else if (!strcmp(command, "print_document")) {
        result = sscanf(line, " %s %s", command, excess);
        if (result != 1) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        return print_document(doc);
    } else if (!strcmp(command, "quit") || !strcmp(command, "exit")) {
        result = sscanf(line, " %s %s", command, excess);
        if (result != 1) {
            return INVALID_CMD;
        }
        /* Return that the user quit so the program will stop */
        return USER_QUIT;
    } else if (!strcmp(command, "append_line")) {
        result = sscanf(line, " %s %d", command, &input1);
        if (result != 2 || input1 < 1) {
            return INVALID_CMD;
        }
        /* Iterate through line until an asterisk is found */
        for (i = 0; i < MAX_LINE_SIZE && line[i] != '*'; i++) {
        }
        /* Check that asterisk is present */
        if (i >= MAX_LINE_SIZE) {
            return INVALID_CMD;
        }
        /* Copy the line over to input3 variable */
        while (i < MAX_LINE_SIZE && line[i] != '\0' && line[i] != '\n') {
            input3[j++] = line[i++];
        }
        input3[j] = '\0';
        /* Function call if command is successful */
        return append_line(doc, input1, input3 + 1);
    } else if (!strcmp(command, "remove_line")) {
        result =
            sscanf(line, " %s %d %d %s", command, &input1, &input2, excess);
        if (result != 3 || input1 < 1 || input2 < 1) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        return remove_line(doc, input1, input2);
    } else if (!strcmp(command, "load_file")) {
        result = sscanf(line, " %s %s %s", command, input3, excess);
        if (result != 2) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        return load_file(doc, input3);
    } else if (!strcmp(command, "replace_text")) {
        /* Iterate through line until quotation mark is found */
        for (i = 0; i < MAX_LINE_SIZE && line[i] != '"' && line[i] != '\0';
             i++) {
        }
        if (i == MAX_LINE_SIZE || i == strlen(line)) {
            return INVALID_CMD;
        }
        i++;
        /* Copy the target text to input3 */
        while (line[i] != '"' && i < MAX_LINE_SIZE) {
            input3[k++] = line[i++];
        }
        input3[k] = '\0';
        i++;
        if (i == MAX_LINE_SIZE || line[i] == '"') {
            return INVALID_CMD;
        }
        /* Continue iterating until next quotation mark is found */
        while (line[i] != '"' && i < MAX_LINE_SIZE) {
            i++;
        }
        i++;
        k = 0;
        /* Copy replacement text to input4 */
        while (line[i] != '"' && i < MAX_LINE_SIZE) {
            input4[k++] = line[i++];
        }
        input4[k] = '\0';
        /* Check that target and replacement are not empty text */
        if (is_all_space(input3) == SUCCESS ||
            is_all_space(input4) == SUCCESS) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        return replace_text(doc, input3, input4);
    } else if (!strcmp(command, "highlight_text")) {
        /* Iterate through line until quotation mark is found */
        for (i = 0; i < MAX_LINE_SIZE && line[i] != '"' && line[i] != '\0';
             i++) {
        }
        if (i == MAX_LINE_SIZE || i == strlen(line)) {
            return INVALID_CMD;
        }
        i++;
        /* Copy the target text to input3 */
        while (line[i] != '"' && i < MAX_LINE_SIZE) {
            input3[k++] = line[i++];
        }
        input3[k] = '\0';
        /* Check that target is not empty text */
        if (is_all_space(input3) == SUCCESS) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        highlight_text(doc, input3);
    } else if (!strcmp(command, "remove_text")) {
        /* Iterate through line until quotation mark is found */
        for (i = 0; i < MAX_LINE_SIZE && line[i] != '"' && line[i] != '\0';
             i++) {
        }
        if (i == MAX_LINE_SIZE || i == strlen(line)) {
            return INVALID_CMD;
        }
        i++;
        /* Copy the target text to input3 */
        while (line[i] != '"' && i < MAX_LINE_SIZE) {
            input3[k++] = line[i++];
        }
        input3[k] = '\0';
        /* Check that target is not empty text */
        if (is_all_space(input3) == SUCCESS) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        remove_text(doc, input3);
    } else if (!strcmp(command, "save_document")) {
        result = sscanf(line, " %s %s %s", command, input3, excess);
        if (result != 2) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        return save_document(doc, input3);
    } else if (!strcmp(command, "reset_document")) {
        result = sscanf(line, " %s %s", command, excess);
        if (result != 1) {
            return INVALID_CMD;
        }
        /* Function call if command is successful */
        reset_document(doc);

    } else {
        /* If command isn't recognized */
        return INVALID_CMD;
    }
    return SUCCESS;
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
