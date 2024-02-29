#pragma once

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

enum {
    READ,
    WRITE,
};

void die();

pid_t create_child();

void create_pipe(int fd[2]);

void print_help();