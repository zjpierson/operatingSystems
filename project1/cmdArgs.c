//--------------    cmdArgs.c    ------------//
#include "cmdArgs.h"


const char commands[NUM_CMDS][LEN_CMD] = {"quit", "hello", "help"};

void quit(char* input)
{
    printf("Now exiting...\n");
    exit(0);
}


void hello(char* input)
{
    printf("You called the hello function\n");
}


void help(char* input)
{
    printf("You called the help function\n");
}
