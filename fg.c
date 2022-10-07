#include "fg.h"
void fg(char *input)
{
    char *token;
    int job_number;
    int status;
    int pid;
    token = strtok(NULL, " \t");
    if (token == NULL)
    {
        printf("very few arguments\n");
        return;
    }
    job_number = atoi(token);
    token = strtok(NULL, " \t");
    if (token != NULL)
    {
        printf("Please check arguments count\n");
        return;
    }
    if (job_number <= 0)
    {
        printf("Invalid Job Number\n");
        return;
    }
    if (job_number > job)
    {
        printf("bullshit number\n");
        return;
    }
    pid = process_id(job_number);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    int fd0=0;
    int fd1=1;
    tcsetpgrp(fd0, pid);
    tcsetpgrp(fd1, pid);
    int check;
    check = kill(pid, SIGCONT);
    if (check < 0)
    {
        printf("abnormal kill\n");
        return;
    }
    waitpid(pid, &status, WUNTRACED);
    if (WIFSTOPPED(status))
    {
        kill(pid, SIGSTOP);
    }
    tcsetpgrp(fd0, getpid());
    tcsetpgrp(fd1, getpid());
    if (!WIFSTOPPED(status))
    {
        dell(pid);
    }
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return;
}
