#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BigInteger.h"

// Function to create a new node
struct node *createNode(int data) 
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of a linked list
void insertAtEnd(struct node **head, int data) 
{
    struct node *newNode = createNode(data);
    if (*head == NULL) 
    {
        *head = newNode;
    } else 
    {
        struct node *current = *head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

SBI initialize(char* str) 
{
    SBI temp;
    temp.L=NULL;
    int l;
    int i;
    int num;
    l = strlen(str);
    for (i = 0; i<l; i++) 
    {
        if (str[i] >= '0' && str[i] <= '9' || str[i]=='-' || str[i]=='+')
        {
            int digit=str[i]-'0';
            insertAtEnd(&temp.L,digit);
        }

    }
    temp.length=0;
    struct node* current=temp.L;
    while(current!=NULL)
    {
        temp.length++;
        current=current->next;
    }
    return temp;
}

SBI reverseLinkedList(SBI num) 
{
    SBI prev;
    SBI current = num;
    SBI next;
    prev.L=NULL;
    next.L=NULL;
    while (current.L != NULL) 
    {
        next.L = current.L->next;
        current.L->next = prev.L;
        prev.L = current.L;
        current.L= next.L;
    }
    return prev;
}

int compare(SBI num1,SBI num2)
{
    if(num1.length<num2.length)
    return -1;
    if(num1.length>num2.length)
    return 1;
    struct node *p1=num1.L;
    struct node *p2=num2.L;
    while(p1!=NULL && p2!=NULL)
    {
        if(p1->data<p2->data)
        return -1;
        if(p1->data>p2->data)
        return 1;
        p1=p1->next;
        p2=p2->next;
    }
    return 0;
}

// Function to add two big integers represented as linked lists
SBI add(SBI num1, SBI num2) 
{
    struct node *result = NULL;
    int carry = 0;
    SBI temp1=reverseLinkedList(num1);
    SBI temp2=reverseLinkedList(num2);
    struct node *ptr1 = temp1.L;
    struct node *ptr2 = temp2.L;    
    while (ptr1 != NULL || ptr2 != NULL) 
    {
        int val1 = (ptr1 != NULL) ? ptr1->data : 0;
        int val2 = (ptr2 != NULL) ? ptr2->data : 0;
        int sum = val1 + val2 + carry;
        carry = sum / 10;
        insertAtEnd(&result, sum % 10);
        if (ptr1 != NULL) 
        {
            ptr1 = ptr1->next;
        }
        if (ptr2 != NULL) 
        {
            ptr2 = ptr2->next;
        }
    }
    if (carry > 0) 
    {
        insertAtEnd(&result, carry);
    }
    SBI resultSBI;
    resultSBI.length = num1.length + num2.length; // Updated length
    resultSBI.L = result;
    return reverseLinkedList(resultSBI);
}

SBI sub(SBI num1,SBI num2)
{
    SBI result;
    result.L = NULL;
    result.length = 0;
    SBI temp1=reverseLinkedList(num1);
    SBI temp2=reverseLinkedList(num2);
    struct node* ptr1 = temp1.L;
    struct node* ptr2 = temp2.L;
    int borrow = 0;
    while (ptr1 != NULL || ptr2 != NULL) 
    {
        int val1 = (ptr1 != NULL) ? ptr1->data : 0;
        int val2 = (ptr2 != NULL) ? ptr2->data : 0;
        int diff = val1 - val2 - borrow;
        if (diff < 0) 
        {
            diff += 10;
            borrow = 1;
        } else 
        {
            borrow = 0;
        }
        struct node* newNode = createNode(diff);
        if (result.L == NULL) 
        {
            result.L = newNode;
        } 
        else 
        {
            struct node* current = result.L;
            while (current->next != NULL) 
            {
                current = current->next;
            }
            current->next = newNode;
        }
        if (ptr1 != NULL) 
        {
            ptr1 = ptr1->next;
        }
        if (ptr2 != NULL) 
        {
            ptr2 = ptr2->next;
        }
    }
    // Remove leading zeros
    struct node* current = result.L;
    while (current != NULL && current->data == 0) 
    {
        struct node* temp = current;
        current = current->next;
        free(temp);
    }
    result.L = current;
    // Recalculate the length
    result.length = 0;
    current = result.L;
    while (current != NULL) 
    {
        result.length++;
        current = current->next;
    }
    return reverseLinkedList(result);
}

SBI mul(SBI num1,SBI num2)
{
    SBI result;
    result.L = createNode(0);  // Initialize with a single node containing 0
    result.length = 1;
    SBI temp1=reverseLinkedList(num1);
    SBI temp2=reverseLinkedList(num2);
    struct node* ptr2 = temp2.L;
    while (ptr2 != NULL) 
    {
        int val2 = ptr2->data;
        SBI tempResult;
        tempResult.L = NULL;
        tempResult.length = 0;
        struct node* current = temp1.L;
        int carry = 0;
        // Multiply num1 with a single digit of num2
        while (current != NULL || carry != 0) 
        {
            int val1 = (current != NULL) ? current->data : 0;
            int product = val1 * val2 + carry;
            carry = product / 10;
            int digit = product % 10;
            struct node* newNode = createNode(digit);
            if (tempResult.L == NULL) 
            {
                tempResult.L = newNode;
            } 
            else 
            {
                struct node* tempCurrent = tempResult.L;
                while (tempCurrent->next != NULL) 
                {
                    tempCurrent = tempCurrent->next;
                }
                tempCurrent->next = newNode;
            }
            if (current != NULL) 
            {
               current = current->next;
            }
        }
        // Add the temporary result to the final result with appropriate shifts
        for (int i = 0; i < result.length - 1; i++) 
        {
            struct node* newNode = createNode(0);
            struct node* tempCurrent = tempResult.L;
            while (tempCurrent->next != NULL) 
            {
                tempCurrent = tempCurrent->next;
            }
            tempCurrent->next = newNode;
            tempResult.length++;
        }
        result = add(result, tempResult);
        ptr2 = ptr2->next;
    }
    return reverseLinkedList(result);
}

SBI div1(SBI num1,SBI num2)
{
    SBI quotient;
    SBI temp1=reverseLinkedList(num1);
    SBI temp2=reverseLinkedList(num2);
    quotient.L = NULL;
    quotient.length = 0;
    SBI remainder = temp1;
    while (compare(remainder, temp2) >= 0) 
    {
        SBI temp;
        temp.L = NULL;  
        temp.length = 0;
        int count = 0;
        while (compare(remainder, temp2) >= 0) 
        {
            remainder = sub(remainder, temp2);
            count++;
        }
        insertAtEnd(&(temp.L), count);
        temp.length = 1;
        quotient = add(quotient, temp);
    }
    return reverseLinkedList(quotient);
}

// Function to display a big integer represented as a linked list
void display(SBI num) 
{
    struct node *current = num.L;
    while (current != NULL) 
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}
