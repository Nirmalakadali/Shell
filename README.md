# Implementation of shell in c
## K.Lakshmi Nirmala (2021101126)


[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

---
# Requirements
- Bash Terminal
- Linux OS (Preferably ubuntu)
---

# Important Note

*  The following commands are with respect to the write in vscode and execute it in vscode and i run it on ubuntu

---

## Commands to execute file
Open the file ../2021101126_Assignment-3 directory and then execute these commands
```
$ make
$ ./terminal
```
---
## Commands implemented in this shell

- ECHO : echo prints what we are given in the command line after echo command and this command written in  [ echo.c ] 
- CD: cd changes directory according to our input, prints sleep time if there is any sleep command given by us and implemented in [cd.c]
- PINFO:prints out process info according to the given pid and implemented in [pinfo.c]
- DISCOVER : Behaves like find command,supports -f -d flags and implemented in [discover.c]
- LS : prints list of files and folders, supports -l -a -al or -la flags and implemented in [ls.c]
- HISTORY : prints last 10 commands executed by terminal and also prints commands according to our given count ,saves in [history.txt] implemented in [history.c]
- JOBS: prints all the running and stopped process, supports -r -s flags and implemented in [jobs.c]
- SIG : sig command takes the signal number and job numbers and does operation on the job according to the signal number and implemented in [sig.c]
- FG : It takes background process to the foreground according to the given job number and implemented in [fg.c]
- BG : It resumes stopped process to running in the background according to the job number and implemented in [bg.c]
- EXIT : This shell exits on exit command or ctrl+d click 
---
# Additional Featues
- This shell supports Autocompletion on tab press
- Supports system commands which were not implemented by me
- Supports input output redirection and piping
- Handles ctrl+c , ctrl+d and ctrl+z signals
- Handles multiple commands
- prints message after exiting background process
- prints special outputs in colored
- --
# Example commads 
- ls:
```
$ls
$ls -a
$ls -al
$ls -l
$ls -la
```
- echo:
 ```
 $ echo hello world
 # for inputoutputredirection
 $ echo hello > out.txt
 $ echo hello >> out.txt
 ```
 - cd:
 ```
 $ cd ..
 $ cd folderpath/foldername
 $ cd filepath/filename
 $ cd -
 ```
 - pwd
 ```
 $ pwd
 ```
 - pinfo
 ```
 $ pinfo
 $ pinfo pid
 ```
 - jobs
 ```
 $ jobs
 $ jobs -s
 $ jobs -r
 ```
 - fg
 ```
 $ fg jobnumber
 ```
 - bg
 ```
 $ bg jobnumber
 ```
 - sig
```
$ sig jobnumber signalnumber
```
- discover
```
$ discover -d
$ discover -f
$ discover foldername/folderpath filename/filepath
```
- input-outputredirection and piping
```
$ echo hello > out.txt
$ cat sample2.txt | head -7 | tail -5
$ cat < out.txt
```
---
# List of files
- [shell.c]
- [status.c]
- [system_commands.c]
- [get_input.c]
- [user_prompt.c]
- [cd.c]
- [ls.c]
- [echo.c]
- [pwd.c]
- [discover.c]
- [fg.c]
- [bg.c]
- [sig.c]
- [jobs.c]
- [pinfo.c]
- [color.c]
- [history.c]
- [signal_handling.c]
- [redirection.c] 
- [list.c] contains pid and helps in jobs,fg,bg,sig
---
Thankyou...

---

  [shell.c]: shell.c
  [status.c]: status.c 
  [system_commands.c]: system_commands.c 
 [get_input.c]: get_input.c 
 [user_prompt.c]: user_prompt.c 
 [cd.c]: cd.c 
 [ls.c]: ls.c 
 [echo.c]: echo.c 
 [pwd.c]: pwd.c 
 [discover.c]: discover.c 
 [fg.c]: fg.c 
 [bg.c]: bg.c 
 [sig.c]: sig.c 
 [jobs.c]: jobs.c 
 [list.c]: list.c 
 [pinfo.c]: pinfo.c
 [color.c]: color.c 
 [history.c]: history.c 
 [signal_handling.c]: signal_handling.c 
  [redirection.c]: redirection.c 
  
