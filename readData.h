#ifndef readData_h
#define readData_h

#define INITIAL_ARRAY_SIZE 100
#define INITIAL_BIG_STRUCTURE_SIZE 10000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ar {
    char *word;
    char rep;
    int value;
};

struct ru {
    char *consequent;
    int count;
    char **atecendent;
};

struct ru *readRules(char **filename, int nFiles);
struct ar *readData(char **filename, int nFiles);
unsigned long hash(char *word);

#endif
