#include "bg.h"
void bg(char *input)
{
    char *token = strtok(NULL, " \t");
    int pid;
    int job_number;
    int flag;
    if (token == NULL)
    {
        printf("YOu need to give few more arguments\n");
        return;
    }
    job_number = atoi(token);
    token = strtok(NULL, " \t");
    if (token != NULL)
    {
        printf("oh no please give less arguments\n");
        return;
    }
    
    if (job_number <= 0) 
    {
        printf("No job with  this job number\n");
        return;
    }
    if( job_number > job)
    {
        printf("BUllshit number\n");
        return;

    }
    pid = process_id(job_number);
    flag = kill(pid, SIGCONT);
    if (flag < 0)
    {
        perror("Kill Unsuccessful");
    }
    return;
}