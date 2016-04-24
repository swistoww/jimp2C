#include "printData.h"

void printData(struct ar *dataBank){
    int i;
    printf("Z pliku odczytalismy dane:\n\n");
    for (i=0; i < INITIAL_BIG_STRUCTURE_SIZE; i++){
        if(dataBank[i].word != NULL) {
            if (dataBank[i].kind == 'D') {
                printf("%s = %d\n", dataBank[i].word, dataBank[i].value);
            }
        }
    }
}

void printRules(struct ru *ruleBank){
    int i;
    printf("Z pliku odczytalismy reguly:\n\n");
    for (i=0; i < ruleBank[0].counter; i++){
        printf("%s => %s\n", ruleBank[i].atecendent, ruleBank[i].consequent);
    }
}

void printResults(struct ar *dataBank){
    int i;
    printf("Otrzymalismy nastepujace wyniki:\n\n");
    for (i=0; i < INITIAL_BIG_STRUCTURE_SIZE; i++){
        if(dataBank[i].word != NULL) {
            if (dataBank[i].kind == 'S') {
                printf("%s = %d\n", dataBank[i].word, dataBank[i].value);
            }
        }
    }
}