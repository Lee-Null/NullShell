#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"
#include "interpret.h"
#include "util.h"

char dir[PATH_SIZE];

/**
 * Fuction: input
 * --------------
 * get inputs from user.
 * 
 * return : 0 if no error otherwise if error.
*/
int input(int *mod){
    char cmd[INPUT_SIZE];
    char *nseparated[INPUT_SIZE/CMD_SIZE];
    char *cmdseparated[INPUT_SIZE/CMD_SIZE];
    char *interpreted[INPUT_SIZE/TOK_SIZE];
    int fd[2] = {0, 1};
    
    int status = 0, ncount = 0, cmdcount = 0, tokcount = 0;
    int i = 0, j = 0;
    
    printf("%s with %s: ", dir, *mod == basic ? "basic" : "custom");
    // scanf("%s", cmd);
    fgets(cmd, sizeof(cmd), stdin);
    cmd[strlen(cmd) - 1] = '\0';
    trim(cmd, cmd);
    if(strcmp(cmd, "") == 0) return 0;

    ncount = separate(mod, cmd, nseparated, escapes[*mod][next]);
    // printf("count : %d\n", ncount);
    for(i = 0; i < ncount; i++){
        // printf("B%s\n", nseparated[i]);
        trim(nseparated[i], nseparated[i]);
        // printf("%s\n", nseparated[i]);
        cmdcount = separate(mod, nseparated[i], cmdseparated, escapes[*mod][then]);

        // printf("cmds : %d\n", cmdcount);
        for(j = 0; j < cmdcount; j++){
            trim(cmdseparated[j], cmdseparated[j]);
            tokcount = interpret(mod, cmdseparated[j], dir, interpreted, fd);
            // printf("in : %d out : %d\n", fd[STDIN_FILENO], fd[STDOUT_FILENO]);
            // printf("interpreted : ");
            // for(int k = 0; k < tokcount; k++)
            //     printf("I%s ", interpreted[k]);
            // printf("\n");
            status = exec(interpreted, fd);
            //TODO
        }
        // printf("TOK : %d\n", tokcount);
    }
    return status;
}

/**
 * Fuction: load
 * --------------
 * load the settings.
*/
int load(){
    getcwd(dir, sizeof(dir));

    escapes[basic][then] = "|";
    escapes[basic][into] = ">";
    escapes[basic][from] = "<";
    escapes[basic][next] = ";";

    escapes[custom][then] = "then";
    escapes[custom][into] = "into";
    escapes[custom][from] = "from";
    escapes[custom][next] = "next";

    return 0;
}

int main(void){
    int status = 0, mod = basic;

    if(load() < 0){
        fprintf(stderr, "Load error\n");
        exit(1);
    }
    while(status >= 0)
        status = input(&mod);
    return status;
}