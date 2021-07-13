## Files info
- shell.c - The place where process starts executing.
- prompt.c - Display the prompt.
- parse.c - Parse the commands having ; and space.
- in.c - Input is taken. 
- check.c - Checks for whether the command is inbuilt and execute accordingly. Also it has fg, bg, overkill, kjob, jobs command implemented.
- pinfo.c - Displays process information.
- ls.c - Checks the flags for ls commands.
- ls_p.c - ls is implemented according to the flags.
- pipe.c - Command involving pipes are implemented.
- redirect.c - Command involving only redirection are implemented.
- epc.c - Commands echo, pwd, cd, setenv, unsetenv, ctrl-C and ctrl-Z handler are implemented.


## Usage
1. make
2. ./a.out
To delete all .o files, run ```make clean```.