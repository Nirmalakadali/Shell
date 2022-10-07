#ifndef _REDIRECTION_H_
#define _REDIRECTION_H_
#include "redirection.h"
#include "directories.h"
#include "shell.h"
int input_outputredirection(char **command, int pipes, int in, int op, int append, char *input_file, char *output_file);
#endif