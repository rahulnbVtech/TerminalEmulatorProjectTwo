#include "utility.h"

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char *> castArgs(const std::vector<std::string> &cmd)
{
    std::vector<char*> argv;
    for (const auto& arg : cmd) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // null-terminate
    return argv;
}

// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string &command, char delimiter)
{
    std::string word;
    std::vector<std::string> wordVector;
    std::istringstream stringStream(command);

    while (std::getline(stringStream, word, delimiter)) {
        if (word.empty() == false) {
            wordVector.push_back(word);
        }
    }

    return wordVector;
}
