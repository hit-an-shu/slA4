#include "heap.h"

list* list_ptr = (list*) myHeap;

void InitialiseHeap()
{
    list_ptr->prev = NULL;
    list_ptr->isFree = TRUE;
    list_ptr->next = NULL;
    list_ptr->count = 1;
    list_ptr->mark = FALSE;
    list_ptr->size = (HEAP_CAPACITY - sizeof(list));
}

void *MyMalloc(size_t size) /* first fit */
{
    Bool check = FALSE;
    void* ptr = NULL;
    list *lptr = list_ptr, *nptr; /* nptr for the new list block to be created for the remaining space after allocation */

    if(size == 0){
        ptr = NULL;
    }
    else {
        while(lptr != NULL && !check) /* traverse through the implicit list */
        {
            if((lptr->isFree) && ((size + sizeof(list)) <= lptr->size)) {
                ptr = (void*)(lptr + sizeof(list));/* this is the pointer to the allocated space */
                nptr = lptr + size + sizeof(list); /* next block is assigned */

                lptr->isFree = FALSE;
                nptr->isFree = TRUE;
                nptr->mark = FALSE;

                nptr->prev = lptr;
                nptr->next = lptr->next;
                if(lptr->next != NULL){lptr->next->prev = nptr;}
                
                lptr->next = nptr;
                
                nptr->size = lptr->size - size - sizeof(list);
                nptr->count = 1;
                lptr->size = size;
                check = TRUE;
            }
            lptr = lptr->next;
        }
    }
    return ptr;
}

/* free function expects that delete_ptr is same as returned by malloc */
list* MyFree(void* delete_ptr)
{
    list* lptr = (list* ) (delete_ptr - 576);

    list *prev_ptr, *next_ptr, *retval;
    prev_ptr = lptr->prev;
    next_ptr = lptr->next;

    lptr->isFree = TRUE;
    if(next_ptr == NULL || (next_ptr != NULL && !next_ptr->isFree))
    {
        retval = next_ptr;
    }
    
    if(next_ptr != NULL && next_ptr->isFree) /* here, short-circuiting protects us from null pointer dereferencing */
    {
        retval = next_ptr->next;
        lptr->size += next_ptr->size + sizeof(list);
        lptr->next = (next_ptr)->next;
    }
    if(prev_ptr != NULL && prev_ptr->isFree) /* here, short-circuiting protects us from null pointer dereferencing */
    {
        prev_ptr->size += lptr->size + sizeof(list);
        (prev_ptr)->next = lptr->next;
    }
    return retval;
}

void ShowList()
{
    list* lptr = list_ptr;
    while (lptr != NULL)
    {
        printf("\n");
        printf("lptr -> %p ", lptr); printf("ptr -> %p ", lptr+sizeof(list));
        if(lptr->next != NULL) {printf("next -> %p ", lptr->next);} else {printf("next = NULL ");}
        if(lptr->prev != NULL) {printf("prev -> %p ", lptr->prev);} else {printf("prev = NULL ");}
        if(lptr->isFree) {printf("FREE ");} else{printf("USED ");}
        printf("size = %d ", lptr->size);
        printf("count = %d \n", lptr->count);

        lptr = lptr->next;
    }
}

void PointerAssignment(int** ptr1, int** ptr2) /*ptr1 = ptr2*/ 
/*called when both are pointing to some memory in the heap or ptr2 is NULL and ptr1 is pointing to memory in heap*/
{
    if(ptr1 != NULL)
    {
        list* lptr1 = (list* ) (*ptr1 - 144); /* dealing with offsets */
        lptr1->count -= 1;
        if(ptr2 != NULL)
        {
            list* lptr2 = (list* ) (*ptr2 - 144);
            lptr2->count += 1;
        }
        *ptr1 = *ptr2;        
    }
}

void GC_ReferenceCounting()
{
    list* lptr = list_ptr;
    void* ptr;
    while (lptr != NULL)
    {
        ptr = (void*)(lptr + sizeof(list));
        if(lptr->count == 0)
        {
            lptr = MyFree(ptr);
        }
        if(lptr != NULL)
        {
            lptr = lptr->next;
        }        
    }
}

void GC_Sweep()
{
    list* lptr = list_ptr;
    void* ptr;
    while (lptr != NULL)
    {
        ptr = (void*)(lptr + sizeof(list));
        if(!lptr->mark)
        {
            lptr = MyFree(ptr);
        }
        else
        {
            lptr->mark = FALSE;
        }

        if(lptr != NULL)
        {
            lptr = lptr->next;
        }        
    }
}

void MarkingTreeTraversal(TreeNode* root) /* mark in inorder */
{
    TreeNode *curr, *prev;
  
    if(root != NULL)
    {
        curr = root;
        while(curr != NULL) 
        {
            if(curr->left == NULL) 
            {
                curr->mark = TRUE;
                curr = curr->right;
            }
            else 
            {
                prev = curr->left;
                while(prev->right != NULL && prev->right != curr)
                {
                    prev = prev->right;
                }

                if(prev->right == NULL) 
                {
                    prev->right = curr;
                    curr = curr->left;
                }
                else 
                {
                    prev->right = NULL;
                    curr->mark = TRUE;
                    curr = curr->right;
                }
            }
        }
    }
}