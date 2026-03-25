#ifndef LEETCODE_H
#define LEETCODE_H


#include<stdbool.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);
void reverseString(char* s, int sSize);
bool containsDuplicate(int* nums, int numsSize);
bool isAnagram(char* s, char* t);
int diagonalSum(int** mat, int matSize, int* matColSize);
char *mergeAlternately(char * word1, char * word2);
char *gcdOfStrings(char* str1, char* str2);


#endif // LEETCODE_H
