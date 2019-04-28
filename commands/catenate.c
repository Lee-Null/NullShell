#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFF_SIZE 128

int catenate(char **files, int argc){
    int i = 0, fd = 0, size;
    unsigned char buff[BUFF_SIZE];

    if(argc == 0){
        fprintf(stderr, "[Usage] : catenate <files>");
        return -1;
    }
    for(i = 0; i < argc; i++){
        fd = open(files[i], O_RDONLY);

        if(fd < 0){
            fprintf(stderr, "FILE ERROR");
            return -1;
        }

        while((size = read(fd, buff, sizeof(buff)) > 0))
            write(stdout, buff, read);
        
        close(fd);
    }
    return 0;
}