#include "leetcode.h"
#include<stdlib.h> 
#include<stdio.h> 
#include<stdbool.h> 


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

//containsDuplicate
bool containsDuplicate(int* nums, int numsSize)
{
  // compare function is needed for qsort()
  int compare(const void* a, const void* b)
  {
    return (*(int*)a - *(int*)b);
  }

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

}
