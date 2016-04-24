#include "backward.h"

struct ar *backwardThinking(struct ar *dataBank, struct ru *ruleBank){
    struct bw *temporaryData = malloc(INITIAL_BIG_STRUCTURE_SIZE * sizeof(struct bw));
    int x;
    for ( x= 0;  x < INITIAL_BIG_STRUCTURE_SIZE; x++) {
        temporaryData[x].shortcut = NULL;
        temporaryData[x].value = NULL;
        temporaryData[x].rule = NULL;
    }

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
            printf("Brak takiej danej");
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
            if (nSIdx != -1)
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx - 1);
            else
                strncpy(tmpRule, rule + nSIdx + 1, nEIdx - nSIdx);

            char *addData = malloc(10 * sizeof(char));
            sprintf(addData, "add%d", m);
            temporaryData[hash(addData)].shortcut = addData;
            temporaryData[hash(addData)].rule = tmpRule;

            char *part1;
            char *part2;
            if (nSIdx > -1) {
                part1 = malloc((nSIdx + 1) * sizeof(char));
                part2 = malloc((strlen(rule) - nEIdx + 1) * sizeof(char));

                strncpy(part1, rule, nSIdx);
                strncpy(part2, rule + nEIdx + 1, strlen(rule));
                rule = strcat(strcat(part1, addData), part2);
            } else {
                part1 = malloc(/*(nSIdx + 2) * */1 * sizeof(char));
                part2 = malloc((strlen(rule) - nEIdx + 1) * sizeof(char));

                strncpy(part1, rule, nSIdx + 1);
                strncpy(part2, rule + nEIdx, strlen(rule));
                rule = strcat(strcat(part1, addData), part2);
            }
            nawias--;
            if (nawias > -1) {
                m++;
            }
            else {
                temporaryData[hash(addData)].value = dataBank[dataIdx].value;
                m = -1;
                free(part1);
                free(part2);
            }
        } while(m>0);
    }
    return dataBank;
}

struct bw *simpleBackwardThinking (char *rule, struct ar *dataBank, struct bw *subRulesBank){
    unsigned long dataIdx;
    char *tmpRule = rule;
    int value1, value2, k, value;
    k = 1;
    char *operand2;

    if (k==1) {
        operand2 = tmpRule;
        value = subRulesBank[hash(operand2)].value;
    }
    tmpRule = subRulesBank[hash(operand2)].rule;
    char *operator = malloc(2*sizeof(char));
    operand2 = strdup(strrchr(tmpRule, ' ')+1);
    strncpy(operator, strrchr(tmpRule, ' ')-2, 2);
    char *operand1 = malloc((strlen(tmpRule)-strlen(operand2)-4)*sizeof(char));
    strncpy(operand1, tmpRule, strlen(tmpRule)-strlen(operand2)-4);


    return dataBank;
}