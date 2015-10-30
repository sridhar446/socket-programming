main:server.o client.o
	gcc -o server server.o client.o

server.o:server.c
	gcc -c server.c -o server.o

client.o:client.c
	gcc -c client.c -o client.o

clean:
	rm -rf server client *.o