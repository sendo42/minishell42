// #include "minishell.h"
#include <libc.h>
#include "minishell.h"
    /*
        親プロセスが子プロセスの終了状態を取得しなかった場合wait
        ()
        ゾンビプロセスが生じる

        ゾンビプロセスは下記のような特徴を持ちます。

        CPUリソースは使用しない
        メモリリソースはほぼ（プロセス関連の情報だけしか）消費しない
        PIDを消費する（PIDの数はOSで上限がある）
        killコマンドで消せない（親プロセスをkillする必要がある）
        従って、PIDを消費する以外では基本的に害はありません。

        プロセステーブルに名前が残り続けてしまう
        https://askubuntu.com/questions/537262/do-zombie-processes-cause-memory-shortage-do-they-get-killed-by-the-init-proces
        https://kakts.dev/entry/OS%E3%81%AE%E3%83%97%E3%83%AD%E3%82%BB%E3%82%B9%E3%80%81fork%E3%81%AA%E3%81%A9
        先に親が子より先に終了した場合、pid=1のinitプロセスが子の親になり終了してくれる

        ゾンビプロセスに限らずプロセスは終了時に下記の手順を取る。

        ① オープンしてたファイルをすべて閉じる

        ② プロセスが使用してたメモリ領域の解放

        ③ プロセス構造体を解放

        ④ プロセステーブルのエントリ解放

        ⑤ プロセスの終了

        実装を細かく追うならこの辺。
    */
    /*

        構造体でメモリのやり取りをする。
        
        いくつ単語のリストがあるのかを数える

        その数だけ毎回pipeをしてプロセスを生成する。

        パイプの入出力先を書き換える
            実行させる
        子プロセス　親プロセス
        echo "aaa" | cat | cat | cat > file
    */
// char **wordlist = {"ls","cat","echo"};
// char **pathlist = {"/bin/ls","/bin/cat","/bin/echo"};

/*
    必要な情報は
    
    forkは親だけで何度かする。
    その度にパイプを保持する。
    保持したものを次のやつに渡す。

*/

/*

単語リストをもらう。
パイプの数を知りたい
パイプでwhileの数だけforkで兄弟を作る
https://stackoverflow.com/questions/17630247/coding-multiple-pipe-in-c
pipe
fork

親
保持する
子
if 次
dup2(fd[1],1)
読む
fd１書く
else 次なし
読む
１書く

ほしい機能は、    
とりあえずこれをうまく分割して一つの意味を持たせること

もらう単語リストによって実装が少し変わるが、いい感じだと思う

引数をもらい、処理をして次のやつに渡す。
簡易的にやる


実際には、
開ける
作る
    保持する

複製する
処理する
次に渡す

開ける
作る
    保持する

複製する
処理する
次に渡す

開ける
作る
    保持する

複製する
処理する
次に渡す

fd


*/

// int p_pipe_next(int *tmp_fd,int *fd)
// {
//     *tmp_fd =fd[0];
//     // close(fd[0]);
//     close(fd[1]);
//     return *tmp_fd;
// }

// void c_pipe_exe(char *cmd,int *tmp_fd, int *fd,int last_flag)
// {
//     char buf[1024];

//     dup2(*tmp_fd,0);
//     close(*tmp_fd);
//     if(last_flag == 1)
//     {
//         dup2(fd[1],1);
//         close(fd[1]);
//     }
//     while(read(0,buf,1) > 0)
//         write(1,buf,1);
//     close(fd[1]);
//     close(0);
//     exit(0);
// }
/*
int create_pipe(char **cmd,int pipe_num)
{
    int i;
    int fd[2];
    int tmp_fd;
    pid_t pid;
    int status;

    i = 0;
    tmp_fd = 0;
    while(i < pipe_num)
    {
        pipe(fd);
        pid = fork();
        if(pid > 0)
            p_pipe_next(&tmp_fd,fd);
        else
            c_pipe_exe(*cmd,&tmp_fd, fd ,1);
        i++;
        cmd++;
    }
    waitpid(pid,&status,0);
    return 0;
}
このままではコマンドを認識できない。構造体で一連の塊として渡さないといけない。
*/

// char **cmd = {
//     "echo",
//     "-n",
//     "aaa",
//     "|",
//     "cd"
//     ".."
// };
/*
複数のコマンドをどうするか、
ビルトインとそうでないものとをどうするか
cmd[0]にechoを、まずはビルトインを探して次にパスを探す
cmd[1]に文字列を

*/

// int cmd_count(t_cmd *cmd)
// {
//     int i;

//     i = 0;
//     while(cmd != NULL)
//     {
//         i++;
//         cmd = cmd->next;
//     }
//     return i;
// }

// void pipe_execute(t_cmd *cmd, t_info *info,int i)
// {
//     char buf[1024];

