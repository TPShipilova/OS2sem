#include "isPipeEmpty.h"
#include <iostream> 

bool isPipeEmpty(int fd) {
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    return (select(fd + 1, &rfds, NULL, NULL, &tv) == 0);
}