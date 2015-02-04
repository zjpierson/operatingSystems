//--------------    cmdArgs.c    ------------//
#include "cmdArgs.h"


void (*func[NUM_CMDS]) (char* input) = {quit, quit, cmdnm, pid, systat, help};
const char commands[NUM_CMDS][LEN_CMD] = 
{
    "quit", 
    "exit", 
    "cmdnm", 
    "pid", 
    "systat", 
    "help"
};

void quit(char* input)
{
    printf("Now exiting...\n");
    exit(0);
}


void cmdnm(char* input)
{
    char path[50] = {"/proc/"};
    char *pid;
    char cmdname[50];
    FILE *fp = NULL; 

    //Get the next command
    pid = strtok(input, " \t");
    if(pid == NULL)
    {
        printf("*Error: must specify a pid (dash>  cmdnm  <pid>)");
        return;
    }

    //add pid to the file path: "/proc/<pid>"
    strcat(path, pid);

    /************************************************
     *  NOTE:                                       *
     *  full path name can be found in cmdline      *
     *                                              *
     ***********************************************/
    //add the comm file to the path:"/proc/<pid>"
    strcat(path, "/comm");

    //open the file
    fp = fopen(path, "r");
    if( fp == NULL )
    {
        printf("*Error: invalid <pid>");
        return;
    }

    //the command name is the first thing inside the comm file
    fscanf(fp, "%s", cmdname);
    //print the command name that belongs to <pid>
    printf("%s", cmdname);

    fclose(fp);
}


//loop though all pid directories and return pid numbers that match 
//any substring of the given command
//finding all sub directories using dirent.h should be given credit to:
//http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//
void pid(char* input)
{
    DIR * dir;
    DIR * tmpdir;
    struct dirent *ent;
    if( (dir = opendir("/proc")) == NULL )
    {
        printf("**Error: could not open /proc directory");
        return;
    }

    //find all pids that match any substring of the given command
    while( (ent = readdir(dir)) != NULL )
    {
        printf("%s\n", ent->d_name);
        char path[50] = {"/proc/"};
        char *pid;
        char cmdname[50];
        FILE *fp = NULL; 

        //Get the next command
        pid = strtok(input, " \t");
        if(pid == NULL)
        {
            printf("*Error: must specify a pid (dash>  cmdnm  <pid>)");
            return;
        }

        //add pid to the file path: "/proc/<pid>"
        strcat(path, pid);

        /************************************************
         *  NOTE:                                       *
         *  full path name can be found in cmdline      *
         *                                              *
         ***********************************************/
        //add the comm file to the path:"/proc/<pid>"
        strcat(path, "/comm");

        //open the file
        fp = fopen(path, "r");
        if( fp == NULL )
        {
            printf("*Error: invalid <pid>");
            return;
        }

        //the command name is the first thing inside the comm file
        fscanf(fp, "%s", cmdname);
        //print the command name that belongs to <pid>
        printf("%s", cmdname);

        fclose(fp);
    }

    closedir(dir);

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
