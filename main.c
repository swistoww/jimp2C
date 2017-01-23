#include <stdio.h>
#include "readData.h"
#include "forward.h"
#include "printData.h"
#include "backward.h"
#include "checkData.h"

int main(int argc, char **argv) {
    char **filename;
    struct ar *dataBank;
    struct ru *ruleBank;
    int i;
    int nFiles = atoi(argv[2]);
    filename = malloc(nFiles*sizeof(char*));
    for (i=0; i < nFiles; i++){
        filename[i] = strdup(argv[i+3]);
    }

        dataBank = readData(filename, nFiles);
        printData(dataBank);
        ruleBank = readRules(filename, nFiles);
        printRules(ruleBank);
    if (strcmp(argv[1], "przod") == 0){
        dataBank = forwardThinking(dataBank, ruleBank);
        if (argv[i+3] != NULL)
            printToFile(argv[i+3], dataBank);
        printResults(dataBank);
    }
    else if(strcmp(argv[1], "tyl") == 0){
        dataBank = backwardThinking(dataBank, ruleBank);
        printResults(dataBank);
    } else {
        printf("Nieznany tryb pracy! Przeczytaj instrukcje.");
    }

    return(0);
}
