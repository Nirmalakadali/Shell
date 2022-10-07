#include "shell.h"
int job;
int main()
{
    int flag = 0, k = 0, g = 0, command = 0, dir_count = 0, count, status_of_pid;
    char *input, *limiting, *token2, *token3, *tokenizer, cc[1024], cc2[1024];
    char present_directory[MAX], copy[MAX], ls_copy1[MAX], copy2[MAX], previous_directory[MAX];
    getcwd(present_directory, 10000);
    char **string = (char **)malloc(10000 * sizeof(char *));
    char **comman = (char **)malloc(10000 * sizeof(char *));
    char string2[50][MAX] = {'\0'};
    // char string[15][MAX] = {'\0'};
    strcpy(previous_directory, present_directory);
    // flag = user_system(present_directory);
    char *path = (char *)malloc(10000 * sizeof(char *));
    char new_input[MAX];
    strcpy(path, present_directory);
    strcat(path, "/");
    strcat(path, "history.txt");
    tokenizer = " ;\t";
    int cou = 1;
    job = 0;
    int c = 0;
    int append = 0;
    char *command_Seperator;

    signal(SIGTSTP, CtrlZ);
    signal(SIGINT, CtrlC);
    root = initialize_node(-100000, "empty", 0);
    ret_pid = -1;
    rl_bind_key('\t', rl_complete);
    while (1)
    {
        // printf("going here\n");
        char separated_input[15][MAX] = {'\0'};
        char *input_file = NULL, *outputfile = NULL;
        int in = 0, op = 0, pips = 0;
        int background = 0;
        c = 0;
        if (flag == 1)
        {
            return 0;
        }
        memset(&copy[0], 0, sizeof(copy));
        memset(&new_input[0], 0, sizeof(new_input));
        // input = "\0";
        int pid, pid_status;
        // to know if the ctrlc is clicked or not
        //signal(SIGINT, CtrlC);
        input = readline(user_system(present_directory, 0, 0));
        // printf("--%s--",input);
        signal(SIGKILL, Ctrld);
        if (!input)
        {
            printf("\n");
            break;
        }
        if (input[0] == '\0')
        {
            printf("\n");
        }
        else if (input == "\0")
        {
            printf("\n");
            return 0;
        }
        history(input, path);
        // history adding
        int and_c = 0;
        int lenn = strlen(input);
        while (and_c < strlen(input))
        {
            if (input[and_c] == '&')
            {
                c++;
                background = 1;
            }
            and_c++;
        }
        // copying input int o new_input
        strcpy(new_input, input);
        // while loop to know the process  flag = get_input(&input);
        // history adding
        strcpy(copy,input);
        history(input, path);
        // copying input into cc
        strcpy(cc, input);
        // copying input int o new_input
        strcpy(new_input, input);
        int i = 0, length = 0;
        command_Seperator = ";";
        limiting = strtok(new_input, command_Seperator);
        // printf("%s", limiting);

        while (limiting != NULL)
        {
            strcpy(string2[i], limiting);
            string[i] = limiting;
            // printf("goinf");
            i++;
            limiting = strtok(NULL, command_Seperator);
        }
        limiting = NULL;
        int it = 0;
        length = i;

        for (it = 0; it < length; it++)
        {
            strcpy(cc, string2[it]);

            limiting = strtok(cc, " \t");
            int j = 0;
            while (limiting != NULL)
            {
                comman[j] = limiting;
                limiting = strtok(NULL, " \t");
                j++;
            }
            comman[j] = NULL;
            j = 0;
            if (comman[0] == NULL)
            {
                continue;
            }

            i = 0;
            while (comman[i] != NULL)
            {
                if (strcmp(comman[i], "<") == 0)
                {
                    in = 1;
                    if (comman[i + 1] == NULL)
                    {
                        perror("Please enter valid input\n");
                        return 0;
                    }
                    pips = 0;
                    input_file = comman[i + 1];
                }
                if (strcmp(comman[i], "|") == 0)
                {
                    pips++;
                    if (comman[i + 1] == NULL)
                    {
                        perror("Please give valid input\n");
                        return 0;
                    }
                }

                if (strcmp(comman[i], ">") == 0 || strcmp(comman[i], ">>") == 0)
                {
                    if (strcmp(comman[i], ">>") == 0)
                    {
                        append = 1;
                    }

                    if (comman[i + 1] == NULL)
                    {
                        perror("please enter valid command\n");
                        return 0;
                    }
                    op = 1;
                    outputfile = comman[i + 1];
                    break;
                }
                i++;
            }

            if (pips != 0 || in != 0 || op != 0)
            {
                flag = input_outputredirection(comman, pips, in, op, append, input_file, outputfile);
            }
            else if (pips == 0 && in == 0 && op == 0)
            {

                // printf("---%s\n",string[it]);
                token2 = strtok(string[it], tokenizer);
                // printf("--->%s\n",string[it]);
                count = 0;
                while (token2 != NULL)
                {
                    if (count == 0)
                    {

                        if (pips == 0 && in == 0 && op == 0)
                        {
                            if (strcmp(token2, "echo") == 0)
                            {
                                echo(string[it]);
                            }
                            else if (strcmp(token2, "pwd") == 0)
                            {
                                get_pwd();
                            }
                            else if (strcmp(token2, "cd") == 0)
                            {
                                cd(previous_directory, present_directory);
                            }
                            else if (strcmp(token2, "ls") == 0)
                            {
                                ls(string[it], present_directory);
                            }
                            else if (strcmp(token2, "exit") == 0)
                            {
                                return 0;
                            }
                            else if (strcmp(token2, "history") == 0)
                            {
                                showhistory(path);
                            }
                            else if (strcmp(token2, "discover") == 0)
                            {
                                printable(copy);

                            }
                            else if (strcmp(token2, "jobs") == 0)
                            {
                                jobs(token2);
                            }
                            else if (strcmp(token2, "fg") == 0)
                            {
                                fg(token2);
                            }
                            else if (strcmp(token2, "bg") == 0)
                            {
                                bg(token2);
                            }
                            else if (strcmp(token2, "sig") == 0)
                            {
                                sig(token2);
                            }
                            else if (strcmp(token2, "pinfo") == 0)
                            {
                                pinfo(string[it], present_directory);
                            }
                            else
                            {
                                system_commands(token2, 0, present_directory);
                                break;
                            }
                            if (c && (strcmp(token2, "ls") == 0 || strcmp(token2, "echo") == 0 || strcmp(token2, "pinfo") == 0 || strcmp(token2, "discover") == 0 || strcmp(token2, "history") == 0 || strcmp(token2, "cd") == 0))
                            {
                                system_commands(token2, 0, present_directory);
                                break;
                            }
                            c = 0;
                        }
                        if (flag == 1)
                        {
                            return 0;
                        }
                        token2 = strtok(NULL, tokenizer);
                    }
                    count++;
                }
            }

            i++;
            if (flag == 1)
                break;
        }
        if (pips == 0 && in == 0 && op == 0)
        {
            signal(SIGCHLD, bghandler);
        }
        if (flag == 1)
        {
            break;
        }
        free(input);
    }
    return 0;
}
