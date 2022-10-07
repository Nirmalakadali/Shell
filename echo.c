#include "shell.h"
void echo(char *input)
{
    char *delimiter,copy2[MAX];
    delimiter = " \t";
    char *token, *copy;
    int i = 0, j = 0;
    token = strtok(NULL, delimiter);
    // printf("%s in function",token);
    while (token != NULL)
    {
        copy = token;
        token = strtok(NULL, delimiter);
        j=0;
        while (j < strlen(copy))
        {
            if (copy[j] == '&')
            {
                copy[j] = ' ';
            }
            j++;
        }
        if (copy[i] == '$')
        {
            strcpy(copy2,"echo");
            strcat(copy2," ");
            strcat(copy2,copy);
            system(copy2);
        }
        else
            printf("%s ", copy);
    }
    printf("\n");
    return;
}
