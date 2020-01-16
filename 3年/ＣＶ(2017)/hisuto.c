#include<stdio.h>

int main (void){
  int i,j,k,cnt[7]={},lv[12]={};  
  int data[4][4] = {{0,2,2,7},
		    {0,2,3,7},
		    {1,1,5,7},
		    {1,1,6,7}};

  printf("入力画素\n");
  for(i=0;i<4;i++){
    for(j=0;j<4;j++)
      printf("%2d",data[i][j]);
    printf("\n");
  }
  printf("\n");
  
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){ 
      for(k=0;k<8;k++){ 
	if(data[i][j] == k)  
	  cnt[k]++;
      }
    }
  }

  for(k=0;k<8;k++)
    printf("%d画素の個数 = %2d\n",k,cnt[k]);

  

  return 0;
}
