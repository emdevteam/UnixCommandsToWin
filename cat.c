#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        char command[256];
        snprintf(command, sizeof(command), "type %s", argv[i]);
        system(command);
    }
    return 0;
}
