#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include<stdio.h>

#define V 9 /* represents the number of vertices in the graph */


void InitializeMatrix(int mat[][V]);
void ShowAdjacencyMatrix(int mat[][V]);
void SetMatrix1(int mat[][V]);
void SetMatrix2(int mat[][V]);
void MarkAndSweepGC(int mat[][V]);
void ReferenceCountGC(int mat[][V]);

#endif