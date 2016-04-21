#include "readData.h"
#include "forward.h"

struct ar *forwardThinking(struct ar *dataBank, struct ru *ruleBank, char **arguments){
    int i;
    int length;
    unsigned long ruleIdx, dataIdx;
    char *word;
    char *token;
    char *operator;
    for (i=0; i < length; i++){
        int k = 1;
        int value1, value2;
        word = *(*arguments+i);
        ruleIdx = hash(word);
        if(word =! ruleBank[ruleIdx].consequent){
            printf("Dane sa niekompletne. Brak danej %s\n", word);
            exit(1);
        }
        else{
            token = strtok(ruleBank[ruleIdx].atecendent[i], " ");
            while(token != NULL){
                //usuwamy nawias otwierający
                dataIdx = hash(token);
                if (k=1){
                    value1 = dataBank[dataIdx].value;
                }
                //jezeli token ma nawias otwierający {
                //rekurencja z tokenem }
                operator = strtok(NULL, " ");
                token = strtok(NULL, " ");
                //jeżeli nawias zamykający {
                //usuwamy nawias z tokena }
                dataIdx = hash(token);
                value2 = dataBank[dataIdx].value;
                if (strcmp(operator, "&&") == 0){
                    value1 = (value1 && value2);
                }
                if (strcmp(operator, "||") == 0) {
                    value1 = (value1 && value2);
                }
            }
            if (dataBank[ruleIdx].value == NULL){
                dataBank[ruleIdx].value = value1;
            }
        }
    }
}