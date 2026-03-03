#include<stdio.h>
#include<stdlib.h>
#include "leetcode.h"

int main()
{
  int nums[] = {3,2,4};
  int target = 6;
  int resultSize;

  int* result = twoSum(nums, 3,target,&resultSize);
 
  for(int i=0; i < resultSize; i++)
  {
    printf("%d \n", result[i]);
  }

  free(result);
}
