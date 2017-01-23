#include "printData.h"

void printData(struct ar *dataBank){
    int i;
    printf("Z pliku odczytalismy dane:\n\n");
    for (i=0; i < INITIAL_BIG_STRUCTURE_SIZE; i++){
        if(dataBank[i].word != NULL) {
            if (dataBank[i].kind == 'D') {
                printf("%s = %s\n", dataBank[i].word, dataBank[i].rep);
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
                if (dataBank[i].value == 1){
                    printf("%s = T\n", dataBank[i].word);
                }else{
                    printf("%s = F\n", dataBank[i].word);
                }
            }
        }
    }
}

void printToFile(char *output, struct ar *dataBank){
    int i;
    FILE *fp;
    fp = fopen(output, "w");
    for (i=0; i < INITIAL_BIG_STRUCTURE_SIZE; i++){
        if(dataBank[i].word != NULL) {
            if (dataBank[i].kind == 'S') {
                if (dataBank[i].value == 1){
                    fprintf(fp, "%s = T\r\n", dataBank[i].word);
                }else {
                    fprintf(fp, "%s = F\r\n", dataBank[i].word);
                }
            }
        }
    }
}