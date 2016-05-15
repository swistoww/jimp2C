#include "readData.h"
#include "forward.h"
#include "checkData.h"

struct ar *forwardThinking(struct ar *dataBank, struct ru *ruleBank) {
    int i;
    int value= -1, counter = 0;
    for (i = 0; counter < ruleBank[0].counter; i++) { //tutaj po przejściu przez wszystkie reguły i ustawia się na 1 zamiast na 0 :/ Trzeba to poprawić
        int j;
        int oposite = 0;
        int  nawias = 0;
        if(ruleBank[i].consequent[0] == '!') {
            memmove(&ruleBank[i].consequent[0], &ruleBank[i].consequent[1], strlen(ruleBank[i].consequent));
            oposite++;
        }
        if(dataBank[hash(ruleBank[i].consequent)].rep !=NULL){
            counter++;
            if(counter == ruleBank[0].counter)
                break;
            continue;
        }
        unsigned long dataIdx = hash(ruleBank[i].consequent);
        if (dataBank[dataIdx].word == NULL){
            printf("Brak takiej szukanej");
            exit(1);
        }
        struct ru *tmpRuleBank = ruleBank;
        char *rule = strdup(tmpRuleBank[i].atecendent);
        //char *tmpRule = malloc(2 * sizeof(char));
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
            char *tmpRule = malloc((nEIdx - nSIdx) * sizeof(char));
            if(nSIdx != -1){
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx-1);
                if(strlen(tmpRule) > (nEIdx - nSIdx - 1)){
                    tmpRule[nEIdx - nSIdx-1] = '\0';
                }
            }
            else{
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx);
            }
            value = simpleThinking(tmpRule, dataBank);
            if (value == 2){
                break;
            }

            char *addData = malloc(10 * sizeof(char));
            sprintf(addData, "add%d", m);
            dataBank[hash(addData)].value = NULL;
            dataBank[hash(addData)].value = value;
            dataBank[hash(addData)].rep = "Q";

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

            //free(tmpRule);
           //tmpRule = NULL;
            //free(part1);
           // free(part2);

            if (nawias > -1){
                m++;
            } else {
                //m = -1;
                if (rule[0] == '!') {
                    if (dataBank[hash(addData)].value == 1)
                        value = 0;
                    else if (dataBank[hash(addData)].value == 0)
                        value = 1;
                }
                //free(part1);
                //free(part2);
                break;
            }
        } while (m > -1);

        if (value == 2){
            counter++;
            if(i == (ruleBank[0].counter -1))
                i = -1;
            if (counter == (ruleBank[0].counter - 1))
                dataMissing();
            continue;
        }

        //free(tmpRule);

        if (dataBank[dataIdx].rep !=  "F" && dataBank[dataIdx].rep != "T") { //wstawienie do tablicy danych obliczonej wartosci
            if (oposite == 1){
                if (value == 1) {
                    dataBank[dataIdx].value = 0;
                    dataBank[dataIdx].rep = "F";
                }
                else {
                    dataBank[dataIdx].value = 1;
                    dataBank[dataIdx].rep = "T";
                }
            }
            else {
                dataBank[dataIdx].value = value;
                if (value == 1)
                    dataBank[dataIdx].rep = "T";
                else dataBank[dataIdx].rep = "F";
            }
        }
        if(i == (ruleBank[0].counter - 1))
            i = -1;
        counter = 0;
    }
    return dataBank;
}

int simpleThinking (char *rule, struct ar *dataBank){
    int value1, value2, k=1;
    unsigned long dataIdx;
    char *operator;
    char *temporaryRule = strdup(rule);
    char *token = strtok(temporaryRule, " ");

    while(1){
        if (k == 1){
            if(token[0] == '!'){
                memmove(&token[0], &token[1], strlen(token));
                dataIdx = hash(token);
                if(dataBank[dataIdx].rep == NULL) {
                    value1 = 2;
                    break;
                }
                if (dataBank[dataIdx].value == 1)
                    value1 = 0;
                else if (dataBank[dataIdx].value == 0)
                    value1 = 1;
                else
                    dataEmpty(dataBank[dataIdx].word);
            }else {
                dataIdx = hash(token);
                if(dataBank[dataIdx].rep == NULL) {
                    value1 = 2;
                    break;
                } else value1 = dataBank[dataIdx].value;
            }
            if ((strlen(rule)) == strlen(token) || (strlen(rule)-1) == strlen(token))
                break;
            operator = strtok(NULL, " ");
            token = strtok(NULL, " ");
        }
        else{
            token = strtok(NULL, " ");
            if(token[0] == '!'){
                memmove(&token[0], &token[1], strlen(token));
                dataIdx = hash(token);
                if(dataBank[dataIdx].rep == NULL) {
                    value1 = 2;
                    break;
                }
                if (dataBank[dataIdx].value == 1)
                    value2 = 0;
                else if (dataBank[dataIdx].value == 0)
                    value2 = 1;
                else
                    dataEmpty(dataBank[dataIdx].word);
            }else {
                dataIdx = hash(token);
                if(dataBank[dataIdx].rep == NULL) {
                    value1 = 2;
                    break;
                }
                value2 = dataBank[dataIdx].value;
            }
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