#pragma once
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#include <stdbool.h>
#include "stack.cpp"
#include <sys/mman.h>
#include <fcntl.h>

// malloc.cpp from - https://stackoverflow.com/questions/8475609/implementing-your-own-malloc-free-with-mmap-and-munmap
void * _malloc ( size_t size )
{
    int *plen;
    int len = size + sizeof( size ); // Add sizeof( size ) for holding length.
    plen = (int*)mmap( NULL, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, f, 0 );
    *plen = len;                     // First 4 bytes contain length
    return (void*)(&plen[1]);        // Memory that is after length variable.
}

void _free ( void * ptr )
{
    int *plen = (int*)ptr;
    int len;

    plen--;                          
    len = *plen;                    
    munmap( (void*)plen, len );
}