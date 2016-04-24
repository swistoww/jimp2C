#ifndef backward_h
#define backward_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

struct bw{
    char *shortcut;
    char *rule;
    int value;
};

struct ar *backwardThinking(struct ar *dataBank, struct ru *ruleBank);

struct bw *simpleBackwardThinking (char *rule, struct ar *dataBank, struct bw *subRulesBank);

#endif