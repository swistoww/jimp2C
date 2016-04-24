#ifndef readData_h
#define readData_h

#define INITIAL_SIZE 1
#define INITIAL_BIG_STRUCTURE_SIZE 10000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ar {
    char *word;
    char kind;
    char rep;
    int value;
};

struct ru {
    char *consequent;
    char *atecendent;
    int counter;
};

struct ru *readRules(char **filename, int nFiles);
struct ar *readData(char **filename, int nFiles);
unsigned long hash(char *word);

#endif
