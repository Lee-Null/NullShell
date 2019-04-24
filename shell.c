#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"
#include "interpret.h"

char dir[PATH_SIZE];

int input(){
    char cmd[INPUT_SIZE];
    int status = 1;
    int mod = basic;
    while(status){
        printf("%s with %s: ", dir, mod == basic ? "basic" : "custom");
        // scanf("%s", cmd);
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd) - 1] = '\0';
        if(strcmp(cmd, "") == 0) continue;

        status = interpret(&mod, cmd, dir);
    }
    return status;
}

int load(){
    getcwd(dir, sizeof(dir));

    pipes[basic][then] = "|";
    pipes[basic][into] = ">";
    pipes[basic][from] = "<";
    pipes[basic][next] = ";";

    pipes[custom][then] = "then";
    pipes[custom][into] = "into";
    pipes[custom][from] = "from";
    pipes[custom][next] = "next";

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