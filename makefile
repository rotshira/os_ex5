LD = arm-none-eabi-g++
all: server client 

server: server.cpp
	g++ server.cpp -lpthread -o server

client: client.cpp
	g++ client.cpp -lpthread -o client

# malloc: malloc.cpp
# 	g++ malloc.cpp -o malloc

clean:
	rm -f *.o server client Thread

runs:
	./Thread

runc:
	./client