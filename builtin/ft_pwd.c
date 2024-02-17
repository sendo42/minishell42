#include "minishell.h"

void ft_pwd ()
{
    printf("%s\n",getcwd(NULL, 1024));
}

int main()
{
    ft_pwd();

}