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

int main() {
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    
    if(ftruncate(fd, SIZE_SH) == -1) {
        cout << "truncate throwed\n";
        exit(1);
    }

    char* str = (char*)mmap(NULL, SIZE_SH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(str == MAP_FAILED) {
        cout << "mmap failed\n";
        exit(1);
    }

    string input;
    getline(cin, input);

    strncpy(str, input.c_str(), SIZE_SH);

    // Создание дочернего процесса
    pid_t pid = fork();
    if (pid < 0){
        perror("can't create fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Дочерний процесс

        execl("child", "child", "/myshm", "output.txt", nullptr);

        /*char* str = (char*)mmap(NULL, SIZE_SH, PROT_READ, MAP_SHARED, fd, 0);

        // Проверка строки на соответствие правилу
        if (str[strlen(str) - 1] == '.') {
            cout << str << endl;
        } else {
            FILE* file = fopen("output.txt", "w");
            fprintf(file, "%s", str);
            fclose(file);
        }*/

        munmap(str, SIZE_SH);
        cout << "EXECL ERROR" << endl;
        return 1;
    } else {
        // Родительский процесс

        wait(NULL);
        

        munmap(str, SIZE_SH);

        close(fd);
        shm_unlink("/myshm");
    }

    return 0;
}
