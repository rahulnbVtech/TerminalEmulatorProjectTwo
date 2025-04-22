#include "mypipe.h"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>


mypipe::mypipe()
{
    auto status{pipe(fd.data())};
    if(status < 0){
        exit(1);
    }
}

mypipe::~mypipe()
{
    close(fd[0]);
    close(fd[1]);
}

void mypipe::redirect()
{
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

std::string mypipe::read()
{
    std::array<char, 256> buf = {};
    std::size_t bytes;
    bytes = ::read(fd[0], buf.data(), buf.size());
    if(bytes > 0)
        return std::string(buf.data(), bytes);
    else
        return std::string();
}
