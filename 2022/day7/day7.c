#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 100

typedef struct treeNodeTag {
    char *name; // FOR DEBUGGING
    long size;
    int childIdx;
    struct treeNodeTag *parent;
    struct treeNodeTag **children;
} treeNode;

typedef struct {
    treeNode *root;
} tree;

int main() {
    FILE *fin = fopen("day7.in", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    tree fileTree;
    fileTree.root = NULL;

    treeNode *currNode = (treeNode *) malloc(sizeof(treeNode));
    currNode->name = (char *) malloc(MAX_NAME_LENGTH * sizeof(char));
    currNode->name = "/\0"; // FOR DEBUGGING
    currNode->size = 0;
    currNode->childIdx = -1;
    currNode->parent = NULL;
    currNode->children = NULL;

    fileTree.root = currNode;

    int numSubs = 0;

    /*
    attempt 1 -> create tree with level order traversal, DFS for sum of dir sizes <= 1e6
    $ cd -> create new treeNode for that directory
    $ ls -> continue parsing
    dir -> create new treenode and add to current node's children
    <size> -> create node for file
    */
    while ((read = getline(&line, &len, fin)) != -1) {
        printf("LINE: %s", line);
        printf("CURR NODE NAME: %s\n", currNode->name);
        // for (int i = 0; i < numSubs; i++) {
        //     printf("CHILD NAME: %s\n", currNode->children[i]->name);
        // }
        char command[5];
        strlcpy(command, &line[0], 5);
        if (line[0] == '$') {
            if (strcmp(command, "$ cd\0") == 0) {
                if (line[5] == '.' && line[6] == '.') { // $ cd ..
                    currNode = currNode->parent;
                } else { // cd <dir>
                    if (line[5] != '/') {
                        numSubs = 0;
                        currNode->childIdx++;
                        currNode = currNode->children[currNode->childIdx];
                    }
                }
            }
        } else { // directory or file encountered
            numSubs++;
            treeNode *newNode = (treeNode *) malloc(sizeof(treeNode));
            newNode->name = (char *) malloc(MAX_NAME_LENGTH * sizeof(char));
            newNode->size = 0;
            newNode->childIdx = -1;
            newNode->parent = currNode;
            if (numSubs == 1) {
                currNode->children = (treeNode **) malloc(sizeof(treeNode *));
            } else {
                currNode->children = (treeNode **) realloc(currNode->children, numSubs * sizeof(treeNode *));
            }
            if (strcmp(command, "dir \0") == 0) { // add each dir node to current node's children array
                strlcpy(newNode->name, &line[4], strlen(line) - 4);
                currNode->children[numSubs - 1] = newNode;
            } else { // add each file to current node's children
                long size = strtol(line, &line, 10);
                newNode->size = size;
                currNode->children[numSubs - 1] = newNode;
            }
            free(newNode);
        }
    }

    free(currNode);
    free(line);
    fclose(fin);

    return 0;
}