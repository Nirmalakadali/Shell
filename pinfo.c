#include "shell.h"
void pinfo(char *input, char *root)
{
    int root_len, pfile_len;
    int count = 0,j=0;
    root_len = strlen(root);
    char original[10000];
    // thread group id
    char *thread_gid = (char *)malloc(100 * sizeof(char *));
    // parent process id
    char *parent_processid = (char *)malloc(100 * sizeof(char *));
    // path of executable
    char *path = (char *)malloc(1000 * sizeof(char));
    char *path2 = (char *)malloc(1000 * sizeof(char));
    char *copy = (char *)malloc(1000 * sizeof(char *));
    pid_t PID;
    char *token = strtok(NULL, " \t\n");
    char path_p[MAX];
    if (token == NULL)
    {
        PID = getpid();
        sprintf(path_p, "%d", PID);
    }
    while (token != NULL)
    {
        if (j > 1)
        {
            printf("Too many arguments for pinfo");
            exit(1);
        }
        j++;
        PID = atoi(token);
        strcpy(path_p, token);
        token = strtok(NULL, " \t\n");
        
    }
    strcpy(path, "/proc/");
    strcat(path, path_p);
    strcat(path, "/stat");
    strcpy(path2, "/proc/");
    strcat(path2, path_p);
    strcat(path2, "/exe");
    FILE *FID = fopen(path, "r");
    //printf("%s\n", path);
    if (FID == NULL)
    {
        red();
        printf("Error while open file\n");
        perror("");
        reset();
        return;
    }
    fgets(original, 10000, FID);
    //printf("%s\n", original);
    token = strtok(original, " \t\n");
    count++;
    while (token != NULL)
    {
        int ppid=7;
        int tgid=4;
        int mem=22;
        int status=2;
        // printf("%d-->%s\n", count, token);
        token = strtok(NULL, " \t\n");
        if (count == status)
        {
            printf("pid : %d\n", PID);
            printf("process status : {%s", token);
        }
        else if (count == tgid)
        {
            strcpy(thread_gid, token);
        }
        else if (count == ppid)
        {
            strcpy(parent_processid, token);
        }
        else if (count == mem)
        {
            if (strcmp(thread_gid, parent_processid) == 0)
                printf("+}\n");
            else
                printf("}\n");
            printf("memory : ");
            printf("%s ", token);
            printf("{Virtual Memory}");
            printf("\n");
        }
        count++;
    }
    strcpy(original, "");
    //printf("-->%s\n", path2);
    int retu = readlink(path2, original, 10000);
    if (retu == -1)
    {
        red();
        printf("Error while accessing /proc/%d/exe\n", PID);
        reset();
        return;
    }
    original[retu] = '\0';
    pfile_len = strlen(original);
    // printf("===%s\n",root);
    if (root_len > pfile_len)
        printf("Executable Path : %s\n", original);
    else
    {
        printf("executable Path : ");
        strncpy(copy, original, root_len);
        copy[root_len] = '\0';
        if (strcmp(copy, root) == 0 && original[root_len] == '/')
        {
            printf("~");
            int i=root_len;
            while(i<pfile_len)
            {
                printf("%c", original[i]);
                i++;
            }
        }
        else if (strcmp(copy, root) == 0 && root_len == pfile_len)
            printf("~");
        else
            printf("%s", original);
        printf("\n");
    }
    return;
}