#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct stackEltTag {
    char crate;
    struct stackEltTag *next;
} stackElt;

typedef struct {
    stackElt *top;
} stack;

void initStack(stack *s) {
    s->top = NULL;
}

void push(stack *s, stackElt *elt) {
    elt->next = s->top;
    s->top = elt;
}

stackElt pop(stack *s) {
    return *s->top;
}

void removeTop(stack *s) {
    stackElt *elt;
    if (s->top) {
        elt = s->top;
        if (!elt->next) {
            s->top = NULL;
        } else {
            s->top = elt->next;
        }
        free(elt);
    }
}

void printStack(stack *s) {
    stackElt *elt;
    elt = s->top;
    while (elt) {
        printf("%c\n", elt->crate);
        elt = elt->next;
    }
}

int main() {
    FILE *fin = fopen("day5.in", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int numLines = 0;
    bool firstLine = true;

    read = getline(&line, &len, fin);
    int numStacks = strlen(line) / 4;
    stack stacks[numStacks]; 

    for (int i = 0; i < numStacks; i++) {
        initStack(&stacks[i]);
    }

    char *arr;

    rewind(fin); // reset file pointer to beginning of fin

    while ((read = getline(&line, &len, fin)) != -1) {
        // 1D array encoding of initial stacks state
        if (firstLine) {
            arr = (char *) malloc(numStacks * sizeof(char));
            for (int i = 1; i < strlen(line) - 1; i += 4) {
                if (line[i] == ' ') {
                    arr[(i - 1) / 4] = '~';
                } else {
                    arr[(i - 1) / 4] = line[i];
                }
            }
            numLines++;
            firstLine = false;
        } else if (line[0] == '[') {
            numLines++;
            arr = (char *) realloc(arr, numStacks * numLines);
            for (int i = 1; i < strlen(line) - 1; i += 4) {
                if (line[i] == ' ') {
                    arr[((i - 1) / 4) + (numLines - 1) * numStacks] = '~';
                } else {
                    arr[((i - 1) / 4) + (numLines - 1) * numStacks] = line[i];
                }
            }
        } else if (line[0] == ' ' && line[1] != ' ') { // initialize stacks and populate
            int currStack = numStacks - 1;
            for (int i = strlen(arr) - 1; i >= 0; i--) {
                if (arr[i] != '~') {
                    stackElt *elt;
                    elt = (stackElt*) malloc(sizeof(*elt));
                    elt->crate = arr[i];
                    push(&stacks[currStack], elt);
                }
                currStack--;
                if (currStack == -1) {
                    currStack = numStacks - 1;
                }
            }
        } else if (line[0] == 'm') { // perform move operations
            int numCount = 0;
            long int amount, from, to;
            char *p = line;
            while (*p) {
                if (isdigit(*p)) {
                    long int val = strtol(p, &p, 10);
                    if (numCount % 3 == 0) {
                        amount = val;
                    } else if (numCount % 3 == 1) {
                        from = val;
                    } else {
                        to = val;
                    }
                    numCount++;
                } else {
                    p++;
                }
            }
            stack tempStack;
            initStack(&tempStack);
            for (int i = 0; i < amount; i++) { // populate temporary stack
                stackElt fromElt = pop(&(stacks[from - 1]));
                removeTop(&(stacks[from - 1]));
                stackElt * addedElt = (stackElt *) malloc(sizeof(stackElt *));
                addedElt->crate = fromElt.crate;
                push(&tempStack, addedElt);
            }
            for (int i = 0; i < amount; i++) { // populate to stack
                stackElt fromElt = pop(&tempStack);
                removeTop(&tempStack);
                stackElt * addedElt = (stackElt *) malloc(sizeof(stackElt *));
                addedElt->crate = fromElt.crate;
                push(&(stacks[to - 1]), addedElt);
            }
        }
    }

    for (int i = 0; i < numStacks; i++) {
        printf("%c\n", stacks[i].top->crate);
    }

    fclose(fin);
    free(arr);

    if (line) {
        free(line);
    }

    return 0;
}