#include "shell.h"
void permissions_check(char *copyname, int p[4][4])
{
  struct stat st;
  stat(copyname, &st);
  int x = st.st_mode;

  if (S_ISDIR(x))
  {
    p[0][0] = 0;
  }
  else
  {
    p[0][0] = 1;
  }
  if (x & S_IRUSR)
  {
    p[1][0] = 1;
  }
  else
  {
    p[1][0] = 0;
  }
  if (x & S_IWUSR)
  {
    p[1][1] = 1;
  }
  else
  {
    p[1][1] = 0;
  }
  if (x & S_IXUSR)
  {
    p[1][2] = 1;
  }
  else
  {
    p[1][2] = 0;
  }
  if (x & S_IRGRP)
  {
    p[2][0] = 1;
  }
  else
  {
    p[2][0] = 0;
  }
  if (x & S_IWGRP)
  {
    p[2][1] = 1;
  }
  else
  {
    p[2][1] = 0;
  }
  if (x & S_IXGRP)
  {
    p[2][2] = 1;
  }
  else
  {
    p[2][2] = 0;
  }
  if (x & S_IROTH)
  {
    p[3][0] = 1;
  }
  else
  {
    p[3][0] = 0;
  }
  if (x & S_IWOTH)
  {
    p[3][1] = 1;
  }
  else
  {
    p[3][1] = 0;
  }
  if (x & S_IXOTH)
  {
    p[3][2] = 1;
  }
  else
  {
    p[3][2] = 0;
  }
}

