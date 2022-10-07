#include "shell.h"
int get_pwd()
{
    char directory[MAX];
    if (getcwd(directory, 10000) == NULL)
    {
        red();
        perror("error while Getting the current directory name");
        reset();
        return -1;
    }
    else
    {
        printf("%s\n", directory);
    }
    return 0;
}
