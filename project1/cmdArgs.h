//--------------    cmdArgs.h    ------------//

#ifndef __CMDARGS_h__
#define __CMDARGS_h__

#include <stdio.h>
#include <string.h>     //strtok
#include <stdlib.h>     //exit

#define NUM_CMDS 5
#define LEN_CMD 100

extern const char commands[NUM_CMDS][LEN_CMD];
extern void (*func[NUM_CMDS]) (char* input);

void quit(char* input);
void cmdnm(char* input);
void pid(char* input);
void systat(char* input);
void help(char* input);

#endif