void print(char *word, int aflag, int lflag)
{

  struct stat st;
  DIR *d;
  struct dirent **namelist;
  struct dirent *dir;
  char newname[MAX];
  if (word == NULL)
  {
    word = ".";
  }
  int isDirectory = 0;
  stat(word, &st);
  isDirectory = S_ISDIR(st.st_mode);
  char copyname[PATH_MAX];
  int len = strlen(word);
  strcpy(newname, word);
  newname[len] = '/';
  newname[len + 1] = '\0';
  int perm[4][4];
  int total = 0;
  char time[50];
  if (!isDirectory)
  {
    if (lflag == 0)
    {
      printf("%s\n", word);
    }
    else
    {
      struct stat str;
      struct passwd *ps;
      struct group *gp;
      lstat(word, &str);
      permissions_check(word, perm);
      ps = getpwuid(str.st_uid);
      gp = getgrgid(str.st_gid);
      if (perm[0][0] == 0)
        cyan();
      else if (perm[0][0] != 0 && perm[1][2] == 1 && perm[2][2] == 1 && perm[3][2] == 1)
        ex();

      strftime(time, sizeof(time), "%b %d %H:%M", localtime(&str.st_mtime));
      // printf("%ld",str.st_blocks);
      printf("%c%c%c%c%c%c%c%c%c%c %3lu %12s %12s %10ld %s %s\n",
             ((perm[0][0] == 0) ? 'd' : '-'),
             (perm[1][0] == 0) ? '-' : 'r', (perm[1][1] == 0) ? '-' : 'w', (perm[1][2] == 0) ? '-' : 'x', (perm[2][0] == 0) ? '-' : 'r', (perm[2][1] == 0) ? '-' : 'w', (perm[2][2] == 0) ? '-' : 'x', (perm[3][0] == 0) ? '-' : 'r', (perm[3][1] == 0) ? '-' : 'w', (perm[3][2] == 0) ? '-' : 'x', str.st_nlink, ps->pw_name, gp->gr_name, str.st_size, time, word);
      reset();
    }
  }
  else if (isDirectory)
  {
    int c;
    int n = scandir(word, &namelist, 0, alphasort);
    if (n < 0)
      perror("scandir");
    word = newname;
    strcpy(copyname, word);
    d = opendir(word);
    if (d && lflag == 1)
    {
      struct stat str;
      struct passwd *ps;
      struct group *gp;
      for (int i = 0; i < n; i++)
      {
        c = 0;
        if ((namelist[i]->d_name[0] == '.' && aflag) || (namelist[i]->d_name[0] != '.'))
        {
          strcat(copyname, namelist[i]->d_name);
          struct stat k;
          total += k.st_blocks;
          lstat(copyname, &str);
          c = str.st_blocks;
          total += c / 2;
          strcpy(copyname, word);
        }
      }
      printf("Total:%d\n", total);
      for (int i = 0; i < n; i++)
      {
        if ((namelist[i]->d_name[0] == '.' && aflag) || (namelist[i]->d_name[0] != '.'))
        {
          strcat(copyname, namelist[i]->d_name);
          struct stat k;
          lstat(copyname, &str);
          permissions_check(copyname, perm);
          ps = getpwuid(str.st_uid);
          gp = getgrgid(str.st_gid);
          strftime(time, sizeof(time), "%b %d %H:%M", localtime(&str.st_mtime));
          if (perm[0][0] == 0)
            cyan();
          else if (perm[0][0] != 0 && perm[1][2] == 1 && perm[2][2] == 1 && perm[3][2] == 1)
            ex();

          printf("%c%c%c%c%c%c%c%c%c%c %3lu %12s %12s %10ld %s %s\n",
                 ((perm[0][0] == 0) ? 'd' : '-'),
                 (perm[1][0] == 0) ? '-' : 'r', (perm[1][1] == 0) ? '-' : 'w', (perm[1][2] == 0) ? '-' : 'x', (perm[2][0] == 0) ? '-' : 'r', (perm[2][1] == 0) ? '-' : 'w', (perm[2][2] == 0) ? '-' : 'x', (perm[3][0] == 0) ? '-' : 'r', (perm[3][1] == 0) ? '-' : 'w', (perm[3][2] == 0) ? '-' : 'x', str.st_nlink, ps->pw_name, gp->gr_name, str.st_size, time, namelist[i]->d_name);
          reset();
          strcpy(copyname, word);
        }
      }
    }
    else if (d && lflag == 0)
    {
      int print = 0;
      int p[4][4];
      for (int i = 0; i < n; i++)
      {

        if ((namelist[i]->d_name[0] == '.' && aflag == 1) || (namelist[i]->d_name[0] != '.'))
        {
          strcat(copyname, namelist[i]->d_name);
          struct stat k;
          lstat(copyname, &k);
          permissions_check(copyname, p);
          if (p[0][0] == 0)
            cyan();
          else if (p[0][0] != 0 && p[1][2] == 1 && p[2][2] == 1 && p[3][2] == 1)
            ex();
          printf("%s\n", namelist[i]->d_name);
          reset();
          strcpy(copyname, word);
        }
      }
      closedir(d);
    }
  }
  // printf("%d",total);
}
void ls(char *input33, char *root)
{
  // printf("%ld", strlen(path));
  //  printf("%s",path[0]);
 // printf("%s", input33);
  // strcpy(commands, path);ls --block-size=512 -s sparse-file
  char *path = strtok(NULL, ";\n");
  // printf("%s\n",path);
  if (path == NULL)
  {
    path="ls";
    char present[MAX], realpath[MAX];
    getcwd(present, 260);
    char **string = (char **)malloc(10000 * sizeof(char *));
    char commands[MAX] = {0};
    int flag = 0, aflag = 0, lflag = 0;
    int ls_a = 0;
    int c;
    int len = strlen(path);
    //printf("-->%s", path);
    for (int i = 0; i < len; i++)
    {

      strncat(commands, &path[i], 1);
      // printf("%c\n", path[i]);
      if ((path[i] == '-' && path[i + 1] == 'l' && path[i + 2] == 'a') || path[i] == '-' && path[i + 1] == 'a' && path[i + 2] == 'l')
      {
        lflag = 1;
        aflag = 1;
      }
      else if (path[i] == '-' && path[i + 1] == 'l')
      {
        lflag = 1;
        // commands[i]=path[i];
      }
      else if (path[i] == '-' && path[i + 1] == 'a')
      {
        aflag = 1;
        // commands[i]=path[i];
      }
    }
    int h = 0;
    string[h] = strtok(commands, " \t");
    while (string[h] != NULL)
    {
      h++;
      // printf("str:%s\n",string[h]);
      string[h] = strtok(NULL, " \t");
      // printf("%d--> %d",h,string[h][0]);
    }
    int i = 0;
    char mm[MAX];
    strcat(mm, "/home/");
    strcat(mm, username);
    int length = 0;
    while (string[i] != NULL)
      i++;
    length = i;

    for (i = 0; i < length; i++)
    {
      if (string[i][0] == ';')
        break;
      if ((string[i][0] != '-' || strlen(string[i]) == 1) && strcmp(string[i], "ls") && string[i][0] != ';')
      {
        if (strcmp(string[i], "~") == 0)
        {
          strcpy(string[i], ".");
        }
        strcpy(realpath, string[i]);
        flag = 1;
        struct stat st = {0};
        // printf("%s",realpath);
        int x = stat(realpath, &st);
        if (x < 0)
          printf("ls: cannot access '%s': No such file or directory\n", string[i]);
        else
        {

          print(realpath, aflag, lflag);
        }
      }
    }
    // free(mm);
    memset(&mm[0], 0, sizeof(mm));
    if (flag == 0)
      print(NULL, aflag, lflag);
     //printf("\n");
  }
  else
  {
    //printf("%s\n",path);
    if (path != NULL)
    {
      char present[MAX], realpath[MAX];
      getcwd(present, 260);
      char **string = (char **)malloc(10000 * sizeof(char *));
      char commands[MAX] = {0};
      int flag = 0, aflag = 0, lflag = 0;
      int ls_a = 0;
      int c;
      int len = strlen(path);
      //printf("-->%s", path);
      for (int i = 0; i < len; i++)
      {

        strncat(commands, &path[i], 1);
        // printf("%c\n", path[i]);
        if ((path[i] == '-' && path[i + 1] == 'l' && path[i + 2] == 'a') || path[i] == '-' && path[i + 1] == 'a' && path[i + 2] == 'l')
        {
          lflag = 1;
          aflag = 1;
        }
        else if (path[i] == '-' && path[i + 1] == 'l')
        {
          lflag = 1;
          // commands[i]=path[i];
        }
        else if (path[i] == '-' && path[i + 1] == 'a')
        {
          aflag = 1;
          // commands[i]=path[i];
        }
      }

      // printf("%s\n",commands);
      //  if (strcmp(path, "ls "))
      //    printf("yes\n");
      //  printf("lflag->%d aflag%d\n",lflag,aflag);
      int h = 0;
      string[h] = strtok(commands, " \t");
      while (string[h] != NULL)
      {
        h++;
        // printf("str:%s\n",string[h]);
        string[h] = strtok(NULL, " \t");
        // printf("%d--> %d",h,string[h][0]);
      }
      int i = 0;
      char mm[MAX];
      strcat(mm, "/home/");
      strcat(mm, username);
      int length = 0;
      while (string[i] != NULL)
        i++;
      length = i;

      for (i = 0; i < length; i++)
      {
        if (string[i][0] == ';')
          break;
        if ((string[i][0] != '-' || strlen(string[i]) == 1) && strcmp(string[i], "ls") && string[i][0] != ';')
        {
          if (strcmp(string[i], "~") == 0)
          {
            strcpy(string[i], ".");
          }
          strcpy(realpath, string[i]);
          flag = 1;
          struct stat st = {0};
          int x = stat(realpath, &st);
          if (x < 0)
            printf("ls: cannot access '%s': No such file or directory\n", string[i]);
          else
          {

            print(realpath, aflag, lflag);
          }
        }
      }
      memset(&mm[0], 0, sizeof(mm));
      if (flag == 0)
        print(NULL, aflag, lflag);
     // printf("\n");
    }
  }
  return;
}
