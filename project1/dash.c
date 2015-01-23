#include "dash.h"

const char commands[NUM_CMDS][LEN_CMD] = {"quit", "hello", "help"};

int main()
{
    int i;
    char* input;
    char* cmd;

    printf("\n");
    //Enter command loop (Read Eval Print Loop)
    while(1)
    {
        printf("dash> ");
        scanf("%s", input);
        
        //Get command option from user
        cmd = strtok(input, " ");

        for(i = 0; i < NUM_CMDS; i++)
        {
//            if(!strcmp(cmd, commands[i]))
//            {
//                printf("%s is a command!\n", cmd);
//            }
        }
    }

    return 0;
}
