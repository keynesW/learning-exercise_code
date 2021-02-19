client:client.o list.o
	gcc client.o list.o -o client 

client.o:client.c
	gcc -c client.c -o client.o
list.o:list.c
	gcc -c list.c -o list.o

clean:
	rm *.o 
