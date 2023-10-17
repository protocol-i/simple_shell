#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WRITE_BUF_SIZE 1024

/* Data Structures */

typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;

typedef struct info_s
{
    int argc;
    char **argv;
    char **env;
    int status;
    int err_num;
    int line_count;
    int readfd;
    char *fname;
    list_t *history;
    list_t *alias;
} info_t;

/* Function Prototypes */

/* main.c */
int main(int argc, char **argv, char **env);

/* shell_utilities.c */
int is_interactive(info_t *info);
int is_delimiter(char c, char *delimiters);
int is_alpha(int c);
int string_to_int(char *s);

/* string_functions.c */
char *_strncpy(char *dest, const char *src, size_t n);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(const char *s, int c);

/* file_operations.c */
int file_exists(const char *filename);
ssize_t read_textfile(const char *filename, char **text, size_t letters);

/* error_functions.c */
void print_error(info_t *info, const char *estr);

/* environment.c */
char *_getenv(info_t *info, const char *name);
int _setenv(info_t *info, const char *name, const char *value);
int _unsetenv(info_t *info, const char *name);
int populate_env_list(info_t *info);

/* history.c */
void print_list(list_t *head);
list_t *add_node_end(list_t **head, const char *str, int len);
list_t *create_history_list(char *filename);
int save_history(list_t *head, const char *filename);

#endif /* SHELL_H */

