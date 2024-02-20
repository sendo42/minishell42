#include "builtins.h"
int ft_strlen(char *str)
{
    int i;

    i = 0;
    if(str == NULL)
        return -1;
    while(str[i])
    {
        i++;
    }
    return i;
}

char *ft_strjoin(char *str1, char *str2)
{
    int count1;
    int count2;
    char *str;

    count1 = ft_strlen(str1);
    count2 = ft_strlen(str2);
    if((count1 == -1 || count2 == -1) || (str1 == NULL || str2 == NULL))
        return NULL;
    else
    {
        str = malloc(count1 + count2);
        memcpy(str, str1, count1);
        memcpy(str + count1, str2, count2);
        str[count1 + count2] = '\0';
    }
    return str;
}

// int ft_strcmp_flag (char *str1, char *str2)
// {
//     int i;
//     int flag;
    
//     flag = 0;
//     i = 0;
//     while (str1[i] != NULL && str2[i] != NULL)
//     {
//         if(str1[i] == str2[i])
//             i++;
//         if(str2[i] == '\0' && i != 0)
//         {
//             flag = 1;
//             break;
//         }
//     }
//     return flag;
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i + 1 < n && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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