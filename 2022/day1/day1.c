#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fin = fopen("day1.in", "r");

    char *line = NULL;
    size_t len = 0; // size_t -> unsigned int to represent size of objects in bytes
    ssize_t read; // ssize_t -> signed int, same as size_t but can represent -1 (error)

    int cal1 = 0;
    int cal2 = 0;
    int cal3 = 0;
    int curr = 0;

    while ((read = getline(&line, &len, fin)) != -1) {
        if (strcmp(line, "\n") == 0) {
            if (curr > cal1) {
                cal3 = cal2;
                cal2 = cal1;
                cal1 = curr;
            } else if (curr > cal2) {
                cal3 = cal2;
                cal2 = curr;
            } else if (curr > cal3) {
                cal3 = curr;
            }
            curr = 0;
        } else {
            curr += atoi(line);
        }
    }

    printf("Top 3 Calories Sum: %d\n", cal1 + cal2 + cal3);

    fclose(fin);

    if (line) {
        free(line);
    }

    return 0;
}