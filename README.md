This is my basic replica of bash written in c.
* To compile: make 
* To run: ./a.out 
* Clean: make clean 
Features implemented 
1) A shell prompt of the form: <username@system_namecurr_dir> with path relative to home 
2) Semi-colon (;) separated commands 
3) Some built in commands like cd ,echo ,ls , and pwd re-implemented 
4) Type exit to exit the shell 
5) & to run a process in background 
7) Process id printed when background process terminates 
8) Type pinfo in the prompt to print: pid, process, status, memory and executable path  
 **Some bash commands are implemented and the rest are invoked using execvp**

 Bonus:
 1)history command to print history .
 
 2)nightswatch command.

Files in Directory:-

1) shell.c :- contains the main ,prompt ,printprompt function .

2) ls.c  :- contains ls ,lsl ,get permissions function. It handles ls command .

3) echo.c :- contains echo function .

4) cd.c :- It handles cd command.

5) global.h :- contains all the definitions of functions and the definitions of the constants to be used.

6) pinfo.c :- It prints the process related info of our shell program.

7) pwd.c   :- It handles pwd command.

8) sepcommand.c  :-It splits the commands entered so that they can be executed.

9)executecommand.c :- contains launchfunc ,child process ,executefunc function.

10)nightswatch.c :- imitates watch command with dirty and interrupt flag.

11)history.c-:keeps history of the running session.

