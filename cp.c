#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: cp <source> <destination>\n");
        return 1;
    }
    char command[512];
    snprintf(command, sizeof(command), "copy %s %s", argv[1], argv[2]);
    system(command);
    return 0;
}
