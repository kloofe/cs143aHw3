CC = gcc
CFLAGS = -I.

all: my_shell

my_shell: my_shell.c
	$(CC) -o my_shell my_shell.c $(CFLAGS)

run: my_shell 
	./my_shell

clean:
	rm my_shell
