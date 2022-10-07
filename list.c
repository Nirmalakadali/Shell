#include "directories.h"
struct node *root;
struct node *initialize_node(int pid, char *name, int job_id)
{
    struct node *lls = (struct node *)malloc(sizeof(struct node));
    lls->process = (char *)malloc(1000 * sizeof(char));
    lls->process[0] = '\0';
    lls->pid = pid;
    lls->job = job_id;
    lls->next = NULL;
    strcpy(lls->process, name);
    return lls;
}

void printlist(int flag)
{
    struct node *head;
    head = root;
    if (head == NULL)
    {
        return;
    }

    while (head->next != NULL)
    {

        char pinfopath[10] = "";
        sprintf(pinfopath, "%d", head->next->pid);
        char path[1000] = "";
        strcpy(path, "/proc/");
        strcat(path, pinfopath);
        // printf("%s\n", pinfopath);
        strcat(path, "/stat");
        int st_file = 0;
        FILE *FID;
        FID = fopen(path, "r");
        if (FID == NULL)
        {
            perror("There might be an error in file please check");
            return;
        }
        char file_info[10000] = " ";
        fgets(file_info, 10000, FID);
        char status[2] = "";
        char *token;
        token = strtok(file_info, " \t\n");
        st_file++;

        while (token != NULL)
        {
            token = strtok(NULL, " \t\n");
            if (st_file == 2)
            {
                strcpy(status, token);
            }
             st_file++;
        }
        if(strcmp(status,"\0")==0)
        {
            perror("Error in status of the file\n");
            return;
        }
        if (flag == 2)
        {
            if ((strcmp(status, "R") != 0 && (strcmp(status, "S") != 0) && (strcmp(status, "D") != 0)))
            {
                printf("[%d]  ", head->next->job);
                printf("Stopped  ");
                printf("%s ", head->next->process);
                printf("[%d]\n", head->next->pid);
            }
        }
        else if (flag == 1)
        {
            if ((strcmp(status, "R") == 0 || (strcmp(status, "S") == 0) || (strcmp(status, "D") == 0)))
            {
                printf("[%d] ", head->next->job);
                printf("Running ");
                printf("%s ", head->next->process);
                printf("[%d]\n", head->next->pid);
            }
        }
        else if (flag == 0)
        {
            // printf("---%s\n", status);
            printf("[%d] ", head->next->job);
            if ((strcmp(status, "R") != 0 && (strcmp(status, "S") != 0) && (strcmp(status, "D") != 0)))
            {
                printf("Stopped ");
            }
            else if (strcmp(status, "S") == 0 || (strcmp(status, "R") == 0) || (strcmp(status, "D") == 0))
            {
                printf("Running ");
            }
            
            printf("%s  ", head->next->process);
            printf("[%d]\n", head->next->pid);
        }

        head = head->next;
        if (head->next == NULL)
        {
            break;
        }
    }
    return;
}
void push_p(int pid, char *name, int job_id)
{
    struct node *lls;
    struct node *head;
    lls = initialize_node(pid, name, job_id);
    head = root;
    if (head == NULL)
    {
        return;
    }
    while (head->next != NULL && (strcmp(name, head->next->process) >= 0))
    {
        head = head->next;
        if (head->next == NULL)
        {
            break;
        }
        if (strcmp(name, head->next->process) >= 0)
        {
            break;
        }
    }
    lls->next = head->next;
    head->next = lls;
    return;
}
int process_id(int job)
{
    struct node *temp;
    temp = root;
    if (temp == NULL)
    {
        return 0;
    }
    while (temp != NULL)
    {
        if (temp->job == job)
        {
            return temp->pid;
        }
        temp = temp->next;
    }
    return 0;
}
char *search_node(int pid)
{
    struct node *temp;
    temp = root;
    if (temp == NULL)
    {
        return NULL;
    }
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            return temp->process;
        }
        temp = temp->next;
    }

    return NULL;
}

void dell(int pid)
{
    struct node *prev;
    struct node *del;
    prev = root;
    if (prev == NULL)
    {
        return;
    }
    del = prev->next;
    while (prev != NULL)
    {
        del = prev->next;
        if (prev->next != NULL)
        {
            if (prev->next->pid == pid)
            {
                prev->next = prev->next->next;
                free(del->process);
                free(del);
            }
            else
            {
            }
        }
        prev = prev->next;
    }
    return;
}
