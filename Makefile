main:
	gcc -c check.c in.c ls.c ls_p.c parse.c pinfo.c prompt.c epc.c pipe.c redirect.c
	gcc shell.c check.c in.c ls.c ls_p.c parse.c pinfo.c prompt.c epc.c pipe.c redirect.c

clean:
	rm -f check.o in.o ls.o ls_p.o parse.o pinfo.o prompt.o epc.o shell.o pipe.o redirect.o
