#include "utils.hpp"

void die() {
    write(STDERR_FILENO, "Fatal error occured\n", 20);
    exit(EXIT_FAILURE);
}

pid_t create_child() {
    pid_t pid = fork();
    if(pid == -1)
        die();
    return pid;  
}

void create_pipe(int fd[2]) {
    if(pipe(fd) == -1)
        die();
}


void print_help() {
    std::cout << "This is a game client [PID " << getpid() << "]\n";
    std::cout << "leaderboard - shows players stats\n";
    std::cout << "play - starts new game" << std::endl;
}
