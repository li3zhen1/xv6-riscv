#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: sleep milliseconds\n");
        exit(0);
    }

    int tm = atoi(argv[1]);
    sleep(tm);

    exit(0);
}
