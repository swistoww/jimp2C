#include "readData.h"
#include "forward.h"
#include "checkData.h"

struct ar *forwardThinking(struct ar *dataBank, struct ru *ruleBank) {
    int i;
    for (i = 0; i < ruleBank[0].counter; i++) {
        int j;
        int oposite = 0;
        int value, nawias = 0;
        if(ruleBank[i].consequent[0] == '!') {
            memmove(&ruleBank[i].consequent[0], &ruleBank[i].consequent[1], strlen(ruleBank[i].consequent));
            oposite++;
        }
        unsigned long dataIdx = hash(ruleBank[i].consequent);
        if (dataBank[dataIdx].word == NULL){
            printf("Brak takiej szukanej");
            exit(1);
        }
        struct ru *tmpRuleBank = ruleBank;
        char *rule = strdup(tmpRuleBank[i].atecendent);
        char *tmpRule = malloc(10 * sizeof(char));
        int m = 1;
        do {
            int nSIdx = -1, nEIdx = strlen(rule);
            for (j = 0; j < strlen(rule); j++) {
                if (rule[j] == '(') {
                    nSIdx = j;
                }
                if (rule[j] == ')') {
                    nEIdx = j;
                    nawias++;
                    break;
                }
            }
            tmpRule = realloc(tmpRule, (nEIdx - nSIdx) * sizeof(char));
            if(nSIdx != -1)
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx-1);
            else
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx);
            value = simpleThinking(tmpRule, dataBank);

            char *addData = malloc(10 * sizeof(char));
            sprintf(addData, "add%d", m);
            dataBank[hash(addData)].value = value;

            char *part1;
            char *part2;
            if (nSIdx > -1){
                part1 = malloc((nSIdx + 1) * sizeof(char));
                part2 = malloc((strlen(rule) - nEIdx + 1) * sizeof(char));

                strncpy(part1, rule, nSIdx);
                strncpy(part2, rule + nEIdx + 1, strlen(rule));
                rule = strcat(strcat(part1, addData), part2);
            }else {
                part1 = malloc(/*(nSIdx + 2) * */1 *sizeof(char));
                part2 = malloc((strlen(rule) - nEIdx + 1) * sizeof(char));

                strncpy(part1, rule, nSIdx + 1);
                strncpy(part2, rule + nEIdx, strlen(rule));
                rule = strcat(strcat(part1, addData), part2);
            }
            nawias--;

            if (nawias > -1){
                m++;
            } else {
                m = -1;
                if (rule[0] == '!') {
                    if (dataBank[hash(addData)].value == 1)
                        value = 0;
                    else if (dataBank[hash(addData)].value == 0)
                        value = 1;
                }
                free(part1);
                free(part2);
            }
        } while (m > 0);

        free(tmpRule);

        if (dataBank[dataIdx].value == _NULL) { //wstawienie do tablicy danych obliczonej wartosci
            if (oposite == 1){
                if (value == 1) {
                    dataBank[dataIdx].value = 0;
                    dataBank[dataIdx].rep = 'F';
                }
                else {
                    dataBank[dataIdx].value = 1;
                    dataBank[dataIdx].rep = 'T';
                }
            }
            else {
                dataBank[dataIdx].value = value;
                if (value == 1)
                    dataBank[dataIdx].rep = 'T';
                else dataBank[dataIdx].rep = 'F';
            }
        }
        else if (dataBank[dataIdx].value != value) {
            dataInconsistent(dataBank[dataIdx].word);
        }
    }
    return dataBank;
}

int simpleThinking (char *rule, struct ar *dataBank){
    int value1, value2, k=1;
    unsigned long dataIdx;
    char *operator;
    char *token;
    char *tmpRule = strdup(rule);

    token = strtok(tmpRule, " ");
    while(1){
        if (k == 1){
            if(token[0] == '!'){
                memmove(&token[0], &token[1], strlen(token));
                dataIdx = hash(token);
                if(dataBank[dataIdx].word == NULL)
                    dataMissing(dataBank[dataIdx].word);
                if (dataBank[dataIdx].value == 1)
                    value1 = 0;
                else if (dataBank[dataIdx].value == 0)
                    value1 = 1;
                else
                    dataEmpty(dataBank[dataIdx].word);
            }else {
                dataIdx = hash(token);
                if(dataBank[dataIdx].word == NULL)
                    dataMissing(dataBank[dataIdx].word);
                value1 = dataBank[dataIdx].value;
            }
            if ((strlen(rule)) == strlen(token))
                break;
            operator = strtok(NULL, " ");
            token = strtok(NULL, " ");
        }
        else{
            token = strtok(NULL, " ");
        }
        if(token[0] == '!'){
            memmove(&token[0], &token[1], strlen(token));
            dataIdx = hash(token);
            if(dataBank[dataIdx].word == NULL)
                dataMissing(dataBank[dataIdx].word);
            if (dataBank[dataIdx].value == 1)
                value2 = 0;
            else if (dataBank[dataIdx].value == 0)
                value2 = 1;
            else
                dataEmpty(dataBank[dataIdx].word);
        }else {
            dataIdx = hash(token);
            if(dataBank[dataIdx].word == NULL)
                dataMissing(dataBank[dataIdx].word);
            value2 = dataBank[dataIdx].value;
        }
        char *tmpAnd = "&&";
        if (strcmp(operator, tmpAnd) == 0){
            value1 = (value1 && value2);
        }
        char *tmpOr = "||";
        if (strcmp(operator, tmpOr) == 0) {
            value1 = (value1 || value2);
        }
        k++;
        operator = strtok(NULL, " ");
        if (operator == NULL)
            break;
    }
    return value1;
}