#include "status.h"

void bghandler(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    char *token = (char *)malloc(sizeof(char *) * 1000);
    struct node * head = root;
    if (pid > 0)
    {
        token = search_node(pid);
        if (!WIFEXITED(status))
        {
            printf("%s with pid %d exited abnormally\n", token, pid);
            // head->next->job--;
        }
        else
        {
            printf("%s with pid %d exited normally\n", token, pid);
            // head->next->job--;
        }
        dell(pid);
    }
    return;
}
