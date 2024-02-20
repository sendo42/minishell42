#include "builtins.h"

/*
ここからexportを作る
1,envp で得られたものを構造体に入れる
2,=が見つかるまで探し、（）
    左側があれば再代入
    右側があれば新規に作成する。

create
*/

// メモリenv_dictを作る関数


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

// void print_node(t_env **node)
// {
//     t_env *current = *node;

//     while (current->next != NULL)
//     {
//         printf("%s\n", current->menvp);
//         // if (current->next != NULL)
//             current = current->next;
//         // else
//             // break;
//     }
//     printf("\n\n\n\n");
//     while (current->prev != NULL)
//     {
//         printf("%s\n", current->menvp);
//         // if (current->next != NULL)
//             current = current->prev;
//         // else
//             // break;
//     }
// }


// int main (int argc, char **argv, char **envp)
// {
//     t_env **word_list;
//     t_env *found_str;

//     word_list = (t_env **)malloc(sizeof(t_env));
//     word_list = ft_create_node(word_list, envp);

//     // print_node(word_list);
//     found_str = ft_find_env(word_list, argv[1]);
//     detach_node(found_str);
//     print_node(word_list);
// }