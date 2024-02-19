#include "builtins.h"

char *trim_follow_slash (char *str)
{
    int count;
    char *start;
    char *path;

    start = str;
    count = 0;

    while (*str != '\0' && count < 3)
    {
        if(strchr("/",*str) != NULL)
        {
            // printf("str: %s\n",str);
            count++;
        }
        str++;
    }
    if (count == 3)
    {
        path = (char *)malloc(str - start);
        memcpy(path, start, str - start);
        // printf("path :%s",path);  
    }
    return path;
}//こんなことしなくても、envpのHOMEを参照してそこにいけばできる


void cd_home (void)
{
    char *str;

    str = getcwd(NULL,1024);
    str = trim_follow_slash (str);
    if(chdir(str) == -1)
        exit(1);//perror?
    free(str);
    system("pwd");
    write(1,"b",1);
    return ;
}

void ft_cd (char *str)
{
    int flag;
    
    if(str == NULL)
        cd_home();
    else if(*str == '\0')
        return ;
    else
    {
        flag = chdir(str);
        if(flag == 0)
        {
            printf("%s\n",getcwd(NULL,1024));
            //perror?
        }
        if(flag == -1)
        {
            printf("cd: no such file or directory:%s",str);
            exit(1);
        }
    }
}

// int main (int argc, char **argv)
// {
//     char *str;

//     ft_cd(argv[1]);
//     return 0;
//     // https://www.ibm.com/docs/ja/spectrum-protect/8.1.9?topic=parameters-file-specification-syntax
//     // mac は1024 windows は256らしい。MAXPATHLENで検索

//         system("ls");

//     // systemというコマンドでc言語内でコマンドが使える
//     //そのプロセスが終了すると親プロセスには反映されない。こプロセスには反映される。だから一つのプログラム内で行わなければならない。
// }