//     if(i == 0)
//     {
//         char *send = "hello from first";
//         close(info->pipe_fd[0]);
//         dup2(info->pipe_fd[1],1);
//         close(info->pipe_fd[1]);
//         printf("%s\n",send);
//         // close(1);なぜかここを閉めると動かない
//         exit(0);
//     }
//     else
//     {
//         dup2(info->tmp_fd,0);
//         close(info->tmp_fd);
//         if(i != 2)
//             dup2(info->pipe_fd[1],1);
//         close(info->pipe_fd[1]);
//         while(read(0,buf,1) > 0)
//             write(1,buf,1);
//         close(info->pipe_fd[1]);
//         // printf("bbb\n");
//         close(0);
//         exit(0);
//     }

//     if(i != 0)
//         dup2(info->tmp_fd,0);
//     printf("fd :%d ",info->tmp_fd);
//     close(info->tmp_fd);
//     close(info->pipe_fd[0]);
//     printf("i:%d %s\n",i,cmd->arg_str[i]);
//     if(cmd->next != NULL)
//     {
//         dup2(info->pipe_fd[1],1);
//         close(info->pipe_fd[1]);
//     }
//     if(i == 0)
//     {}
//     else
//     {
//         while(read(0,buf,1)> 0)
//         write(1,buf,1);
//     }
//     // printf("%d aaa\n",i);
//     close(1);
//     exit(0);
// }

void pipe_execute(t_cmd *cmds, t_info *info)
{
    char buf[1024];

    dup2(info->tmp_fd,0);
    close(info->tmp_fd);
    if(cmds->next != NULL)
    {
        dup2(info->pipe_fd[1],1);
        close(info->pipe_fd[1]);
    }
    if(cmds->flag != 1)
    {
        while(read(0,buf,1)>0)
            write(1,buf,1);
    }
    printf("cmds: %s\n",cmds->cmd);
    close(0);
    exit(0);//ここで終わらせないとプロセスが2倍ずつ増え続ける
}


void pipe_create(t_cmd *cmd)
{
    t_info pipe_i;

    pipe_i.tmp_fd = 0;
    while(cmd != NULL)
    {
        pipe(pipe_i.pipe_fd);
        pipe_i.pid = fork();
        if(pipe_i.pid == 0)
            pipe_execute(cmd,&pipe_i);
        else
        {
            pipe_i.tmp_fd = pipe_i.pipe_fd[0];
            close(pipe_i.pipe_fd[1]);
        }
        cmd = cmd->next;
    }
        waitpid(pipe_i.pid,NULL,0);
}

void builtins_select(t_cmd *cmds)
{
    if(ft_strncmp(cmds->cmd,"echo",3))
    {
        ft_cd(cmds->arg_str[0]);
        system("pwd");
    }
    // else if(ft_strncmp(cmds->cmd,"cd",2))
    // else if(ft_strncmp(cmds->cmd,"pwd",3))
    // else if(ft_strncmp(cmds->cmd,"export",6))
    // else if(ft_strncmp(cmds->cmd,"unset",5))
    // else if(ft_strncmp(cmds->cmd,"env",3))
}

void is_multiple_pipe(t_cmd *cmd)
{
    if(cmd->next != NULL)
        pipe_create(cmd);
    else
        builtins_select(cmd);
}

int main() {
    t_cmd cmd1;
    t_cmd cmd2;
    t_cmd cmd3;

    // cmd1 の設定
    cmd1.cmd = "cd";
    cmd1.option = NULL;
    cmd1.arg_str = malloc(sizeof(char*));
    cmd1.arg_str[0] = NULL;
    cmd1.flag = 1;
    cmd1.next = NULL;

    // // cmd2 の設定
    // cmd2.cmd = "grep";
    // cmd2.option = malloc(sizeof(char*));
    // cmd2.option[0] = "-i";
    // cmd2.arg_str = malloc(sizeof(char*));
    // cmd2.arg_str[0] = "world";
    // cmd2.flag = 0;
    // cmd2.next = &cmd3;

    // // cmd3 の設定
    // cmd3.cmd = "wc";
    // cmd3.option = NULL;
    // cmd3.arg_str = malloc(sizeof(char*));
    // cmd3.arg_str[0] = NULL; // 適切な値を設定する必要があります
    // cmd3.flag = 0;
    // cmd3.next = NULL;

    // テスト用のデータを作成

    t_info info;
    info.pipe_fd[0] = -1;
    info.pipe_fd[1] = -1;
    info.tmp_fd = -1;
    info.pid = -1;

    // パイプの作成とテストの実行
    is_multiple_pipe(&cmd1);

    // メモリの解放
    free(cmd1.arg_str);
    free(cmd2.option);
    free(cmd2.arg_str);

    return 0;
}