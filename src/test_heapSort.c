#include<stdio.h>
#include<stdlib.h>

#include"zcj_heapSort.h"

int main(int argc, char *argv[])
{
  int len,i;

  scanf("%d",&len);
  int *arr=malloc(sizeof(int)*len);
  for(i=0;i<len;i++)
    scanf("%d",&arr[i]);
  
  printf("before sorted:\n");
  for(i=0;i<len;i++){
    printf("%d ",arr[i]);
  }
  printf("\n");

  heapSort(arr,len);
  
  printf("after sorted:\n");
  for(i=0;i<len;i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
  
  free(arr);
  
  return 0;
}
