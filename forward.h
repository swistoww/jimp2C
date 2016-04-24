#ifndef forward_h
#define forward_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ar *forwardThinking(struct ar *dataBank, struct ru *ruleBank);
int simpleThinking (char *rule, struct ar *dataBank);

#endif
