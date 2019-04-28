#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#include "send.h"

int send(int pid, int sig){
    return kill(pid, sig);
}