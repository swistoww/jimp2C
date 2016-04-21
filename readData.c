#include "readData.h"

unsigned long hash(char *word) {
    unsigned long hash = 5381;
    int c;
    while (c = *word++)
        hash = (((hash << 5) + hash) + c) % INITIAL_BIG_STRUCTURE_SIZE; /* hash * 33 + c */
    return hash;
}

struct ar *readData(char **filename, int nFiles) {

    struct ar *dataBank = malloc(INITIAL_BIG_STRUCTURE_SIZE * sizeof(struct ar));
    int i;
    unsigned long hashIdx = 0;
    for (i = 0; i < nFiles; i++) {
        FILE *fp = fopen(filename[i], "r");
        char *line = NULL;
        size_t len = 0;
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        } else {

            int k = 1;                                //zmienna do sprawdzenia ilości wykonań
            getline(&line, &len, fp);
            char *token = strtok(line, " =\r\n");
            if (strcmp(token, "Dane:") == 0) {
                while (getline(&line, &len, fp) != -1) {
                    if (strlen(line) > 2) {
                        token = strtok(line, " =\r\n");
                    } else continue;
                    if (strcmp(token, "Wzory:") == 0 || strlen(line) == 1) {
                        do {
                            getline(&line, &len, fp);
                            if (strlen(line) > 2) {
                                token = strtok(line, " =\r\n");
                            }
                        } while (strcmp(token, "Szukane:") != 0 || strlen(line) < 3);
                        getline(&line, &len, fp);
                        while (strlen(line) < 3) {
                            getline(&line, &len, fp);
                        }
                        token = strtok(line, " =\r\n");
                    }
                    k++;
                    hashIdx = hash(token);
                    dataBank[hashIdx].word = strdup(token);
                    token = strtok(NULL, " =\r\n");
                    dataBank[hashIdx].rep = strdup(token);
                    if (strcmp(token, "F") == 0) {
                        dataBank[hashIdx].value = 0;
                    } else if (strcmp(token, "T") == 0) {
                        dataBank[hashIdx].value = 1;
                    } else if (strcmp(token, "?") == 0) {
                        dataBank[hashIdx].value = NULL;
                    } else {
                        printf("Plik z danymi jest niepoprawny.");
                        exit(1);
                    }

                }
            }
        }
    }
    return dataBank;
}

struct ru *readRules(char **filename, int nFiles) {

    struct ru *ruleBank = malloc(INITIAL_BIG_STRUCTURE_SIZE * sizeof(struct ru));
    int i;
    unsigned long hashIdx = 0;
    for (i = 0; i < nFiles; i++) {
        FILE *fp = fopen(filename[i], "r");
        char *line = NULL;
        char *tmp;
        size_t len = 0;
        int k = 1;                                //zmienna do sprawdzenia ilości wykonań
        char *token;
        do {
            getline(&line, &len, fp);
            if (strlen(line) > 2) {
                token = strtok(line, " =\r\n");
            }
        } while (strcmp(token, "Wzory:") != 0 || strlen(line) < 3);
        while(getline(&line, &len, fp) != -1){
            if (strlen(line) > 2) {
                token = strtok(line, "=>\r\n");
            } else continue;
            if(strcmp(token, "Szukane:") == 0){
                break;
            }
            tmp = token;
            token = strtok(NULL, " \r\n");
            hashIdx = hash(token);
            if (ruleBank[hashIdx].consequent == NULL){
                ruleBank[hashIdx].consequent = token;
                ruleBank[hashIdx].atecendent[0] = tmp;
                ruleBank[hashIdx].count = 1;
            }
            if (ruleBank[hashIdx].consequent != NULL && strcmp(ruleBank[hashIdx].consequent, tmp) == 0){
                ruleBank[hashIdx].atecendent[ruleBank[hashIdx].count] = tmp;
                ruleBank[hashIdx].count++;
            }

        }
    }
    return ruleBank;
}
