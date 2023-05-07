#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int min = 2;

int main(int argc, char* argv[]) {
    int p[2][2];
    pipe(p[0]);

    int index = 0;
    int num;
    for (int i = min; i < 35; i++) {
        write(p[index][1], &i, 4);
    }
    close(p[0][1]);
    while (fork() == 0) {
        if (read(p[index][0], &min, 4) != 0) {
            printf("prime %d\n", min);
        } else {
            exit(0);
        }
        pipe(p[index ^ 1]);
        while (read(p[index][0], &num, 4) != 0) {
            if (num % min) {
                write(p[index ^ 1][1], &num, 4);
            }
        }
        close(p[index ^ 1][1]);
        index = index ^ 1;
    }
    close(p[index][0]);
    wait(0);
    exit(0);
}