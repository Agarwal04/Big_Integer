#ifndef BigInteger_h
#define BigInteger_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node 
{
    int data;
    struct node *next;
};

typedef struct BigInteger 
{
    int length;
    struct node *L;
} SBI;

struct node *createNode(int);
void insertAtEnd(struct node**,int);
SBI initialize(char*);
SBI reverseLinkedList(SBI);
int compare(SBI,SBI);
SBI add(SBI,SBI);
SBI sub(SBI,SBI);
SBI mul(SBI,SBI);
SBI div1(SBI,SBI);
void display(SBI);

#endif