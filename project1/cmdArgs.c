//--------------    cmdArgs.c    ------------//
#include "cmdArgs.h"


void (*func[NUM_CMDS]) (char* input) = {quit, cmdnm, pid, systat, help};
const char commands[NUM_CMDS][LEN_CMD] = {"quit", "cmdnm", "pid", "systat", "help"};

void quit(char* input)
{
    printf("Now exiting...\n");
    exit(0);
}


void cmdnm(char* input)
{
    char pid[10] = {0};
    printf("You called the cmdnm function\n");
    printf("the second argument is %s!\n", input);

    
}


void pid(char* input)
{
    printf("You called the pid function\n");
}



void systat(char* input)
{
    printf("You called the systat function\n");
}

void help(char* input)
{
    printf("Usage Options:");
    printf("\n\tcmdnm  <pid>\t - return name of a given process id");
    printf("\n\tpid  <command>\t - return pid of a given command");
    printf("\n\tsystat\t\t - print process information\n");
}
