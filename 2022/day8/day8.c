#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fin = fopen("day8.in", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // read in array
    read = getline(&line, &len, fin);
    int numCols = strlen(line) - 1;

    fseek(fin, 0, SEEK_SET);

    int numRows = 0;
    while ((read = getline(&line, &len, fin)) != -1) {
        numRows++;
    }

    int grid[numRows][numCols];
    memset(grid, 0, numRows * numCols * sizeof(int));
    
    fseek(fin, 0, SEEK_SET);

    for (int r = 0; r < numRows; r++) {
        read = getline(&line, &len, fin);
        for (int c = 0; c < numCols; c++) {
            grid[r][c] = line[c] - '0';
        }
    }

    

    return 0;
}