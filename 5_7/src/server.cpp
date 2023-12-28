#include <zmq.hpp>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "wait.h"
#include "SpringBootApplication.hpp"
#include "ServerNode.hpp"

void child(int sig) {
    pid_t pid;
    pid = wait(nullptr);
}

int main(int argc, char** argv) {
    signal(SIGCHLD, child);
    if (argc != 4) {
        return 0;
    }
        ServerNode serverNode(atoi(argv[0]), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        std::cout << "server created" << std::endl;
        serverNode.run();
        return 0;
}