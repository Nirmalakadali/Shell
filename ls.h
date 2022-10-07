#ifndef _LS_H_
#define _LS_H_
#include "ls.h"
#include "directories.h"
#include "shell.h"
void permissions_check(char *copyname, int p[4][4]);
void print(char *word, int aflag, int lflag);
void ls(char *input33, char *root);
#endif