#include "backward.h"
#include "checkData.h"

struct ar *backwardThinking(struct ar *dataBank, struct ru *ruleBank) {

    int i, counter = 0;
    for (i = 0; i < ruleBank[0].counter && counter < ruleBank[0].counter; i++) {
        if (ruleBank[i].processedFlag == 1){
            counter++;
            if (counter == (ruleBank[0].counter))
                dataMissing();
            continue;
        }
        int j;
        int value = 2, nawias = 0;
        char *rep = strdup("rep");
        if(ruleBank[i].consequent[0] == '!') {
            memmove(&ruleBank[i].consequent[0], &ruleBank[i].consequent[1], strlen(ruleBank[i].consequent));
            if (dataBank[hash(ruleBank[i].consequent)].value == 1){
                value = 0;
            } else {
                value = 1;
            }
        }else {
            value = dataBank[hash(ruleBank[i].consequent)].value;
        }
        if (dataBank[hash(ruleBank[i].consequent)].value != 1 && dataBank[hash(ruleBank[i].consequent)].value != 0){
            counter++;
            if (counter == (ruleBank[0].counter))
                dataMissing();
            continue;
        }
        unsigned long dataIdx = hash(ruleBank[i].consequent);
        if (dataBank[dataIdx].word == NULL){
            printf("Brak takiej danej");
            exit(1);
        }
        char *rule = strdup(ruleBank[i].atecendent);
        char *tmpRule = malloc(10 * sizeof(char));

        for (j= 0, nawias = 0; j < strlen(rule); j++){
            if (rule[j] == '(') {
                nawias++;
            }
        }
        int k = 1;
        do{
            int nSIdx = -1, nEIdx = strlen(rule), deep = 0;
            for (j = strlen(rule)-1; j >0; j--) { //tu trzeba ogarnąć nawiasy
                if (rule[j] == ')') {
                    if (deep == 0)
                        nEIdx = j;
                    deep++;
                }
                if (rule[j] == '(') {
                    nSIdx = j;
                    deep--;
                    if (deep == 0)
                        break;
                }
            }
            tmpRule = realloc(tmpRule, (nEIdx - nSIdx) * sizeof(char));
            if (nSIdx != -1)
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx - 1);
            else
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx);
            if (k > 1){
                value = dataBank[hash(rep)].value;
            }

            if (nSIdx > -1){
                char *part1 = malloc((nSIdx + 1) * sizeof(char));
                char *part2 = malloc((strlen(rule) - nEIdx + 1) * sizeof(char));

                strncpy(part1, rule, nSIdx);
                strncpy(part2, rule + nEIdx + 1, strlen(rule));
                rule = strcat(strcat(part1, rep), part2);
            }
            dataBank = simpleBackwardThinking(dataBank, rule, value);
            free(rule);
            rule = strdup(tmpRule);

            nawias--;
            k++;
        }while (nawias > -1);

        if (dataBank[hash("processedFlag")].value == 1){
            ruleBank[i].processedFlag = 1;
            dataBank[hash("processedFlag")].value = NULL;
        }
        if (ruleBank[i].processedFlag == 1){
            counter++;
            if(i == (ruleBank[0].counter -1))
                i = -1;
            continue;
        }
        counter = 0;
    }
    return dataBank;
}

struct ar *simpleBackwardThinking (struct ar *dataBank, char *rule, int ruleValue){
    char *tmpAnd = "&&";
    char *tmpOr = "||";
    char *tmpRule = rule;
    int valueRight = 2, valueLeft = 2, value = ruleValue, lengthRight;
    char *operandRight;
    char *operator = malloc(2*sizeof(char));

    operandRight = strdup(strrchr(tmpRule, ' ')+1);
    strncpy(operator, strrchr(tmpRule, ' ')-2, 2);
    char *operandLeft = malloc((strlen(tmpRule)-strlen(operandRight)-4)*sizeof(char));
    strncpy(operandLeft,tmpRule, strlen(tmpRule)-strlen(operandRight)-4);

    while((strlen(tmpRule)-strlen(operandRight)-4) > 0){
        int opositeRight = 0;
        lengthRight = strlen(operandRight);
        if (operandRight[0] == '!'){
            memmove(&operandRight[0], &operandRight[1], strlen(operandRight));
            opositeRight = 1;
        }
        if (dataBank[hash(operandRight)].value != NULL){
            if (opositeRight == 1){
                if (dataBank[hash(operandRight)].value == 1){
                    valueRight = 0;
                } else {
                    valueRight = 1;
                }
            } else {
                valueRight = dataBank[hash(operandRight)].value;
            }
            if (strcmp(operator,tmpAnd) == 0){
                if (value == 1 && valueRight == 1){
                    valueLeft = 1;
                }else if (value == 0 && valueRight == 1){
                    valueLeft = 0;
                }
            } else if (strcmp(operator, tmpOr) == 0){
                if (value == 1 && valueRight == 0){
                    valueLeft = 1;
                } else if (value == 0 && valueRight == 0){
                    valueLeft = 0;
                }
            }
        } else {
            if (strcmp(operator,tmpAnd) == 0){
                if (value == 1) {
                    valueLeft = 1;
                    if (opositeRight == 1){
                        valueRight = 0;
                    } else {
                        valueRight = 1;
                    }
                }
            } else if (strcmp(operator, tmpOr) == 0){
                if (value == 0) {
                    valueLeft = 0;
                    if (opositeRight == 1){
                        valueRight = 1;
                    } else {
                        valueRight = 0;
                    }
                }
            }
        }

        if (valueRight != 2 && dataBank[hash(operandRight)].value == NULL){
            dataBank[hash(operandRight)].value = valueRight;
        }
        if (valueLeft != 2){
            value = valueLeft;
        }else {
            dataBank[hash("processedFlag")].value = NULL;
            break;
        }

        valueLeft = 2;
        valueRight = 2;
        free(tmpRule);
        tmpRule = strdup(operandLeft);

        if (strrchr(tmpRule, ' ') == NULL){
            if (operandRight[0] == '!'){
                memmove(&operandRight[0], &operandRight[1], strlen(operandRight));
                if (value == 1){
                    value = 0;
                } else {
                    value =1;
                }
            }
            dataBank[hash(operandLeft)].value = value;
            dataBank[hash("processedFlag")].value = 1;
            break;
        }

        operandRight = strdup(strrchr(tmpRule, ' ')+1);
        strncpy(operator, strrchr(tmpRule, ' ')-2, 2);
        free(operandLeft);
        operandLeft = malloc((strlen(tmpRule)-lengthRight-4)*sizeof(char));

        //strncpy(operandLeft, tmpRule, strlen(tmpRule)-strlen(operandRight)-4);
        //strncpy(tmpRule, operandLeft, strlen(tmpRule)-strlen(operandRight)-4);

        strlcpy(operandLeft, tmpRule, strlen(tmpRule)-lengthRight-3);
    }

    return dataBank;
}