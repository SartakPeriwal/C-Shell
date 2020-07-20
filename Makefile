compile: shell.o sepcommand.o ls.o cd.o echo.o pwd.o executecommand.o pinfo.o history.o nightswatch.o 
	gcc shell.o sepcommand.o ls.o cd.o echo.o pwd.o executecommand.o  pinfo.o history.o nightswatch.o 
shell.o: shell.c
	gcc -c shell.c
sepcommand.o: sepcommand.c
	gcc -c sepcommand.c
nightswatch.o: nightswatch.c
	gcc -c nightswatch.c
ls.o: ls.c
	gcc -c ls.c
history.o: history.c
	gcc -c history.c
cd.o: cd.c
	gcc -c cd.c
echo.o: echo.c
	gcc -c echo.c
pwd.o: pwd.c
	gcc -c pwd.c
execute_command.o: executecommand.c
	gcc -c executecommand.c
pinfo.o: pinfo.c
	gcc -c pinfo.c
clean: shell.o sepcommand.o ls.o cd.o pwd.o echo.o executecommand.o pinfo.o history.o
	rm *.o
