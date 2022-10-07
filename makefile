

default: main

main:shell.c get_input.c user_prompt.c cd.c ls.c echo.c pwd.c discover.c fg.c bg.c sig.c jobs.c list.c pinfo.c color.c history.c system_commands.c signal_handling.c redirection.c  status.c shell.h get_input.h userprompt.h cd.h ls.h echo.h pwd.h discover.h pinfo.h color.h history.h fg.h bg.h sig.h jobs.h signal_handling.h redirection.h system_commands.h status.h directories.h   
	gcc -g -o terminal shell.c status.c system_commands.c get_input.c user_prompt.c cd.c ls.c echo.c pwd.c discover.c fg.c bg.c sig.c jobs.c list.c pinfo.c color.c history.c signal_handling.c redirection.c  -lreadline


