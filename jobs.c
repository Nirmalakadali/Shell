#include "jobs.h"

void jobs(char *input)
{
    int rflag = 0;
    int sflag = 0;
    char *token = strtok(NULL, " \t\n");
    while (token != NULL)
    {
        if (strcmp(token, "-r") == 0 || strcmp(token, "-s") == 0)
        {
            if (strcmp(token, "-r") == 0)
            {
                rflag++;
            }
            else
            {
                sflag++;
            }
        }
        else
        {
            printf("I thinkl it might be an flag error please check it :)%s\n", token);
            return;
        }

        token = strtok(NULL, " \t\n");
    }

    if (sflag == 0 && rflag != 0)
    {
        printlist(1);
    }
    else if (sflag != 0 && rflag == 0)
    {
        printlist(2);
    }
    else
    {
        printlist(0);
    }

    return;
}