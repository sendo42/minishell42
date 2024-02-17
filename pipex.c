// #include "minishell.h"
#include <libc.h>
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

int main(void){
    int fd[2];
    int tmp_fd;
    int pid;
    char buf[1024];

    pipe(fd);
    pid = fork();
    if(pid > 0)
    {
        tmp_fd =fd[0];
        close(fd[1]);
        // close(fd[0]);ここ閉めるとやばい
    }
    else if(pid == 0)
    {
        printf("C, pid: %d\n",pid);
        char *send = "hello from first";
        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);
        printf("%s\n",send);
        close(1);
        exit(0);
    }
    printf("fd : %d\n",tmp_fd);
    pipe(fd);
    pid = fork();
    if(pid > 0)
    {
        tmp_fd =fd[0];
        // close(fd[0]);
        close(fd[1]);
    }
    else if(pid == 0)
    {
        dup2(tmp_fd,0);
        close(tmp_fd);
        dup2(fd[1],1);
        close(fd[1]);
        while(read(0,buf,1) > 0)
            write(1,buf,1);
        close(fd[1]);
        // printf("bbb\n");
        close(0);
        exit(0);
    }
    printf("fd : %d\n",tmp_fd);
    pipe(fd);
    pid = fork();
    if(pid > 0)
    {
        tmp_fd =fd[0];
        // close(fd[0]);
        close(fd[1]);
    }
    else if(pid == 0)
    {
        dup2(tmp_fd,0);
        close(tmp_fd);
        // dup2(fd[1],1);
        // close(fd[1]);
        while(read(0,buf,1) > 0)
            write(1,buf,1);
        close(fd[1]);
        // printf("bbb\n");
        close(0);
        exit(0);
    }

    int status;
    waitpid(pid,&status,0);
}
    // pipe(fd);
    // pid = fork();
    // if(pid > 0)
    // {
    //     tmp_fd =fd[0];
    //     close(fd[0]);
    //     close(fd[1]);
    // }
    // else if(pid == 0)
    // {
    //     close(fd[1]);
    //     while(read(fd[0],buf,1) > 0)
    //         write(1,buf,1);
    // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// void execute_command(char **cmd, int *fd) {
//     int pid;
//     int pipefd[2];

//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     if ((pid = fork()) == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         close(pipefd[0]);
//         if (*fd != -1) {
//             dup2(*fd, STDIN_FILENO);
//             close(*fd);
//         }
//         if (cmd[1] != NULL) {
//             dup2(pipefd[1], STDOUT_FILENO);
//         }
//         close(pipefd[1]);
//         execvp(cmd[0], cmd);
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     } else {
//         close(pipefd[1]);
//         if (*fd != -1) {
//             close(*fd);
//         }
//         *fd = pipefd[0];
//     }
// }

// void loop_pipe(char ***cmd) {
//     int fd = -1;

//     execute_command(cmd[0], &fd);
//     execute_command(cmd[1], &fd);
//     execute_command(cmd[2], &fd);

//     // 結果の利用例
//     char buffer[1024];
//     ssize_t n;
//     while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
//         write(STDOUT_FILENO, buffer, n);
//     }

//     close(fd);
// }

// int main() {
//     char *cmd1[] = {"ls", NULL};
//     char *cmd2[] = {"ls", NULL};
//     char *cmd3[] = {"cat", NULL};
//     char **cmd[] = {cmd1, cmd2, cmd3};

//     loop_pipe(cmd);

//     return 0;
// }
