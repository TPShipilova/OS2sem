#include "unistd.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/mman.h>
#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
const int SIZE_SH = 1024;
using namespace std;

int main(int argc, char* argv[]) {
    int fd = shm_open(argv[1], O_RDWR, 0666);

    char* str = (char*)mmap(NULL, SIZE_SH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Проверка строки на соответствие правилу
    if (str[strlen(str) - 1] == '.' || str[strlen(str) - 1] == ';') {
        cout << str << endl;
    }  else {
            FILE* file = fopen(argv[2], "w");
            fprintf(file, "%s", str);
            fclose(file);
        }

    munmap(str, SIZE_SH);

    return 0;
}
