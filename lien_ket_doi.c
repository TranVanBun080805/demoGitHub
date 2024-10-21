#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
struct node *GenerateDoublyLinkedList(const int A[], const int N)
{
    struct node *start = (struct node *)malloc(sizeof(struct node));
    struct node *p, *q;
    q = start;
    start->data = A[0];
    start->prev = NULL;
    for (int i = 1; i < N; i++)
    {
        p = (struct node *)malloc(sizeof(struct node));
        q->next = p;
        p->data = A[i];
        p->prev = q;
        q = p;
    }
    q->next = NULL;
    return start;

};
struct node *InsertNode(struct node *start, const int value)
{
    struct node *p = start;
    struct node *q, *a;
    if (start == NULL)
    {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->data = value;
        newNode->next = NULL;
        newNode->prev = NULL;
        return newNode;
    }
    else
    {
        while (p->next != NULL && p->data <= value)
        {
            p = p->next;
        }
        if (p->next == NULL && p->data < value)
        {
            a = (struct node *)malloc(sizeof(struct node));
            p->next = a;
            a->data = value;
            a->next = NULL;
            a->prev = p;
            return start;
        }
        if (p->prev == NULL)
        {
            a = (struct node *)malloc(sizeof(struct node));
            p->prev = a;
            a->data = value;
            a->next = p;
            a->prev = NULL;
            return a;
        }
        a = (struct node *)malloc(sizeof(struct node));
        q = p->prev;
        a->data = value;
        q->next = a;
        p->prev = a;
        a->next = p;
        a->prev = q;
        return start;
    }
};
struct node *MergeSortedLinkedList(struct node *start1, struct node *start2)
{
    if (start1 == NULL) return start2;
    if (start2 == NULL) return start1;

    struct node *start = NULL;
    struct node *p = NULL;
    struct node *q;
    if (start1->data < start2->data)
    {
        start = p = start1;
        start1 = start1->next;
    }
    else
    {
        start = p = start2;
        start2 = start2->next;
    }

    q = p;
    while (start1 != NULL && start2 != NULL)
    {
        if (start1->data < start2->data)
        {
            q->next = start1;
            start1->prev = q;
            q = start1;
            start1 = start1->next;
        }
        else
        {
            q->next = start2;
            start2->prev = q;
            q = start2;
            start2 = start2->next;
        }
    }
    if (start1 != NULL)
    {
        q->next = start1;
        start1->prev = q;
    }
    else if (start2 != NULL)
    {
        q->next = start2;
        start2->prev = q;
    }

    return start;
}
bool IsListSymmetric(struct node *start, struct node *end)
{
    if(start==NULL || end==NULL || start==end || start->next==end)
    {
        return true;
    }
    if(start->data!=end->data)
    {
        return false;
    }
   return IsListSymmetric(start->next,end->prev);
}



int main()
{
    struct node *start;
    printf("cau 1:\n");
    int E[]={1,2,3,4,5,6};
    int e = sizeof(E) / sizeof(E[0]);
    start=GenerateDoublyLinkedList(E, e);
    for(int i=0;i<e;i++)
    {
        printf("%d, ",start->data);
        start=start->next;
    }
    printf("\n");
    printf("cau 2:\n");
    int D[]={1, 2, 3, 6, 7, 8};
    int d = sizeof(D) / sizeof(D[0]);
    start=GenerateDoublyLinkedList(D, d);
    start=InsertNode(start,5);
    for(int i=0;i<d;i++)
    {
        printf("%d, ",start->data);
        start=start->next;
    }
    printf("\n");
    printf("cau 3:\n");
     int B[] = {1, 332, 5};
     int C[] = {2, 3, 6};
     int b = sizeof(B) / sizeof(B[0]);
     int c = sizeof(C) / sizeof(C[0]);
     struct node *start1 = GenerateDoublyLinkedList(B, b);
     struct node *start2 = GenerateDoublyLinkedList(C, c);
     struct node *node = MergeSortedLinkedList(start1, start2);
     for (int i = 0; i < c + b; i++)
     {
         printf("%d, ", node->data);
         node = node->next;
     }
     printf("\n");
     printf("cau 4:\n");
    int A[]={1, 4, 6, 1, 5, 1, 6, 4, 1};
    int N = sizeof(A) / sizeof(A[0]);
    start = GenerateDoublyLinkedList(A, N);
    struct node *end=start;
    do
    {
        end=end->next;
    } while(end->next!=NULL);
    if(IsListSymmetric(start,end))
    {
        printf("day la ham doi xung");
    }
    else
    {
        printf("day khong phai la ham doi xung");
    }
    free(start);
    free(end);
    free(start1);
    free(start2);
    free(node);
}

