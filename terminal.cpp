#include "terminal.h"
#include <unistd.h>
#include <iostream>
#include "utility.h"
#include <sys/types.h>
#include <sys/wait.h>

 // run_cmd:
 // Takes a vector of C-style strings (char*), representing the command and its arguments.
 // Forks a child process, redirects its standard output, and executes the command.
 // Captures the output using a custom pipe (mypipe) and prints it to the terminal.
 // Returns 0 on success, non-zero on failure.
int run_cmd(std::vector<char *> argv)
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        std::cout << "\n[child] PID = " << getpid();
        std::cout << " - execvp\n" << std::flush;
        execvp(argv[0], argv.data());
        perror("exec failed");
        exit(127);//“command not found” or “exec failed”
    }

    //pid != 0 not required child returns before this
    int status{0};
    // 0 is flag to wait
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return -1;
    }
    return status;
}

 // terminal_app:
 // Implements a simple interactive terminal loop.
 // Continuously prompts the user for input, parses it into command and arguments,
 // and executes the command using run_cmd().
 // Exits the loop when the user types "exit".
void terminal_app()
{
    std::string input;

    while(true) {
        std::cout << "input something: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
        if (input.empty()) {
            continue;
        }
        std::vector<std::string> vector = cmd2vec(input, ' ');

        if (vector.empty()) {
            continue;
        }
        std::vector<char*> argv = castArgs(vector);

        run_cmd(argv);
    }
}
