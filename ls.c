#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    int length = 4;
    for (int i = 1; i < argc; ++i) {
        length += strlen(argv[i]) + 1;
    }

    char *command = (char *)malloc(length * sizeof(char));
    if (command == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(command, "dir");

    for (int i = 1; i < argc; ++i) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    system(command);

    free(command);

    return 0;
}
