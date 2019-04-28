#include "commands/catenate.h"
#include "commands/help.h"
#include "commands/list.h"
#include "commands/makedir.h"
#include "commands/send.h"
#include "commands/setmode.h"

/**
 * Fuction: exe
 * --------------
 * execute the special command for this shell and common command.
 * 
 * TODO combine to exec() of interpret()
 * 
 * cmd : commands to execute
 * count : the number of command
 * dir : current directory
 * fd : file descriptions to execute with.
 * 
 * return : 0 if no error otherwise if error.
*/
int exe(int *,char **, int , char *, int *);