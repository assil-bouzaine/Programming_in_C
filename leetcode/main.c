#include<stdio.h>
#include<stdlib.h>
#include "leetcode.h"

int main()
{
  int rows1 = 3;
    int* colSizes1 = malloc(rows1 * sizeof(int));

    int** mat1 = malloc(rows1 * sizeof(int*));
    mat1[0] = (int[]){1, 2, 3};  colSizes1[0] = 3;
    mat1[1] = (int[]){4, 5, 6};  colSizes1[1] = 3;
    mat1[2] = (int[]){7, 8, 9};  colSizes1[2] = 3;

    diagonalSum(mat1, rows1, colSizes1);
    free(colSizes1); free(mat1);
}
