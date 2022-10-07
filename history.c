#include "shell.h"
int count = 0;
int len = 1000;
int limit = 20;
void history(char *input, char *path)
{
    char **string = (char **)malloc(1000 * sizeof(char *));
    char **token = (char **)malloc(45 * sizeof(char *));
    char *original_Array = (char *)(calloc(1000, 1));
    int fd = open(path, O_RDWR | O_CREAT, 0677);
    read(fd, original_Array, len);
    token[0] = strtok(original_Array, "\n");
    count = 0;
    int i = 0;
    if (token[0] != NULL)
    {
        string[count] = token[0];
        count++;
    }
    while (token[i] != NULL)
    {
        ++i;
        token[i] = strtok(NULL, "\n");
        if (token[i] != NULL)
        {
            string[count] = token[i];
            count++;
        }
    }
    --i;
    if (token[0] == NULL)
    {
        string[count] = input;
        count++;
    }
    else
    {
        if (strcmp(token[i], input) != 0)
        {
            string[count] = input;
            count++;
        }
    }
    close(fd);
    fd = open(path, O_WRONLY | O_TRUNC, 0677);
    writing(count, string, fd);
    close(fd);
}
void showhistory(char *path)
{
    count = 0;

    char **string = (char **)malloc(1000 * sizeof(char **));
    char *original_Array = (char *)malloc(1000 * sizeof(char *));

    int fd = open(path, O_RDWR);
    read(fd, original_Array, len);
    char *token2, *token3, copy[MAX];
    token2 = "\0";
    token3 = "\0";
    char *token = strtok(original_Array, "\n");
    int print_count = 10;
    if (token)
    {
        string[count++] = token;
        while ((token = strtok(NULL, "\n")))
        {
            string[count++] = token;
        }
    }
    strcpy(copy, string[count - 1]);
    token2 = strtok(copy, " \t\n");
    if (strcmp(token2, "history") == 0 && strlen(string[count - 1]) > 8)
    {

        token3 = strtok(NULL, " \t");
        if (strcmp(token3, "&") == 0)
        {
            strcpy(token3, "10");
        }
        // if(strcmp(token3,"-c")==0)
        // {
        //     char **key={'\0'};
        //     writing(10,key,fd);
        // }
        if (atoi(token3) > 10 )
        {
            red();
            printf("Invalid count: count must be less than 10\n");
            reset();
            return;
        }
    }
    int p = 0;
    if (count > print_count)
    {
        if (strlen(token3) == 1)
        {
            p = count - atoi(token3);
        }
        else
            p = count - print_count;
    }
    close(fd);
    memset(&copy[0], 0, sizeof(copy));
    print_history(string, count, p);
}
void print_history(char **string, int count, int p)
{

    int i;
    i = p;
    while (i < count)
    {
        printf("%s\n", string[i]);
        i++;
    }
}
void writing(int count, char **string, int fd)
{
    int p = 0;
    if (count - limit > 0)
    {
        p = count - limit;
    }
    int i = p;
    while (i < count)
    {
        write(fd, string[i], strlen(string[i]));
        if (i < count - 1)
        {
            write(fd, "\n", 1);
        }
        i++;
    }
}
