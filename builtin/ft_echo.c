#include "builtins.h"
void ft_echo (char *option, char **str)
{
    int i;
    int count;
    i = 0;
    
    while(str[i] != NULL)
    {
        write(1, " ",1);
        count = ft_strlen(str[i]);
        write(1,str[i], count);
        i++;
    }
    if(option == NULL)
    {
        write(1,"\n",1);
    }
}


// int main(int argc, char**argv)
// {
//     int i;
//     i = 0;
//     argc = 0;
    
//     ft_echo("-n", argv);
//     return 0;
// }

