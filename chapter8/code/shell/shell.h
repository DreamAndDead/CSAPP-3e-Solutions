/*
 * shell.h
 */
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parse_line(char *buf, char **argv);
int builtin_command(char **argv);

