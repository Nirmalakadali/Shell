#include "shell.h"
void print_file(char *word, char *string)
{
    struct dirent **namelist;
    struct dirent **list2;
    int m, isd;
    char dir[MAX];
    getcwd(dir, 1000);
    char copy[MAX], copy2[MAX], copy3[MAX];
    strcpy(copy2, word);
    int flag = 0;
    int j = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == '/')
            j++;
    }
    if (strcmp(word, dir) != 0 && j > 1)
    {
        char *ts2 = strdup(copy2);
        strcpy(copy3, "./");
        strcat(copy3, basename(ts2));
        strcpy(word, copy3);
    }
    if (strcmp(word, ".") == 0)
    {
        strcpy(word, dir);
    }
    // printf("%s\n", word);
    int n = scandir(word, &namelist, 0, alphasort);
    int p[4][4];
    // printf("first%s\n", namelist[0]->d_name);
    if (n < 0)
        perror("scandir");
    DIR *d = opendir(word);
    if ((d))

    {
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                struct stat st;
                int isDirectory = 0;
                stat(namelist[i]->d_name, &st);
                isDirectory = S_ISDIR(st.st_mode);
                if (!isDirectory)
                {
                    if (strcmp(namelist[i]->d_name, string) == 0)
                    {
                        flag = 1;
                    }
                    // if (strcmp(word, dir) != 0)
                    // {
                    //     printf("%s/%s\n", word, namelist[i]->d_name);
                    // }
                    // else
                    //     printf("./%s\n", namelist[i]->d_name);
                }
                // else if (isDirectory)
                // {

                //     printf("./%s\n", namelist[i]->d_name);
                //     m = scandir(namelist[i]->d_name, &list2, 0, alphasort);
                //     if (m < 0)
                //     {
                //         perror("scandir");
                //     }
                //     DIR *df = opendir(namelist[i]->d_name);
                //     if (df)
                //     {
                //         for (int j = 0; j < m; j++)
                //         {
                //             struct stat strat = {0};
                //             isd = 0;
                //             if (list2[j]->d_name[0] != '.')
                //             {
                //                 isd = 0;
                //                 stat(list2[j]->d_name, &strat);
                //                 permissions_check(list2[j]->d_name, p);
                //                 if (p[0][0] == 0)
                //                 {
                //                     isd = 1;
                //                 }
                //                 if (isd == 0)
                //                 {
                //                     if (strcmp(word, dir) == 0)
                //                     {
                //                         printf("./%s/", namelist[i]->d_name);
                //                     }
                //                     printf("%s\n", list2[j]->d_name);
                //                 }
                //             }
                //         }
                //     }
                //     reset();
                // }
            }
        }
        if (flag == 1)
        {
            printf("%s/%s", word, string);
        }
    }
    return;
}
void printing(char *word, int dflag, int fflag)
{
    char nm[MAX];
    strcat(nm, "/home/");
    strcat(nm, username);
    struct dirent **namelist;
    struct dirent **list2;
    int m, isd;
    char dir[MAX];

    getcwd(dir, 1000);
    char copy[MAX], copy2[MAX], copy3[MAX];
    strcpy(copy2, word);
    int j = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == '/')
            j++;
    }
    if (strcmp(word, dir) != 0 && j > 1 && strcmp(word, nm) != 0)
    {
        //pointer to the new string to duplicate the string
        char *ts2 = strdup(copy2);
        strcpy(copy3, "./");
        strcat(copy3, basename(ts2));
        strcpy(word, copy3);
    }
    if (strcmp(word, ".") == 0)
    {
        strcpy(word, dir);
    }
    // printf("%s\n", word);
    char cc[MAX];
    int n = scandir(word, &namelist, 0, alphasort);
    int p[4][4];
    // printf("first%s\n", namelist[0]->d_name);
    if (n < 0)
        perror("scandir");
    DIR *d = opendir(word);
    if ((d && fflag == 0 && dflag == 0) || (d && fflag == 1 && dflag == 1))
    {
        printf(".\n");
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                // m = 0;

                struct stat st;
                int isDirectory = 0;
                stat(namelist[i]->d_name, &st);
                isDirectory = S_ISDIR(st.st_mode);
                if (!isDirectory)
                {
                    if (strcmp(word, dir) != 0)
                    {
                        printf("%s/%s\n", word, namelist[i]->d_name);
                    }
                    else
                        printf("./%s\n", namelist[i]->d_name);
                }
                else if (isDirectory)
                {

                    printf("./%s\n", namelist[i]->d_name);
                    m = scandir(namelist[i]->d_name, &list2, 0, alphasort);
                    DIR *df = opendir(namelist[i]->d_name);
                    if (df)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            struct stat strat = {0};
                            if (list2[j]->d_name[0] != '.')
                            {
                                isd = 0;
                                memset(&cc[0], 0, sizeof(cc));
                                strcat(cc, "./");
                                strcat(cc, namelist[i]->d_name);
                                strcat(cc, "/");
                                strcat(cc, list2[j]->d_name);
                                stat(cc, &strat);
                                int x = strat.st_mode;
                                // printf("----%s-->\n", cc);
                                if (S_ISDIR(x))
                                {
                                    isd = 1;
                                }
                                if (isd == 0)
                                {
                                    if (strcmp(word, dir) == 0)
                                    {
                                        printf("./%s/", namelist[i]->d_name);
                                    }
                                    printf("%s\n", list2[j]->d_name);
                                }
                            }
                        }
                    }
                    reset();
                }
            }
        }
    }
    else if (d && fflag == 1 && dflag == 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                struct stat st;
                memset(&cc[0], 0, sizeof(cc));
                strcat(cc, word);
                strcat(cc, "/");
                strcat(cc, namelist[i]->d_name);
                int isDirectory = 0;
                stat(cc, &st);
                isDirectory = S_ISDIR(st.st_mode);
                // printf("-%s--\n", cc);
                if (!isDirectory)
                {
                    if (strcmp(word, dir) != 0)
                    {
                        printf("%s/%s\n", word, namelist[i]->d_name);
                    }
                    else
                        printf("./%s\n", namelist[i]->d_name);
                }
            }
        }
    }
    else if (d && dflag == 1 && fflag == 0)
    {
        printf(".\n");
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                // m = 0;

                struct stat st;
                int isDirectory = 0;
                stat(namelist[i]->d_name, &st);
                isDirectory = S_ISDIR(st.st_mode);
                if (isDirectory)
                {
                    printf("./%s\n", namelist[i]->d_name);
                    m = scandir(namelist[i]->d_name, &list2, 0, alphasort);
                    if (m < 0)
                    {
                        perror("scandir");
                    }
                    DIR *df = opendir(namelist[i]->d_name);
                    if (df)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            struct stat strat = {0};
                            isd = 0;
                            if (list2[j]->d_name[0] != '.')
                            {
                                isd = 0;
                                memset(&cc[0], 0, sizeof(cc));
                                strcat(cc, "./");
                                strcat(cc, namelist[i]->d_name);
                                strcat(cc, "/");
                                strcat(cc, list2[j]->d_name);
                                stat(cc, &strat);
                                int x = strat.st_mode;
                                // printf("----%s-->\n", cc);
                                if (!S_ISDIR(x))
                                {
                                    isd = 1;
                                }
                                if (isd == 0)
                                {
                                    // printf(" s -->%d\n", list2[j]->d_name, isd);
                                    if (strcmp(word, dir) == 0)
                                    {
                                        printf("./%s/", namelist[i]->d_name);
                                    }
                                    printf("%s\n", list2[j]->d_name);
                                }
                            }
                        }
                    }
                    reset();
                }
            }
        }
    }
    memset(&nm[0], 0, sizeof(nm));
}
void printable(char *root)
{
    char path[MAX];
    strcpy(path, root);
    char commands[MAX] = {0};
    char **string = (char **)malloc(10000 * sizeof(char *));
    char **string1 = (char **)malloc(10000 * sizeof(char *));
    int len = strlen(path);
    int dflag = 0, fflag = 0;
    for (int i = 0; i < len; i++)
    {
        strncat(commands, &path[i], 1);
        if (path[i] == '-' && path[i + 1] == 'f')
            fflag = 1;
        else if (path[i] == '-' && path[i + 1] == 'd')
            dflag = 1;
    }
    //printf("%d %d -->\n", fflag, dflag);
    char word[MAX], realpath[MAX];
    getcwd(word, 1000);
    int h = 0;
    string[h] = strtok(commands, " \t");
    string1[h] = string[h];
    while (string[h] != NULL)
    {
        h++;
        string[h] = strtok(NULL, " \t");
        string1[h] = string[h];
    }
    char ma[MAX];
    //strcpy(ma, string[h - 1]);
    // printf("%s\n",ma);
    int i = 0;
    int length = 0, flag = 0;
    while (string[i] != NULL)
        i++;
    length = i;
    int lj = 0;
    int lent = 0;
    while (string1[lj] != NULL)
        lj++;
    lent = lj;
    int j = 0;
    int increment = 0, x;

    char nm[MAX], gh[MAX];
    strcat(nm, "/home/");
    strcat(nm, username);

    // printf("->%s\n", gh);
    printf("==%c==\n",string[0][0]);

    for (i = 0; i < length; i++)
    {
        if ((string[i][0] != '-' || strlen(string[i]) == 1) && strcmp(string[i], "discover"))
        {
            
            if (strcmp(string[i], "~") == 0)
            {
                strcpy(realpath, ".");
                flag = 1;
            }
            else
            {
                strcpy(realpath, string[i]);
                flag = 1;
            }
            //struct stat is used to store information about files
            struct stat st = {0};
            x = stat(realpath, &st);
            increment++;
        }
    }
    if (flag == 1 && increment == 1)
    {
        if (x < 0)
        {
            printf("discover: cannot access '%s': No such file or directory\n", string[i]);
        }
        else
            printing(realpath, dflag, fflag);
    }
    else if (flag == 1 && increment > 1)
    {
        char mm[MAX + 1000], mm2[MAX], mm3[MAX];
        if (strcmp(string[i - 2], "~") == 0)
        {
            int f, j;
            int len = strlen(ma);
            for (f = 0; f < len; f++)
            {
                if (ma[f] == '"')
                {
                    for (j = f; j < len; j++)
                    {
                        ma[j] = ma[j + 1];
                    }
                    len--;
                    f--;
                }
            }
        }
        else
        {
            strcpy(mm3, string[i - 1]);
            int f, j;
            int len = strlen(mm3);
            for (f = 0; f < len; f++)
            {
                if (mm3[f] == '"')
                {
                    for (j = f; j < len; j++)
                    {
                        mm3[j] = mm3[j + 1];
                    }
                    len--;
                    f--;
                }
            }
        }

        // printf("%s\n", string[i - 2]);
        // printf("%s\n", gh);
        if (strcmp(string[i - 2], "~") == 0)
        {
            strcpy(mm, ".");
        }
        else if (strcmp(string[i - 2], ".") == 0)
        {
            strcat(mm, word);
        }
        else
            strcpy(mm, string[i - 2]);
        strcat(mm, "/");
        if (strcmp(string[i - 2], "~") == 0)
        {
            strcat(mm, ma);
        }
        else
            strcat(mm, mm3);
        FILE *file;
        //printf("%s\n",mm);
        if (file = fopen(mm, "r"))
        {
            char *ts2 = strdup(string[i - 2]);
            char *ts1 = strdup(word);
            // printf("%s\n", word);

            if (strcmp(string[i - 2], ".") == 0)
            {
                strcpy(mm2, "./");
                strcat(mm2, basename(ts1));
            }
            else if (strcmp(string[i - 2], "~") == 0)
            {
                strcpy(mm2, ".");
                //strcat(mm2, nm);
            }
            else
            {
                strcpy(mm2, "./");
                strcat(mm2, basename(ts2));
                // printf("%s\n",mm2);
            }

            strcat(mm2, "/");
            if (strcmp(string[i - 2], "~") == 0)
                strcat(mm2, ma);
            else
                strcat(mm2, mm3);
            // printf("%s\n",mm3);
            strcpy(word, mm2);
            fclose(file);
            printf("%s\n", word);
        }
        else
        {
            printf("Please check folder path or name and file name once\n");
        }
    }

    else if (flag == 0)
        printing(word, dflag, fflag);

    memset(&gh[0], 0, sizeof(gh));
    memset(&nm[0], 0, sizeof(nm));
    return;
    // printf("%s\n", word);
}