#include "adjmatrix.h"
#include "heap.h"


void InitializeMatrix(int mat[][V])
{
    int i, j;
    for(i = 0; i < V; i++)
    {
        for(j = 0; j < V; j++)
        {
            mat[i][j] = 0;
        }
    }
}

void ShowAdjacencyMatrix(int mat[][V])
{
    int i, j, k;
    int arr[V] = {0, 1, 2, 3, 5, 7, 8, 9, 10};
    

    printf(" \t%d", arr[0]);
    for(k = 1; k < 9; k++)
    {
        printf("\t%d", arr[k]);
    }
    printf("\n\n");

    
    for(i = 0; i < V; i++)
    {
        printf("%d\t", arr[i]);
        for(j = 0; j < V; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void InsertEdges(int mat[][V], int from, int to)
{
    if(from > 3)
    {
        from -= 1;
    }
    if(to > 3)
    {
        to -= 1;
    }
    if(from > 4)
    {
        from -= 1;
    }
    if(to > 4)
    {
        to -= 1;
    }

    mat[from][to] = 1;
    mat[to][from] = -1;
}

void RemoveEdges(int mat[][V], int from, int to)
{
    if(from > 3)
    {
        from -= 1;
    }
    if(to > 3)
    {
        to -= 1;
    }
    if(from > 4)
    {
        from -= 1;
    }
    if(to > 4)
    {
        to -= 1;
    }

    mat[from][to] = mat[to][from] = 0;
}

void SetMatrix1(int mat[][V])
{
    InsertEdges(mat, 0, 5);
    InsertEdges(mat, 5, 1);
    InsertEdges(mat, 1, 2);
    InsertEdges(mat, 1, 9);
    InsertEdges(mat, 1, 10);
    InsertEdges(mat, 3, 10);
    InsertEdges(mat, 3, 8);
    InsertEdges(mat, 7, 1);
    InsertEdges(mat, 7, 8);
    InsertEdges(mat, 8, 9);
}

void SetMatrix2(int mat[][V])
{
    InsertEdges(mat, 0, 1);
    InsertEdges(mat, 5, 1);
    InsertEdges(mat, 1, 2);
    InsertEdges(mat, 1, 9);
    InsertEdges(mat, 1, 10);
    InsertEdges(mat, 3, 10);
    InsertEdges(mat, 3, 8);
    InsertEdges(mat, 7, 1);
    InsertEdges(mat, 7, 8);
    InsertEdges(mat, 8, 9);
}

void DeleteNode(int i)
{
    if(i > 4)
    {
        i += 2;
    }
    else if(i > 3) // i == 4
    {
        i += 1;
    }
    printf("Node %d deleted \n", i);
}

void ReferenceCountGC(int mat[][V])
{
    int i, j;
    Bool notFound = TRUE;

    for(j = 1; j < V; j++)
    {
        notFound = TRUE;
        for(i = 0; i < V && notFound; i++)
        {
            if(mat[i][j] == 1)
            {
                notFound = FALSE;
            }
        }
        if(notFound)
        {
            DeleteNode(j);
            for(i = 0; i < V; i++)
            {
                mat[j][i] = mat[i][j] = 0;
            }
        }
    }
}

void MarkAndSweepGC(int mat[][V])
{
    int i, j;
    Bool found;
    int arr[V];
    arr[0] = 0; /* root */
    int arr_size = 1, prev_size = 0;

    /* Marking phase */
    while(prev_size < arr_size)
    {
        for(i = 1; i < V; i++)
        {
            if(mat[arr[prev_size]][i] == 1)
            {
                /*insert if not previously found*/
                found = FALSE;
                for(j = 0; j < arr_size && !found; j++)
                {
                    if(i == arr[j])
                    {
                        found = TRUE;
                    }
                }
                if(!found)
                {
                    arr[arr_size] = i;
                    arr_size++;
                }
            }
        }
        prev_size++;
    }

    /* Sweeping phase */
    for(i = 1; i < V; i++)
    {
        found = FALSE;
        for(j = 0; j < arr_size && !found; j++)
        {
            if(i == arr[j])
            {
                found = TRUE;
            }
        }
        if(!found)
        {
            DeleteNode(i);
            for(j = 0; j < V; j++)
            {
                mat[j][i] = mat[i][j] = 0;
            }
        }
    }
}