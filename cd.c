#include "shell.h"
int cd(char *Prev_dir, char *root)
{
    int k = 0, check = 0, flag = 0;
    char direc[MAX];
    getcwd(direc, 10000);
    char *path, *path2, *tokenizer, copy[MAX], *token;
    tokenizer = " \t";
    token = strtok(NULL, tokenizer);
    // printf("%s",token);
    path = token;
    if (token == NULL)
    {
        strcpy(copy, root);
        k = 1;
    }
    else
    {
        // if nothing is given after cd
        if (token == NULL)
        {
            path = root;
        }
        // if  ~ is given after cd
        else if (strcmp(path, "~") == 0)
        {
            path = root;
        }
        // prints the previously used directory and changes to it.
        else if (strcmp(path, "-") == 0)
        {
            flag = 1;
        }
        // if ~/ is given after cd then stores the previous directory and returns to the home
        else
        {
            if (path[0] == '~')
            {
                if (path[1] == '/')
                {

                    strcpy(copy, root);
                    strcat(copy, &path[1]);
                    // printf("%s", copy);
                    k = 1;
                }
            }
        }
        // To find the remaining tokens of the string subsequent call is required
        token = strtok(NULL, tokenizer);
    }
    // if token is null means everything is read perfectly from the user
    if (token == NULL)
    {
        if (k == 0)
        {
            path2 = path;
        }
        else
        {
            path2 = copy;
        }
    }
    // else something is left to read it means user error
    else
    {
        // prints the error
        red();
        printf("Excessive arguments for cd command\n");
        reset();
        return 0;
    }
    // if flag=1 means token after the cd need printing
    if (flag == 1)
    {
        // prints the directory
        printf("%s\n", Prev_dir);
        check = chdir(Prev_dir);
    }
    else
    {
        check = chdir(path2);
    }
    // if directory is correct then checks if it is past directory or updated once
    // if it is updated once then present directory becomes previous directory
    if (check == 0)
    {
        if (strcmp(path2, direc) != 0)
        {
            strcpy(Prev_dir, direc);
        }
    }
    // if given folder or directory not found then prints error message
    else
    {
        red();
        char str[100] = "Please check directory once\n";
        printf("%s", str);
        perror("");
        reset();
    }
    return 0;
}