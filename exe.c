#include <string.h>
#include <stdlib.h>

#include "exe.h"

int exe(int * mod, char **cmd, int count, char *dir, int *fds){
    if(strcmp(cmd[0], "list") == 0)
        list(dir); //TODO if "list directory" is called, it cannot execute.
    else if(strcmp(cmd[0], "help") == 0)
        help();
    else if(strcmp(cmd[0], "catenate") == 0)
        catenate(cmd, count);
    else if(strcmp(cmd[0], "makedir") == 0)
        makedir(cmd[1]);
    else if(strcmp(cmd[0], "send") == 0)
        send(atoi(cmd[2]), atoi(cmd[1]));
    else if(strcmp(cmd[0], "setmode") == 0)
        setmode(mod, atoi(cmd[1]));
    else
    {
        /* execute code */
    }
    
}