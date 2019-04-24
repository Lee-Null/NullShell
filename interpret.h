#define TOK_SIZE 10
#define PIPE_SIZE 128
#define PIPE_KIND 4

enum pipe {then = 0, into = 1, from = 2, next = 3, non_pipe = 4};
enum mode {basic, custom};

char *pipes[2][PIPE_KIND];

int env(char *);
int pipeline(int *, char *);
int exe(char **, int, int);
int interpret(int *, char *, char *);