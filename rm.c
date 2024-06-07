#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: rm <file1> <file2> ...\n");
        return 1;
    }
    for (int i = 1; i < argc; ++i) {
        char command[256];
        snprintf(command, sizeof(command), "del %s", argv[i]);
        system(command);
    }
    return 0;
}
