#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"
#include "interpret.h"

char dir[PATH_SIZE];

int input(){
    char cmd[INPUT_SIZE];
    char *nseparated[INPUT_SIZE/CMD_SIZE];
    char *cmdseparated[INPUT_SIZE/CMD_SIZE];
    char *interpreted[INPUT_SIZE/TOK_SIZE];
    int fd[2] = {0, 1};
    
    int status = 1, ncount = 0, cmdcount = 0, tokcount = 0;
    int i = 0, j = 0;
    int mod = basic;
    while(status){
        printf("%s with %s: ", dir, mod == basic ? "basic" : "custom");
        // scanf("%s", cmd);
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd) - 1] = '\0';
        if(strcmp(cmd, "") == 0) continue;

        ncount = separate(&mod, cmd, nseparated, escapes[mod][next]);
        printf("count : %d\n", ncount);
        for(i = 0; i < ncount; i++){
            printf("%s\n", nseparated[i]);
            cmdcount = separate(&mod, nseparated[i], cmdseparated, escapes[mod][then]);

            for(j = 0; j < cmdcount; j++){
                tokcount = interpret(&mod, cmdseparated[i], dir, interpreted, fd);
                printf("in : %d out : %d\n", fd[STDIN_FILENO], fd[STDOUT_FILENO]);
                printf("interpreted : ");
                for(int k = 0; k < tokcount; k++)
                    printf("%s ", interpreted[k]);
                printf("\n");
                exec(interpreted, fd);
                //TODO
            }
            printf("TOK : %d\n", tokcount);
        }
    }
    return status;
}

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
    int status = 0;

    if(load() < 0){
        fprintf(stderr, "Load error\n");
        exit(1);
    }

    status = input();
    return status;
}