#define TOK_SIZE 10
#define CMD_SIZE 128
#define PIPE_SIZE 128
#define ESCAPE_KIND 4

enum escape_kind {then = 0, into = 1, from = 2, next = 3, non_pipe = 4};
enum mode {basic, custom};

char *escapes[2][ESCAPE_KIND];

int env(char *);

/**
 * Fuction: escape
 * --------------
 * 
 * mod : the mode of this shell
 * tok : tokken to check if it is escape character(word).
 * 
 * return : positive if it is escape charater(word), negative if error is occured
*/
int escape(int *, char *);


/**
 * Fuction: separate
 * --------------
 * separate command by given string.
 * 
 * mod : the mode of this shell
 * cmd : command to separate
 * separated_cmd : separated strings of given command
 * sep : separator string
 * 
 * return : the number of separated strings
*/
int separate(int *, char *, char **, char *);


/**
 * Fuction: exec
 * --------------
 * execute the command
 * 
 * cmd : commands to execute
 * fd : file descriptions to execute with.
 * 
 * return : 0 if no error otherwise if error.
*/
int exec(char **, int *);


/**
 * Fuction: input
 * --------------
 * intepret a command and separate a command to the tokkens
 * 
 * mod : the mode of this shell
 * cmds : a command to interpret
 * dir : current directory to extend
 * tok : interpreted tokkens
 * fds : file descriptions to build pipeline
 * 
 * return : the number of tokkens.
*/
int interpret(int *, char *, char *, char **, int *);