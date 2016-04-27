#include "checkData.h"

void dataMissing(char *word){
    printf("W bazie nie ma danej:\n %s\nNie moge dalej liczyc!\n.", word);
    exit(1);
}

void dataEmpty(char *word){
    printf("Dana %s nie ma wartosci.\n", word);
}

void dataDuplicate(char *word){
    printf("Dana %s jest zduplikowana.\n", word);
}

void dataInconsistent(char *word){
    printf("Dana %s jest zduplikowana.\n", word);
    exit(1);
}