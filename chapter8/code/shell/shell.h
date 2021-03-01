/*
 * shell.h
 */
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parse_line(char *buf, char **argv);
int builtin_command(char **argv);

/*
 * > fg %10
 * or
 * > fg 3234
 * parse and return right jid/pid
 *
 * if
 * > fg adaf
 * or other wrong format, return -1
 */
int parse_id(char* s);

// test all functions
void test_shell(void);

