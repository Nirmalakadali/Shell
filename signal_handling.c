#include "signal_handling.h"
void CtrlZ(int A)
{
   // printf("\n");
    //used to clear the buffer and used to store the new string
    fflush(stdout);
    char direct[MAX];
    getcwd(direct,MAX);
    printf("\n");
    user_system(direct,0,0);
    return;
}

void CtrlC(int A)
{
    if (ret_pid != -1)
        kill(ret_pid, SIGINT);
    fflush(stdout);
    char direct[MAX];
    getcwd(direct,MAX);
    printf("\n");
    user_system(direct,0,0);
    return;
}
void Ctrld(int A)
{
    fflush(NULL);
    return;
}
