#include "minishell.h"

// envpはexportで書き換えるから、どこかに取っておいて書き換えられるようにしないといけない。


void ft_env (char *envp[])
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        printf("\n%d : %s", i, envp[i]);
        i++;
    }

}



int main(int argc, char **argv, char *envp[])
{
    ft_env(envp);
    return 0;
}