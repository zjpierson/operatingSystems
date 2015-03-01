//--------------    cmdArgs.h    ------------//

#ifndef __CMDARGS_h__
#define __CMDARGS_h__

#include <stdio.h>
#include <string.h>     //strtok(), strcpy()
#include <stdlib.h>     //exit
#include <signal.h>     //signal(), SIG vars
#include <dirent.h>     //DIR, opendir(), readdir(), closedir()
#include <sys/time.h>       //getrusgae()
#include <sys/resource.h>   //getrusgae()
#include <unistd.h>         //fork(), execvp(), chdir()
#include <errno.h>          //errno
#include <fcntl.h>          //O_RDONLY

#define NUM_CMDS 8
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
int redirect_pipe(char* args[]);
void redirected_input(char *args[], char* fileName);
void redirected_output(char *args[], char* fileName);
void do_pipe(char* args[], int index);
void send_signal(char* args[]);
void call(char *args[]);
void sig_handler(int signo);
int tokenize(char* input, char* args[]);

#endif
