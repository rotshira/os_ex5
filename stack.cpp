#pragma once
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std;
int f;  // the file to mymory
char show_Top[256];
//code for stack took from https://www.codewhoop.com/stack/stack-using-linked-list.html

//stack 
typedef struct stack
{
    int top;
    char data[1024];
}Stack, *p_stack;

struct flock lock1;

int Memory_file() // the open file to memory
{
    f = open("file.txt", O_WRONLY | O_CREAT); 
    if (f == -1) 
    {
        printf("Error % d\n", errno);
    }
    memset(&lock1, 0, sizeof(lock1)); 
    return f;
}
//Function to push  element in stack
void push (p_stack stack,char *value)
{
    printf("push:%s\n", value);
    for (int i = 0; i < strlen(value) ; i++)
    {
        stack->data[stack->top+1]=value[i];
        stack->top++;
    }
    stack->data[stack->top+1]='\0'; // add to end of word
    stack->top++;
}

//Function to delete an element from the stack
void pop (p_stack stack)
{
 if(strlen(stack->data)==1)
 {
        printf("Error-the stack is empty \n");
        return;
}
   else 
{
       stack->top-=1;
       while (stack->data[stack->top]!='\0')
       {
          stack->top--;
       }
}
//    printf("pop\n");
}

//Function to show the element at the top of the stack
char* showTop(p_stack stack)
{
        if(stack->top==1)
        {
        printf("the Stack is empty\n");
        return NULL;
        }
     else 
     {
        int index = stack->top-1;
        while (stack->data[index]!='\0')
        {
            index--;
        }     
        for (int j = 0; stack->data[index + 1] != '\0' ; j++){
            show_Top[j] = stack->data[index+1];
            index++;
        }
        printf("The top : %s\n", show_Top);
        return show_Top;
    }
}

 //Main function
char* mainfunc(p_stack s, char* str, char* input, char* output)
{
lock1.l_type = F_WRLCK;
fcntl(f, F_SETLKW, &lock1);
char* ans = NULL;
//  commend PUSH:
    if(strcmp(str, "PUSH") == 0) 
    {
        push(s,input);
    }

    // commend POP:
    else if(strcmp(str, "POP") == 0) {

        pop(s);
    }

    // commend TOP:
    else if(strcmp(str, "TOP") == 0) {

        ans =  showTop(s);
    }
    else 
    {
      printf("Error");
    }
    lock1.l_type = F_UNLCK;
    fcntl (f, F_SETLKW, &lock1);
    return ans;
}
