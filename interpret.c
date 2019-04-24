#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "shell.h"
#include "interpret.h"

int env(char *cmd){

}

int pipeline(int *mod, char *tok){
    int kind = 0;
    for(kind = 0; kind < PIPE_KIND; kind++){
        if(strcmp(tok, pipes[*mod][kind]) == 0)
            break;
    }
    if(kind == PIPE_KIND) return -1;

    return kind;
}

int exec(char **cmd, int into, int from){
    if(fork() == 0){
        dup2(0, from);
        dup2(1, into);
        execvp(cmd[0], cmd);
        execv(cmd[0], cmd);
        printf("No such command\n");
        exit(1);
    }
    else{
        wait(NULL);
    }
}

int interpret(int *mod, char *cmds, char *dir){
    char *tok[INPUT_SIZE/TOK_SIZE];
    char *cache;
    int tok_count = 0, input_fd = 0, output_fd = 1;
    int flag = -1;

    printf("TOKKEN : ");
    cache = strtok(cmds, " ");
    do {
        printf("%s ", cache);
        switch (flag){
            case then:
                
                break;
            case into:
                input_fd = open(cache, O_CREAT | O_WRONLY);
                break;
            case from:
                output_fd = open(cache, O_RDONLY);
                break;
            case next:
                tok[tok_count++] = NULL;
                exec(tok, input_fd, output_fd);
                input_fd = 0; output_fd = 1; tok_count = 0;
                break;
            default:
                break;
        }

        flag = pipeline(mod, cache);

        if(flag < 0)
            tok[tok_count++] = cache;
        
    } while((cache = strtok(NULL, " ")) != NULL);
    printf("TOKKEN COUNT : %d\n", tok_count);
}