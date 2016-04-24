#include "checkData.h"

void dataMissing(char *word){
    printf("W bazie nie ma danej %s.\n.", word);
}

void dataEmpty(char *word){
    printf("Dana %s nie ma wartosci.\n", word);
}

void dataDuplicate(char *word){
    printf("Dana %s jest zduplikowana.\n", word);
}

void dataInconsistent(char *word){
    printf("Dana %s jest zduplikowana.\n", word);
}