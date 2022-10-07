#include "system_commands.h"
void system_commands(char *input, int number, char *present_directory)
{
    // to store tokinized string
    char **string = (char **)malloc(10000 * sizeof(char *));
    // to store the command to save for later use
    char *string2 = (char *)malloc(10000 * (sizeof(char)));
    // token
    char *token = (char *)malloc(10000 * (sizeof(char)));
    char *limiting = (char *)malloc(10000 * (sizeof(char)));
    int j = 0;
    int x;
    string[j] = input;
    j++;
    // tokenizing input
    while (string[j-1] != NULL)
    {
        string[j] = strtok(NULL, " \t");
        //printf("%s",string[j]);
        j++;
    }
    // creating process
    ret_pid = fork();
    if (ret_pid == 0)
    {
        
        if (strcmp(string[j - 2], "&") == 0)
        {
            string[j - 2] = NULL;
        }
        setpgid(0, 0);
        x = execvp(string[0], string);
        if (x == -1)
        {
            red();
            printf("Invalid command\n");
            reset();
        }
        return;
    }
    else
    {
        strcpy(string2, "");
        int i = 0;
        while (i < j - 2)
        {
            strcat(string2, string[i]);
            if (i != j - 2)
            {
                strcat(string2, " ");
            }
            i++;
        }
        //printf("%s",string[j-2]);
        if (strcmp(string[j - 2], "&") == 0)
        {
            job++;
            char Process_Name[1000] = {0};
            i = 0;
            while (i < j - 2)
            {
                strcat(Process_Name, string[i]);
                strcat(Process_Name, " ");
                i++;
            }
            push_p(ret_pid, Process_Name, job);
            if (number == 0)
            {

                printf("[%d]\n", ret_pid);
            }
        }
        else
        {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            int fd0 = 0;
            tcsetpgrp(fd0, ret_pid);
            int status;
            waitpid(ret_pid, &status, WUNTRACED);
            if (strcmp(string[0], "sleep") == 0)
            {
                if(atoi(string[1])==1)
                {
                    printf("sleep for %d second\n",atoi(string[1]));
                }
                else
                {
                    printf("sleep for %d seconds\n",atoi(string[1]));
                }
                //user_system(present_directory, 1, atoi(string[1]));
            }
            char *token2 = (char *)malloc(10000 * (sizeof(char)));
            int tok = 0;
            if (WIFSTOPPED(status))
            {
                job++;
                tok++;
                push_p(ret_pid, string2, job);
                kill(ret_pid, SIGSTOP);
            }
            ret_pid = -1;
            tcsetpgrp(fd0, getpid());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }
    free(string);
    free(string2);
    return;
}