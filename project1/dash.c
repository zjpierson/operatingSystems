//--------------    dash.c    ------------//

#include "cmdArgs.h"


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
            if(!strcmp(cmd, commands[i]))
            {
                //Call appropriate function
                (*func[i]) (input);
                break;
            }
        }
    }

    return 0;
}


//void hello(char* input)
//{
//    printf("You called the hello function\n");
//}
