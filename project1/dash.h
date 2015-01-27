#ifndef __DASH_H__
#define __DASH_H__

#include <stdio.h>
#include <string.h>     //strtok
#include <stdlib.h>     //exit

#define NUM_CMDS 3
#define LEN_CMD 100

const char commands[NUM_CMDS][LEN_CMD] = {"quit", "hello", "help"};

void quit(char* input);
void hello(char* input);
void help(char* input);

#endif
