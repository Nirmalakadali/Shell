
#include "shell.h"
const char *user_system(char *dir_name, int flag, int sleep)
{
    // intialising all required strings
    char path[MAX], concat[MAX], paths_during[MAX], hostname[HOST_NAME_MAX + 1];
    // getting username
    getlogin_r(username, 1000);
    // getting hostname
    gethostname(hostname, HOST_NAME_MAX + 1);
    green();
    // prompt printing
    printf("<%s@%s:~", username, hostname);
    reset();
    getcwd(path, 10000);
    // printf("[%s]\n",path);
    // printf("\n{%s}\n",dir_name);
    // strcat(concat, getenv("USERNAME"));
    // strcat(concat, "@");
    // strcat(concat, hostname);
    // printf("%s", concat);
    // getcwd(path, 10000);
    int Directory_length = strlen(dir_name);
    int PATH_LENGTH = strlen(path);
    // blue();
    // if it is different directory
    if (Directory_length > PATH_LENGTH)
    {
        reset();
        if (flag == 1)
        {
            another();
            printf("took %d seconds~$>\n", sleep);
            reset();
        }
        else if (flag == 0)
            printf("%s$>", path);
    }
    else
    {
        strncpy(paths_during, path, Directory_length);
        paths_during[Directory_length] = '\0';
        // if it is like before without chnaging directory
        if (strcmp(paths_during, dir_name) == 0 && Directory_length == PATH_LENGTH)
        {
            if (flag == 1)
            {
                another();
                printf("took %d seconds~$>\n", sleep);
                reset();
            }
            else if (flag == 0)
                printf("$>");
        }
        // if we give any cd command
        else if (strcmp(paths_during, dir_name) == 0 && path[Directory_length] == '/')
        {
            blue();
            // printf("~");
            int i = Directory_length;
            while (i < PATH_LENGTH)
            {
                printf("%c", path[i]);
                i++;
            }
            reset();

            if (flag == 1)
            {
                another();
                printf("took %d seconds~$>\n", sleep);
                reset();
            }

            else if (flag == 0)
                printf("$>");
        }
        // to print and go to the previous directory cd -
        else
        {
            if (flag == 1)
            {
                another();
                printf("took %d seconds~$>\n", sleep);
                reset();
            }
            else if (flag == 0)
                printf("%s$>", path);
        }
        reset();
    }
    return NULL;
}