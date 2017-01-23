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
    int x;
    for ( x= 0;  x < INITIAL_BIG_STRUCTURE_SIZE; x++) {
        dataBank[x].word = malloc(10* sizeof(char));
        dataBank[x].word = NULL;
        dataBank[x].value = NULL;
        dataBank[x].rep = NULL;
        dataBank[x].kind = NULL;
    }
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
                    if (strcmp(token, "Wzory:") == 0) {
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
                    if (dataBank[hashIdx].rep == NULL) {

                        if (strcmp(token, "F") == 0) {
                            dataBank[hashIdx].value = 0;
                            dataBank[hashIdx].kind = 'D';
                            dataBank[hashIdx].rep = "F";
                        } else if (strcmp(token, "T") == 0) {
                            dataBank[hashIdx].value = 1;
                            dataBank[hashIdx].kind = 'D';
                            dataBank[hashIdx].rep = "T";
                        } else if (strcmp(token, "?") == 0) {
                            dataBank[hashIdx].kind = 'S';
                        } else {
                            printf("Plik z danymi jest niepoprawny. Dana %s ma nieprawidlowa wartosc.", dataBank[hashIdx].word);
                            exit(1);
                        }
                    } else {
                        printf("Dana %s jest zduplikowana!", dataBank[hashIdx].word);
                        exit(1);
                    }
                }
            }
        }
    }
    return dataBank;
}

struct ru *readRules(char **filename, int nFiles) {

    struct ru *ruleBank = malloc(INITIAL_SIZE * sizeof(struct ru));
    int j = 0;
    int s = 0;
    int i;
    for (i = 0; i < nFiles; i++) {
        FILE *fp = fopen(filename[i], "r");
        char *line = NULL;
        char *tmp;
        size_t len = 0;
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
                if(strcmp(token, "Szukane:") == 0){
                    break;
                }
            } else continue;
            s++;
            if ((ruleBank = realloc(ruleBank,(s * INITIAL_SIZE) * sizeof(struct ru))) == NULL){
                printf("Nie moge zaalokowac ponownie pamieci");
            }
            tmp = strdup(token);
            tmp[strlen(tmp)-1] = '\0';
            token = strtok(NULL, " >\r\n");
            ruleBank[j].consequent = strdup(token);
            ruleBank[j].atecendent = strdup(tmp);
            j++;
        }
    }

    ruleBank[0].counter = s;
    return ruleBank;
}
