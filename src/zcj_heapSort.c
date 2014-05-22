#include<stdio.h>

#include"zcj_heapSort.h"

void heapSort(int *arr,int len){
  int i,tmp;

  for(i=len/2;i>=0;i--){
    heapify(arr,len,i);
  }

  for(i=len-1;i>=1;i--){
    tmp=arr[0];
    arr[0]=arr[i];
    arr[i]=tmp;

    heapify(arr,i,0);
  }
}

void heapify(int *arr,int len,int index){
  int max=index;
  if(2*index+2<len){
    max=(arr[2*index+2]>arr[2*index+1])?(2*index+2):(2*index+1);
    max=(arr[max]>arr[index])?max:index;
  }else if(2*index+1<len){
    max=2*index+1;
    max=(arr[max]>arr[index])?max:index;
  }
  if(max!=index){
    int tmp;
    tmp=arr[index];
    arr[index]=arr[max];
    arr[max]=tmp;
    heapify(arr,len,max);
  }
}
