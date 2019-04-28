#include <stdio.h>

void ltrim(char *src, char *dst){
    int p = 0;
    while(*src == '\n' || *src == ' ' || *src == '\t') src++;
    while(*src != '\0'){
        dst[p++] = *src;
        src++;
    }
    dst[p] = '\0';
}

void rtrim(char *str){
    int p = 0;
    while(*str != '\0') str++;
    str--;
    while(*str == '\n' || *str == ' ' || *str == '\t'){
        *str = '\0'; str--;
    }
}

void trim(char *src, char *dst){
    ltrim(src, dst);
    rtrim(dst);
}