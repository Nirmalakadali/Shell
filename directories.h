#ifndef _DIRECTORIES_H_
#define _DIRECTORIES_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <libgen.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <stddef.h>
#include <assert.h>
#include "cd.h"
#include "discover.h"
#include "echo.h"
#include "get_input.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "pwd.h"
#include "userprompt.h"
#include "signal_handling.h"
#include "color.h"
#include "redirection.h"
#include "shell.h"
#include "bg.h"
#include "fg.h"
#include "sig.h"
#include "jobs.h"
#include "status.h"
#include "system_commands.h"
struct node
{
    int pid;
    char *process;
    int job;
    struct node *next;
};
extern struct node *root;
extern int job;
int ret_pid;
struct node *initialize_node(int pid, char *name, int job_id);
char *search_node(int pid);
void push_p(int pid, char *name, int job_id);
void dell(int pid);
void printlist(int flag);
int process_id(int job_number);

#endif