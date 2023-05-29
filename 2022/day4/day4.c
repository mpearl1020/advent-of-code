#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fin = fopen("day4.in", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int numCount = 0;

    int overlaps = 0;

    while ((read = getline(&line, &len, fin)) != -1) {
        int al, ar, bl, br;
        char *p = line;
        while (*p) {
            if (isdigit(*p)) {
                int val = strtol(p, &p, 10);
                if (numCount % 4 == 0) {
                    al = val;
                } else if (numCount % 4 == 1) {
                    ar = val;
                } else if (numCount % 4 == 2) {
                    bl = val;
                } else {
                    br = val;
                }
                numCount++;
            } else {
                p++;
            }
        }
        if (!(ar < bl || br < al)) {
            overlaps++;
        }
    }

    printf("Overlaps: %d\n", overlaps);

    fclose(fin);

    if (line) {
        free(line);
    }

    return 0;
}