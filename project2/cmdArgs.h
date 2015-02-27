//--------------    cmdArgs.h    ------------//

#ifndef __CMDARGS_h__
#define __CMDARGS_h__

#include <stdio.h>
#include <string.h>     //strtok(), strcpy()
#include <stdlib.h>     //exit
#include <dirent.h>     //DIR, opendir(), readdir(), closedir()
#include <sys/time.h>       //getrusgae()
#include <sys/resource.h>   //getrusgae()
#include <unistd.h>         //fork(), execvp(), chdir()
#include <errno.h>          //errno

#define NUM_CMDS 7
#define LEN_CMD 100

extern const char commands[NUM_CMDS][LEN_CMD];
extern void (*func[NUM_CMDS]) (char* args[]);

void quit(char* args[]);
void cmdnm(char* args[]);
void pid(char* args[]);
void systat(char* args[]);
void help(char* args[]);
void cd(char* args[]);
void display_cmdNames();
void display_pid();
void proc_status();
void redirected_output(char *args[], char* fileName);
void call(char *args[], int size);
int tokenize(char* input, char* args[]);

#endif
