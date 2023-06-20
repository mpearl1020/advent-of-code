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

    int visible = 0;

    // algorithm - O(n^3)
    for (int r = 1; r < numRows - 1; r++) {
        for (int c = 1; c < numCols - 1; c++) {
            int leftMax = 0;
            int rightMax = 0;
            int topMax = 0;
            int bottomMax = 0;

            // left
            for (int j = c - 1; j >= 0; j--) {
                if (grid[r][j] > leftMax) {
                    leftMax = grid[r][j];
                }
            }

            // right
            for (int j = c + 1; j < numCols; j++) {
                if (grid[r][j] > rightMax) {
                    rightMax = grid[r][j];
                }
            }

            // top
            for (int i = r - 1; i >= 0; i--) {
                if (grid[i][c] > topMax) {
                    topMax = grid[i][c];
                }
            }

            // bottom
            for (int i = r + 1; i < numRows; i++) {
                if (grid[i][c] > bottomMax) {
                    bottomMax = grid[i][c];
                }
            }

            int currTree = grid[r][c];

            if (leftMax < currTree || rightMax < currTree || topMax < currTree || bottomMax < currTree) {
                visible++;
            }
        }
    }    

    // account for edges
    visible += (2 * numRows + 2 * (numCols - 2));

    printf("Number of visible trees: %d\n", visible);

    return 0;
}