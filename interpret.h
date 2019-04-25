#define TOK_SIZE 10
#define CMD_SIZE 128
#define PIPE_SIZE 128
#define ESCAPE_KIND 4

enum escape_kind {then = 0, into = 1, from = 2, next = 3, non_pipe = 4};
enum mode {basic, custom};

char *escapes[2][ESCAPE_KIND];

int env(char *);
int escape(int *, char *);
int separate(int *, char *, char **, char *);
int exec(char **, int *);
int interpret(int *, char *, char *, char **, int *);