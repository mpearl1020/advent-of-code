#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *fin = fopen("day3.in", "r");

    char *line = NULL;
    size_t len = 0; // size_t -> unsigned int to represent size of objects in bytes
    ssize_t read; // ssize_t -> signed int, same as size_t but can represent -1 (error)

    int priority = 0;

    int lineCount = 0;
    bool notFirst = false;

    int freq1[52] = {0};
    int freq2[52] = {0};
    int freq3[52] = {0};

    while ((read = getline(&line, &len, fin)) != -1) {
        for (int i = 0; i < strlen(line) - 1; i++) {
            int c = line[i];
            if (lineCount % 3 == 0) {
                if (c <= 'Z') { // A - Z
                    freq1[c - 'A' + 26]++;
                } else { // a - z
                    freq1[c - 'a']++;
                }
            } else if (lineCount % 3 == 1) {
                if (c <= 'Z') { // A - Z
                    freq2[c - 'A' + 26]++;
                } else { // a - z
                    freq2[c - 'a']++;
                }
            } else {
                notFirst = true;
                if (c <= 'Z') { // A - Z
                    freq3[c - 'A' + 26]++;
                } else { // a - z
                    freq3[c - 'a']++;
                }
            }
        }
        lineCount++;

        if (lineCount % 3 == 0 && notFirst) {
            for (int i = 0; i < 52; i++) {
                if (freq1[i] > 0 && freq2[i] > 0 && freq3[i] > 0) {
                    priority += (i + 1);
                }
            }
            memset(freq1, 0, sizeof(freq1));
            memset(freq2, 0, sizeof(freq2));
            memset(freq3, 0, sizeof(freq3));
        }
    }

    printf("Priority: %d\n", priority);

    fclose(fin);

    if (line) {
        free(line);
    }

    return 0;
}