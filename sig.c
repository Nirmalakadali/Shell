#include "sig.h"
void sig(char *input)
{
    char *token = strtok(NULL, " \t");
    int signal_number;
    int flag;
    int pid;
    int job_number;
    if (token == NULL)
    {
        red();
        printf("You need to give some more arguments\n");
        reset();
        return;
    }

     job_number = atoi(token);

    if (job_number <= 0)
    {
        red();
        printf("Bull shit job number\n");
        reset();
        return;
    }
    if (job_number > job)
    {
        red();
        printf("Forgotten job number\n");
        reset();
        return;
    }

    token = strtok(NULL, " \t");

    if (token == NULL)
    {
        red();
        printf("You need to give little more arguments\n");
        reset();
        return;
    }

    pid = process_id(job_number);
    signal_number = atoi(token);
    flag = kill(pid, signal_number);
    if (flag < 0)
    {
        red();
        printf("Kill is not successful\n");
        reset();
        return;
    }
    return;
}
