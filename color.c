#include "shell.h"
void blue()
{
    printf("\033[1;34m");
    return;
}
void green()
{
    printf("\033[1;32m");
    return;
}
void reset()
{
    printf("\033[1;37m");
    return;
}
void red()
{
    printf("\033[1;31m");
    return;
}
void cyan()
{
    printf("\033[1;36m");
}
void ex()
{
    printf("\033[1;33m");
}
void another()
{
    printf("\33[1;35m");
}