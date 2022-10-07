#include "shell.h"
int get_input(char **string)
{
    rl_bind_key('\t', rl_complete);
    size_t length = 0;
    int c = getline(string, &length, stdin);
    if (strcmp(*string, "exit\n") == 0)
    {
        return 1;
    }
    if (c < 0)
    {
        red();
        printf("Error while reading string\n");
        reset();
        return 1;
    }
    else
    {
        (*string)[c - 1] = '\0';
    }
    return 0;
}