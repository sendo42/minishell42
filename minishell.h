#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int ft_strlen(char *str);
char *ft_strjoin(char *str1, char *str2);
int ft_strcmp_flag (char *str1, char *str2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

typedef struct s_env 
{
    char *menvp;
    struct s_env *next;
    struct s_env *prev;
} t_env;
