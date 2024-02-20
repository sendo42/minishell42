#include "builtin/builtins.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <fcntl.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int ft_strlen(char *str);
// char *ft_strjoin(char *str1, char *str2);
// int ft_strcmp_flag (char *str1, char *str2);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);

// typedef struct s_env 
// {
//     char *menvp;
//     struct s_env *next;
//     struct s_env *prev;
// } t_env;

typedef struct s_cmd {
    char *cmd;      //echo
    char **option;   //-n
    char **arg_str;  //aaa
    int flag;
    struct s_cmd *next;     
}   t_cmd;

typedef struct s_info {
    int pipe_fd[2];
    int tmp_fd;
    pid_t pid;
}   t_info;

// cmd2 の設定
//  cc builtin/ft_cd.c test.c builtin/ft_lib.c 

