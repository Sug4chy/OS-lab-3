#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int min = 1;
int max = 100;

void childProcFunc(int loto_array[]) {
    srand(time(0) + getpid());
    int rand_i = rand() % N;
    sleep((rand() % 14) + 2);
    printf("%d\n", loto_array[rand_i]);
}

void waitChild(pid_t child_pid) {
    int wstatus;
    pid_t pid = wait(&wstatus);
    if (WIFEXITED(wstatus)) return;
    if (WIFSIGNALED(wstatus)) return;
}

int main() {
    printf("---Loto---\n");
    srand(time(0));
    int loto_array[N];
    pid_t pid_array[N];
    for (int i = 0; i < N; i++) {
        loto_array[i] = (rand() % (max - min + 1)) + min;
    }

    for (int i = 0; i < N; i++) {
        pid_array[i] = fork();
        switch (pid_array[i]) {
            case -1:
                exit(EXIT_FAILURE);
            case 0:
                childProcFunc(loto_array);
                return 0;
            default:
                continue;
        }
    }

    for (int i = 0; i < N; i++) {
        waitChild(pid_array[i]);
    }

    printf("---End---\n");
    return 0;
}
