all:	
	@gcc client.c -o client
	@gcc server_mutlpro.c link_list.c -lpthread -o server


#client server:client.o server.o
#	cc -o client client.o  
#client.o:client.c  client.h 
#	cc -c client.c 

#server:server.o
#	cc -o server server.o
#server.o:server.c server.h
#	cc -c server.c
 
clean:
	rm -rf client.o sever.o client  server
