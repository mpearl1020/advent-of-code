#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fin = fopen("day2.in", "r");

    char *line = NULL;
    size_t len = 0; // size_t -> unsigned int to represent size of objects in bytes
    ssize_t read; // ssize_t -> signed int, same as size_t but can represent -1 (error)

    /*
        A -> rock, B -> paper, C -> scissors
        X -> rock, Y -> paper, Z -> scissors

        X -> lose, Y -> draw, Z -> win

        shape score: rock -> 1, paper -> 2, scissors -> 3
        outcome score: lose -> 0, draw -> 3, win -> 6
    */
    int score = 0;

    while ((read = getline(&line, &len, fin)) != -1) {
        char opp = line[0];
        char out = line[2];
        
        score += (3 * (out - 'X'));

        if (out == 'X') { // lose
            int resX = opp == 'A' ? 3 : (opp == 'B' ? 1 : 2);
            score += resX;
        } else if (out == 'Y') { // draw   
            int resY = opp == 'A' ? 1 : (opp == 'B' ? 2 : 3);
            score += resY;
        } else { // win (Z)
            int resZ = opp == 'A' ? 2 : (opp == 'B' ? 3 : 1);
            score += resZ;
        }
    }

    printf("Strategy Score: %d\n", score);

    fclose(fin);

    if (line) {
        free(line);
    }

    return 0;
}