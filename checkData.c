#include "checkData.h"

void dataMissing(){
    printf("W bazie nie ma potrzebnej danej. Nie moge dalej liczyc!\n.");
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