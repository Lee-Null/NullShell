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
    char *c; int i, pid, status = 0;
    printf("exec stdin : %d, stdout : %d\n", from, into);

        for(i = 0, c = cmd[i]; c != NULL; c = cmd[++i])
            printf("%s ", c);
        printf("\n");

    if((pid = fork()) == 0){
        dup2(from, STDIN_FILENO); //stdin
        dup2(into, STDOUT_FILENO); //stdout

        execvp(cmd[0], cmd);
        execv(cmd[0], cmd);
        printf("No such command\n");
        exit(0);
    }
    else{
        waitpid(pid, &status, 0);
        printf("after stdin : %d, stdout : %d\n", from, into);
        if(into != STDOUT_FILENO)
            close(into);
        if(from != STDIN_FILENO)
            close(from);
    }
}

int interpret(int *mod, char *cmds, char *dir){
    char *tok[INPUT_SIZE/TOK_SIZE];
    char *cache, *file;
    int tok_count = 0, input_fd = 0, output_fd = 1;
    int flag = -1;

    printf("TOKKEN : ");
    cache = strtok(cmds, " ");
    while(cache != NULL){
        switch (flag = pipeline(mod, cache)){
            case then:
                //pipelne in |
                break;
            case into:
                file = strtok(NULL, " ");
                if(file != NULL)
                    output_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
                if(file == NULL || output_fd < 0){
                    fprintf(stderr, "File cannot exist\n");
                    return -1;
                }
                break;
            case from:
                file = strtok(NULL, " ");
                if(file != NULL)
                    input_fd = open(file, O_RDONLY);
                if(file == NULL || input_fd < 0){
                    fprintf(stderr, "File does not exist\n");
                    return -1;
                }
                break;
            case next:
                tok[tok_count++] = NULL;
                exec(tok, output_fd, input_fd);
                input_fd = STDIN_FILENO; output_fd = STDOUT_FILENO; tok_count = 0;
                break;
            default:
                break;
        }
        if(flag < 0)
            tok[tok_count++] = cache;

        cache = strtok(NULL, " ");
    }

    /*
    do {
        printf("%s ", cache);
        switch (flag){
            case then:
                
                break;
            case into:
                output_fd = open(cache, O_CREAT | O_RDWR | O_TRUNC, 0664);
                continue;
                break;
            case from:
                input_fd = open(cache, O_RDONLY);
                if(input_fd < 0)
                    input_fd = 0;
                continue;
                break;
            case next:
                tok[tok_count++] = NULL;
                exec(tok, output_fd, input_fd);
                input_fd = STDIN_FILENO; output_fd = STDOUT_FILENO; tok_count = 0;
                break;
            default:
                break;
        }

        flag = pipeline(mod, cache);

        if(flag < 0)
            tok[tok_count++] = cache;
        
    } while((cache = strtok(NULL, " ")) != NULL);
    */
    printf("TOKKEN COUNT : %d\n", tok_count);
}