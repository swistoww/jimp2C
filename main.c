#include <stdio.h>
#include "readData.h"

int main(int argc, char **argv) {
    char **filename;
    struct ar *dataBank;
    struct ru *ruleBank;
    int i;
    int nFiles = atoi(argv[2]);
    filename = malloc(nFiles*sizeof(char*));
    for (i=0; i < atoi(argv[2]); i++){
        filename[i] = strdup(argv[i+3]);
    }
    dataBank = readData(filename, nFiles);
    ruleBank = readRules(filename, nFiles);
    printf("hello");
    return(0);
}
