#include "heap.h"
#include "adjmatrix.h"

int main()
{
    printf("START \n");

    InitialiseHeap();
    


    int m1[V][V];
    int m2[V][V];

    InitializeMatrix(m1);
    InitializeMatrix(m2);

    SetMatrix1(m1);
    SetMatrix2(m2);

    // ShowAdjacencyMatrix(m1);
    // ReferenceCountGC(m1);
    // ShowAdjacencyMatrix(m1);

    ShowAdjacencyMatrix(m2);
    MarkAndSweepGC(m2);
    ShowAdjacencyMatrix(m2);


    printf("\nEND \n");

    return 0;
}
