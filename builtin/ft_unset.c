#include "minishell.h"

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

void detach_node (t_env *current)
{
    t_env *tmp;

    /*
        見つかったやつのポインタの一個前の次を見つかったやつの次に変更させるだけ
        prev->next
        current->next
    */
   tmp->next = current->next;
   tmp->prev = current->prev;
   current->prev->next = tmp->next;
   current->next->prev = tmp->prev;

   free(current->menvp);
   free(current); 
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
    while (current->prev != NULL)
    {
        printf("%s\n", current->menvp);
        // if (current->next != NULL)
            current = current->prev;
        // else
            // break;
    }
}


int main (int argc, char **argv, char **envp)
{
    t_env **word_list;
    t_env *found_str;

    word_list = (t_env **)malloc(sizeof(t_env));
    word_list = ft_create_node(word_list, envp);

    // print_node(word_list);
    found_str = ft_find_env(word_list, argv[1]);
    detach_node(found_str);
    print_node(word_list);
}