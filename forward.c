#include "readData.h"
#include "forward.h"

struct ar *forwardThinking(struct ar *dataBank, struct ru *ruleBank){
    int i;
    int length;
    unsigned long ruleIdx;
    char *word;
    for (i=0; i < length; i++){
        int k = 1;
        int value1, value2;
        word = **(arguments+i);
        ruleIdx = hash(word);
        if(word =! ruleBank[ruleIdx].consequent){
            printf("Dane sa niekompletne. Brak danej %s\n", word);
            exit(1);
        }
        else{
            char *tmpRule = strdup(ruleBank[ruleIdx].atecendent[i]);

            if (dataBank[ruleIdx].value == NULL){ //wstaiwenie do tablicy danych obliczonej wartosci
                dataBank[ruleIdx].value = value1;
            }
        }
    }
}

int simpleThinking (char *rule, struct ar *dataBank, struct ru *ruleBank){
    int value1, value2, k;
    unsigned long dataIdx;
    char *operator;
    char *token, *tmpRule;
    while(1){
        token = strtok(tmpRule, " ");
        dataIdx = hash(token);
        if (k=1){
            value1 = dataBank[dataIdx].value;
            operator = strtok(NULL, " ");
            token = strtok(NULL, " ");
            dataIdx = hash(token);
        }
        value2 = dataBank[dataIdx].value;
        if (strcmp(operator, "&&") == 0){
            value1 = (value1 && value2);
        }
        if (strcmp(operator, "||") == 0) {
            value1 = (value1 && value2);
        }
        k++;
        if (operator = strtok(NULL, " ") == NULL);
        break;
    }
    return value1;
}