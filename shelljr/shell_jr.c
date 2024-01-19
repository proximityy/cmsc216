/* Zachary Meyers
120279096 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <unistd.h>

#define MAX_LINE_SIZE 1024
#define MAX_DIRS 16

void change_directory(char *);

int main() {
    char line[MAX_LINE_SIZE], cmd[MAX_LINE_SIZE], arg[MAX_LINE_SIZE],
        *dir_stack[MAX_DIRS], curr_dir[MAX_LINE_SIZE], *argv[3];
    int dir_top = 0, i;
    pid_t pid;

    printf("shell_jr: ");
    fflush(stdout);
    strcpy(arg, "");
    while (fgets(line, MAX_LINE_SIZE, stdin)) {
        sscanf(line, "%s %s", cmd, arg);
        if (!strcmp(cmd, "exit") || !strcmp(cmd, "goodbye")) {
            printf("See you\n");
            exit(0);
        } else if (!strcmp(cmd, "cd")) {
            change_directory(arg);
        } else if (!strcmp(cmd, "pushd")) {
            if (dir_top < 16) {
                getcwd(curr_dir, sizeof(curr_dir));
                dir_stack[dir_top] = malloc(strlen(curr_dir) + 1);
                strcpy(dir_stack[dir_top++], curr_dir);
                change_directory(arg);
            } else {
                printf("Directory stack is full\n");
                fflush(stdout);
            }
        } else if (!strcmp(cmd, "dirs")) {
            for (i = 0; i < dir_top; i++) {
                printf("%s\n", dir_stack[i]);
            }
        } else if (!strcmp(cmd, "popd")) {
            if (dir_top > 0) {
                change_directory(dir_stack[dir_top - 1]);
                free(dir_stack[--dir_top]);
            } else {
                printf("Directory stack is empty\n");
                fflush(stdout);
            }
        } else {
            argv[0] = cmd;
            if (strcmp(arg, "")) {
                argv[1] = arg;
                argv[2] = NULL;
            }
            else {
                argv[1] = NULL;
            }
            pid = fork();
            if (pid > 0) {
                wait(NULL);
            } else {
                execvp(argv[0], argv);
                printf("Failed to execute %s\n", cmd);
                fflush(stdout);
                exit(EX_OSERR);
            }
        }
        strcpy(arg, "");
        strcpy(cmd, "");
        printf("shell_jr: ");
        fflush(stdout);
    }
    return 0;
}

void change_directory(char *dir) {
    if (chdir(dir) == -1) {
        printf("Cannot change to directory %s\n", dir);
        fflush(stdout);
    }
}
