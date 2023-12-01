TARGET = client server bit
normal: $(TARGET)

server : server.c
	gcc server.c -o server

client : client.c
	gcc client.c -o client

bit : bit.c
	gcc bit.c -o bit

clean : 
	$(RM) $(TARGET)
