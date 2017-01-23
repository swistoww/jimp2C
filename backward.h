#ifndef backward_h
#define backward_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

struct ar *backwardThinking(struct ar *dataBank, struct ru *ruleBank);
struct ar *simpleBackwardThinking (struct ar *dataBank, char *rule, int ruleValue);

#endif