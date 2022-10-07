#include "shell.h"

int input_outputredirection(char **command, int pipes, int in, int op, int append, char *input_file, char *output_file)
{
    int i = 0;
    int j = 0;
    int pipePresent = 0;
    char **string = (char **)malloc(100);
    int communication = 1;
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    int chanel = 2 * pipes;
    int pip[2 * pipes + 2];
    i = 0;
    while (i < 2 * pipes)
    {
        pipe(pip + i);
        i = i + 2;
    }
    i = 0;

    if (in == 0 || pipes > 0)
    {
        if (pipes > 0)
        {
            pipePresent = 1;
        }
        if (in == 0)
        {
            if (pipes > 0)
            {
                flag = 1;
            }
        }
    }
    while (command[i] != NULL)
    {
        if (in == 1)
        {
            int fd3;
            if ((strcmp(command[i], "|")) == 0)
            {
                pipes--;
                j = 0;
            }
            if ((strcmp(command[i], "<")) == 0)
            {
                flag = 1;
                int fd;
                fd = open(input_file, O_RDONLY);
                if (fd < 0)
                {
                    red();
                    printf("   '%s': No such file or directory\n", input_file);
                    reset();
                    return 0;
                }
                if (pipes >= 1)
                {
                    flag2 = 1;
                    if (fork() == 0)
                    {
                        int x;
                        int y;
                        string[j] = NULL;
                        x = dup2(fd, 0);
                        y = dup2(pip[communication], 1);
                        close(pip[communication - 1]);

                        execvp(string[0], string);
                        red();
                        printf("%s:Invalid command\n", string[0]);
                        reset();
                        return 0;
                    }
                    else
                    {
                        wait(NULL);
                        int t;
                        t = communication;
                        close(pip[t]);
                        t = 0;
                    }
                }
                else if (op == 1)
                {
                    if (fork() == 0)
                    {
                        int x;
                        x = dup2(fd, 0);
                        if (append == 0)
                        {
                            int fd2;
                            int y;
                            string[j] = NULL;
                            fd2 = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                            if (fd2 < 0)
                            {
                                red();
                                printf("   '%s': No such file or directory\n", output_file);
                                reset();
                                return 0;
                            }
                            y = dup2(fd2, 1);

                            execvp(string[0], string);
                            red();
                            printf("%s:Invalid command\n", string[0]);
                            reset();
                            return 0;
                        }
                        else
                        {
                            int fd2;
                            int y;
                            string[j] = NULL;
                            fd2 = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
                            y = dup2(fd2, 1);

                            execvp(string[0], string);
                            red();
                            printf("%s:Invalid command\n", string[0]);
                            reset();
                            return 0;
                        }
                    }
                    return 0;
                }
                else
                {
                    if (fork() == 0)
                    {
                        int x;
                        x = dup2(fd, 0);
                        string[j] = NULL;
                        // printf("going here");
                        execvp(string[0], string);
                        red();
                        printf("%s:Invalid command\n", string[0]);
                        reset();
                        return 0;
                    }
                    return 0;
                }
            }
        }
        if ((!strcmp(command[i], ">") || !strcmp(command[i], ">>")))
        {
            if (pipePresent == 1)
            {
                if (fork() == 0)
                {

                    int x;
                    x = dup2(pip[communication - 1], 0);
                    int fd;
                    close(pip[communication]);
                    if (append == 0)
                    {
                        fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                        if (fd < 0)
                        {
                            red();
                            printf(" '%s': No such file or directory\n", output_file);
                            reset();
                            return 0;
                        }
                    }
                    else
                    {
                        fd = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
                        if (fd < 0)
                        {
                            red();
                            printf("   '%s': No such file or directory\n", output_file);
                            reset();
                            return 0;
                        }
                    }
                    int y;
                    y = dup2(fd, 1);
                    string[j] = NULL;
                    execvp(string[0], string);
                    red();
                    printf("%s:Invalid command\n", string[0]);
                    reset();
                    return 0;
                }
                else
                {
                    wait(NULL);
                    int t;
                    t = communication - 1;
                    close(pip[t]);
                    t = 0;
                }
                return 0;
            }
        }
        if (!strcmp(command[i], "|"))
        {
            if (flag == 1)
            {
                pipes--;
                if (flag3 == 0 && flag2 == 1)
                {
                    flag3 = 1;
                }
                else if (flag2 == 1)
                {
                    communication =communication+ 2;
                    if (fork() == 0)
                    {
                        string[j] = NULL;
                        int x;
                        int y;
                        int t;
                        t=communication;
                        x = dup2(pip[t - 3], 0);
                        y = dup2(pip[t], 1);
                        close(pip[t - 1]);
                        close(pip[t - 2]);
                        t=0;
                        execvp(string[0], string);
                        red();
                        printf("%s:Invalid command\n", string[0]);
                        reset();
                        return 0;
                    }
                    else
                    {
                        wait(NULL);
                        int t;
                        t = communication;
                        close(pip[t]);
                        close(pip[t - 3]);
                        t = 0;
                    }
                }
                else
                {
                    flag2 = 1;
                    flag3 = 1;
                    if (fork() == 0)
                    {
                        string[j] = NULL;
                        int x;
                        x = dup2(pip[communication], 1);
                        close(pip[communication - 1]);
                        execvp(string[0], string);
                        red();
                        printf("%s:Invalid command\n", string[0]);
                        reset();
                        return 0;
                    }
                    else
                    {
                        wait(NULL);
                        int t;
                        t = communication;
                        close(pip[t]);
                        t = 0;
                    }
                }
                j = 0;
            }
        }
        if (in == 0)
        {
            if (pipePresent == 0)
            {
                if (!strcmp(command[i], ">"))
                {
                    int fd;
                    fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                    if (fd < 0)
                    {
                        red();
                        printf("   '%s': No such file or directory\n", output_file);
                        reset();
                        return 0;
                    }
                    if (fork() == 0)
                    {
                        int y;
                        y = dup2(fd, 1);
                        string[j] = NULL;
                        execvp(string[0], string);
                        red();
                        printf("%s:Invalid command\n", string[0]);
                        reset();
                        return 0;
                    }
                    return 0;
                }
                else if (!strcmp(command[i], ">>"))
                {
                    int fd;
                    fd = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
                    if (fd < 0)
                    {
                        red();
                        printf(" '%s': No such file or directory\n", output_file);
                        reset();
                        return 0;
                    }
                    if (fork() == 0)
                    {
                        int y;
                        y = dup2(fd, 1);
                        string[j] = NULL;
                        execvp(string[0], string);
                        red();
                        printf("%s:Invalid command\n", string[0]);
                        reset();
                        return 0;
                    }
                    return 0;
                }
            }
        }
        if (strcmp(command[i], "|"))
        {
            if (strcmp(command[i], "<"))
            {
                if (strcmp(command[i], ">"))
                {
                    if (strcmp(command[i], ">>"))
                    {
                        string[j] = command[i];
                        j++;
                    }
                }
            }
        }
        i++;
    }
    if (pipePresent == 1)
    {
        if (op == 0)
        {
            if (fork() == 0)
            {
                string[j] = NULL;
                int x;
                x = dup2(pip[communication - 1], 0);
                close(pip[communication]);
                execvp(string[0], string);
                red();
                printf("%s:Invalid command\n", string[0]);
                reset();
                return 0;
            }
            else
            {
                wait(NULL);
                int t;
                t = communication - 1;
                close(pip[t]);
                t = 0;
            }
        }
    }
    return 0;
}