#ifndef HEAP_H
#define HEAP_H

#include<stdio.h>
#include<stdlib.h>

#define HEAP_CAPACITY 4096

typedef enum {FALSE, TRUE} Bool;
char myHeap[HEAP_CAPACITY];

typedef struct list_tag
{
    struct list_tag *prev;
    struct list_tag *next;
    size_t size;
    Bool isFree;
    Bool mark; /* mark and sweep */
    int count; /* reference count */
}list;

typedef struct TreeNodeTag
{
    int key;
    Bool mark;
    struct TreeNodeTag* left;
    struct TreeNodeTag* right;
}TreeNode;

void InitialiseHeap();
void *MyMalloc(size_t size);
void ShowList();
void PointerAssignment(int** ptr1, int** ptr2);
void GC_ReferenceCounting();
void MarkingTreeTraversal(TreeNode* root);
void GC_Sweep();


#endif