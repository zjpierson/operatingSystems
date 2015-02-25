//--------------    cmdArgs.h    ------------//

#ifndef __CMDARGS_h__
#define __CMDARGS_h__

#include <stdio.h>
#include <string.h>     //strtok
#include <stdlib.h>     //exit
#include <dirent.h>     //DIR, opendir(), readdir(), closedir()
#include <sys/time.h>       //getrusgae()
#include <sys/resource.h>   //getrusgae()
#include <unistd.h>         //fork(), execvp()

#define NUM_CMDS 6
#define LEN_CMD 100

extern const char commands[NUM_CMDS][LEN_CMD];
extern void (*func[NUM_CMDS]) (char* input);

void quit(char* input);
void cmdnm(char* input);
void pid(char* input);
void systat(char* input);
void help(char* input);
void display_cmdNames();
void display_pid();

#endif
