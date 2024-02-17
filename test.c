// #include "minishell.h"
#include <libc.h>
#include "libft/inc/libft.h"
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
int p_pipe_next(int *tmp_fd,int *fd)
{
    *tmp_fd =fd[0];
    // close(fd[0]);
    close(fd[1]);
    return *tmp_fd;
}

void c_pipe_exe(char *cmd,int *tmp_fd, int *fd,int last_flag)
{
    char buf[1024];

    dup2(*tmp_fd,0);
    close(*tmp_fd);
    if(last_flag == 1)
    {
        dup2(fd[1],1);
        close(fd[1]);
    }
    while(read(0,buf,1) > 0)
        write(1,buf,1);
    close(fd[1]);
    close(0);
    exit(0);
}
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

// typedef struct s_cmd {
//     char *cmd;      //echo
//     char **option;   //-n
//     char **arg_str;  //aaa
//     struct s_cmd *next;     
// }   t_cmd;こんな感じで欲しい




int count_pipe(char **argv,int argc)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while(j < argc)
    {
        if(argv[j][0] == '|')
            i++;
        j++;
    }
    return i; 
}

int main(int argc, char **argv)
{
    int i;

    i = count_pipe(argv,argc);
    create_pipe(argv,i);
    printf("%d\n",i);

}