#ifndef SORTING_H
#define SORTING_H
#include "sorting.h"
#endif
/******************
* Function Name:quicksort
* Input:void* arr(array to sort), int start(index to start sorting from, int stop(index to stop sorting),
                void(*swap)(void*, int, int)(swap function), int(*compare)(void*, int, int))(compare function)
* Output:none
* Function Operation:gets a generic array to sort with indexes to sort from to and generic compare and swap functions
 *                  and sorts the array by quicksort algorithm
******************/

void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int))
{
    if (start >= stop - 1)
    {
        return;
    }
    int pivot=start;
    int j=start;
    for (int i = start+1; i <stop ; i++)
    {
     if(compare(arr,i,pivot))
     {
         j++;
         if (i != j)
         {
             swap(arr,i,j);
         }
     }
    }
    swap(arr, start, j);
    quicksort(arr, start, j,swap,compare);
    quicksort(arr, j + 1, stop,swap,compare);


}