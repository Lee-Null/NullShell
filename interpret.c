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

int separate(int *mod, char *cmd, char **separated_cmd, char *sep){
    char *cache;
    int count = 0;
    cache = strtok(cmd, sep);
    do
        separated_cmd[count++] = cache;
    while((cache = strtok(NULL, sep)) != NULL);
    return count;
}

int escape(int *mod, char *tok){
    int kind = 0;
    for(kind = 0; kind < ESCAPE_KIND; kind++){
        if(strcmp(tok, escapes[*mod][kind]) == 0)
            break;
    }
    if(kind == ESCAPE_KIND) return -1;

    return kind;
}

int exec(char **cmd, int *fd){
    char *c; int i, pid, status = 0;
    int in = fd[STDIN_FILENO], out = fd[STDOUT_FILENO];
    // printf("exec stdin : %d, stdout : %d\n", in, out);

    // for(i = 0, c = cmd[i]; c != NULL; c = cmd[++i])
    //     printf("%s ", c);
    // printf("\n");

    pid = fork();

    if(pid == -1){
        fprintf(stderr, "Fork Error\n");
        return -1;
    }
    else if(pid == 0){
        dup2(in, STDIN_FILENO); //stdin
        dup2(out, STDOUT_FILENO); //stdout

        execvp(cmd[0], cmd);
        execv(cmd[0], cmd);
        fprintf(stderr, "No such command\n");
        return -1;
    }
    else{
        waitpid(pid, &status, 0);
        // printf("after stdin : %d, stdout : %d\n", from, into);
        if(out != STDOUT_FILENO)
            close(out);
        if(in != STDIN_FILENO)
            close(in);
    }
    return 0;
}

int interpret(int *mod, char *cmds, char *dir, char **tok, int *fds){
    char *cache, *file;
    int tok_count = 0, flag = -1;

    // printf("TOKKEN : ");
    fds[STDIN_FILENO] = STDIN_FILENO;
    fds[STDOUT_FILENO] = STDOUT_FILENO;
    // printf("input : %s\n", cmds);
    cache = strtok(cmds, " ");
    while(cache != NULL){
        // printf("before escape : %s\n", cache);
        switch (flag = escape(mod, cache)){
            case into:
                file = strtok(NULL, " ");
                if(file != NULL)
                    fds[STDOUT_FILENO] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
                if(file == NULL || fds[STDOUT_FILENO] < 0){
                    fprintf(stderr, "File cannot exist\n");
                    return -1;
                }
                break;
            case from:
                file = strtok(NULL, " ");
                if(file != NULL)
                    fds[STDIN_FILENO] = open(file, O_RDONLY);
                if(file == NULL || fds[STDIN_FILENO] < 0){
                    fprintf(stderr, "File does not exist\n");
                    return -1;
                }
                break;
            case next:
                tok[tok_count++] = NULL;
                return tok_count;
                // exec(tok, fds[STDOUT_FILENO] , fds[STDIN_FILENO]);
                // input_fd = STDIN_FILENO; output_fd = STDOUT_FILENO; tok_count = 0;
            default:
                break;
        }
        // printf("TOK : %s Flag : %d\n", cache, flag);
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
    // printf("TOKKEN COUNT : %d\n", tok_count);
    return tok_count;
}