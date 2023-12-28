#include <iostream>

#include "ServerNode.hpp"
#include <sys/wait.h>
#include "SpringBootApplication.hpp"

void child(int sig) {
    pid_t pid;
    pid = wait(nullptr);
}

int main() {
    signal(SIGCHLD, child);
    SpringBootApplication app;
    app.run();
}
