#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 4096

int main() {
    FILE *fin = fopen("day6.in", "r");

    char buff[MAX_SIZE];
    fgets(buff, MAX_SIZE, fin);

    int freqArr[26] = {0};

    int i = 0;
    int j = 1;

    freqArr[buff[i] - 'a']++;

    while (j < MAX_SIZE && i < MAX_SIZE) {
        if (j - i == 15) {
            printf("%d\n", j + 1);
            break;
        }
        if (freqArr[buff[j] - 'a'] == 0) {
            freqArr[buff[j] - 'a']++;
            j++;
        } else {
            memset(freqArr, 0, sizeof(freqArr));
            i = j;
            j = i + 1;
        }
    }

    fclose(fin);

    return 0;
}