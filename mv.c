#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: mv <source> <destination>\n");
        return 1;
    }
    char command[512];
    snprintf(command, sizeof(command), "move %s %s", argv[1], argv[2]);
    system(command);
    return 0;
}
