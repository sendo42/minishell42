#include "builtins.h"
// // envpはexportで書き換えるから、どこかに取っておいて書き換えられるようにしないといけない。

// /*
// 1,envp で得られたものを構造体に入れる
// 2,=が見つかるまで探し、
//     左側があれば再代入
//     右側があれば新規に作成する。
// */

// // ここからは最初にenvメモリを作るとき
// t_env *ft_create_node (t_env *create, char *envp)
// {
//     t_env *node;
//     int i;

//     i = ft_strlen(envp);
//     node = (t_env *)malloc(sizeof(t_env));
//     if( node == NULL)
//         printf("nooooo\n");
//     if(create == NULL)
//         create = node;
//     else
//         create->next = node;
//     node->menvp = strdup(envp);
//     return node;
// }

// void free_node (t_env *node)
// {
//     t_env *tmp;
//     int i;

//     i = 0;
//     while(node != NULL)
//     {
//         tmp = node;
//         node = node->next;
//         printf("i : %d\n",i);
//         if(tmp != NULL)
//         {
//             free(tmp->menvp);
//             free(tmp);
//         }
//         i++;
//     }
// }
// // ここまでenvメモリ

// // ここから書き換えする関数
// /*
//     HOME=/Users/sendo
//     USER=sendo
//     が文字列で入ってきたら、
//     env_dict に＝までの左の文字列が一致するやつがあるか探す。
//     見つかったらそれの=より右を書き換える。

//     環境変数cdをすると、PWDがその場所に毎回変わる。
// */



// void ft_export (t_env *env_dict, char *env_change)
// {
//     while( env_dict != NULL)
//     {
//         if(ft_strcmp_flag(env_dict, env_change))
//         {

//         }
//         env_dict = env_dict->next;
//     }
// }
// // ここまで書き換えexport関数

// // デバッグ関数
// void print_node(t_env *start)
// {
//     while(start != NULL)
//     {
//         printf("str: %s\n",start->menvp);
//         start = start->next;
//     }
// }
// // 

// int main(int argc, char **argv, char **envp)
// {
//     t_env *neko;
//     t_env *tmp;
//     int i;

//     i = 0;
//     while(envp[i] != NULL)
//     {
//         neko = ft_create_node(neko,envp[i]);
//         if(i == 0)
//             tmp = neko;
//         i++;
//     }
//     print_node(tmp);
//     free_node(tmp);
//     return 0;
// }

// // __attribute__((destructor))
// // void    destructor(void)
// // {
// //     int     status;
// //     char    buf[50];

// //     snprintf(buf, 50, "leaks %d &> leaksout", getpid());
// //     status = system(buf);
// //     if (status)
// //     {
// //         write(2, "leak!!!\n", 8);
// //         system("cat leaksout >/dev/stderr");
// //         exit(1);
// //     }
// // }

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	while (n--)
		((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	return (dst);
}

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		size;

	size = ft_strlen(s1) + 1;
	cpy = (char *)malloc(size);
	if (cpy == NULL)
		return (NULL);
	ft_memcpy(cpy, s1, size);
	return (cpy);
}

t_env **ft_create_node(t_env **create, char **envp)
{
    t_env *create_prev = NULL;
    t_env *current = NULL;

    *create = NULL;
    while (*envp != NULL)
    {
        current = (t_env *)malloc(sizeof(t_env));
        current->menvp = ft_strdup(*envp);
        current->next = NULL;
        if (create_prev != NULL)
        {
            create_prev->next = current;
            current->prev = create_prev;
        }
        else
        {
            *create = current;
            current->prev = NULL;
        }
        create_prev = current;
        envp++;
    }
    return create;
}


void print_node(t_env **node)
{
    t_env *current = *node;

    while (current->next != NULL)
    {
        printf("%s\n", current->menvp);
        // if (current->next != NULL)
            current = current->next;
        // else
            // break;
    }
    printf("\n\n\n\n");
    while (current != NULL)
    {
        printf("%s\n", current->menvp);
        // if (current->next != NULL)
            current = current->prev;
        // else
            // break;
    }
}

/*
ここからexportを作る
1,envp で得られたものを構造体に入れる
2,=が見つかるまで探し、（）
    左側があれば再代入
    右側があれば新規に作成する。

create
*/

// メモリenv_dictを作る関数

int ft_strlen_equal (char *str)
{
    int i;

    i = 0;
    if(str == NULL)
        return -1;
    while (str[i] != '\0' && str[i] != '=')
        i++;
    return i;
}

t_env *ft_find_env(t_env **env_dict, char *str)
{
    int i;
    int word_length;

    i = ft_strlen_equal(str);
    t_env *current = *env_dict;

    while (current != NULL)
    {
        word_length = ft_strlen_equal(current->menvp);
        printf("i : %d word :%d str : %s\n",i, word_length, current->menvp);
        if(ft_strncmp(current->menvp, str,i) == 0 && i == word_length )
        {
            printf("str id found :%s \n",current->menvp);
            return current;
        }
        current = current->next;
    }
    return NULL;
}


void write_env (t_env *env_str, char *str)
{
    free(env_str->menvp);
    env_str->menvp = NULL;
    env_str->menvp = ft_strdup(str);
}


// int main (int argc, char **argv, char **envp)
// {
//     t_env **word_list;
//     t_env *found_str;

//     word_list = (t_env **)malloc(sizeof(t_env));
//     word_list = ft_create_node(word_list, envp);

//     // print_node(word_list);
//     found_str = ft_find_env(word_list, argv[1]);
//     printf("this is %s\n",found_str->menvp);
//     write_env (found_str, argv[1]);
//     print_node(word_list);

// }