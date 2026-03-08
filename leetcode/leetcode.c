#include "leetcode.h"
#include<stdlib.h> 
#include<stdio.h> 
#include<stdbool.h> 
#include<string.h> 


// twoSum
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
  for(int i = 0 ; i < numsSize; i++)
  { 
    for(int j = i +1 ; j < numsSize; j++)
    {
      if(nums[i] + nums[j] == target)
      {
        int* result = malloc(2 * sizeof(int));
        result[0] = i;
        result[1] = j;
        *returnSize = 2;
        return result;
      }
    }
  }


  *returnSize = 0;
  return NULL;
}

// reverseString
void reverseString(char* s, int sSize)
{
  int i = 0;
  int j = sSize - 1;

  while(i < j)
  {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
    i++;
    j--;
  }
}

// compare function is needed for qsort()
int compare(const void* a, const void* b)
{
  return (*(int*)a - *(int*)b);
}


int compareString(const void* a, const void* b)
{
  char ca = *(char*)a;
  char cb = *(char*)b;
  return (ca > cb) - (ca < cb);
}

//containsDuplicate
bool containsDuplicate(int* nums, int numsSize)
{

  qsort(nums,numsSize,sizeof(int),compare);
  for(int i = 1; i < numsSize; i++) {
    if(nums[i] == nums[i - 1])
    {
      return true;
    }
  }
  return false;
}

// isAnagram
bool isAnagram(char* s, char* t)
{
  if(strlen(s) != strlen(t))
    return false;

  char* s_copy = strdup(s);
  char* t_copy = strdup(t);
  qsort(s_copy,strlen(s_copy),sizeof(char),compareString);
  qsort(t_copy,strlen(t_copy),sizeof(char),compareString);
  int result = strcmp(s_copy, t_copy);
  return (result == 0)? true: false;
}

//diagonalSum
int diagonalSum(int** mat, int matSize, int* matColSize)
{
  
}
