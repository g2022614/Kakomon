#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void get_data(void);
void rgb_to_ybr(void);
int round_out();
int conversion(int i);
void processing(void);
void  ybr_to_rgb(void);
void put_data(void);

unsigned char header[54],imgin[3][512][512],imgout[3][512][512];
int width,height;

int main(void){

  get_data();
  rgb_to_ybr();
  processing();
  ybr_to_rgb();
  put_data();
 
 return 0;
}

void get_data(void){
  int i,j,k,filesize,offset,bits,byte;
  char name[100];
  FILE *fp;

  printf("入力ファイル名を入力してください:");
  scanf("%s",name);

  fp = fopen(name,"rb");
  if(fp == NULL){
    printf("ファイルをオープンできませんでした。\n");
    exit(1);
  }
  printf("ファイルをオープンしました。\n");

  for(i=0;i < 54;i++)
    header[i] =  fgetc(fp);

  for(i=0;i<54;i++){
    if(i == 5){
      printf("\n<ファイルサイズ>\n");
      filesize = conversion(i);
      printf("%dバイト\n",filesize);
    }  
    else if(i == 13){
      printf("\n<オフセット>\n");
      offset = conversion(i);
      printf("%dバイト\n",offset);
    }
    else if(i == 21){
      printf("\n<画像の幅>\n");
      width = conversion(i);
      printf("%d画素\n",width);
    }
    else if(i == 25){
      printf("\n<画像の高さ>\n");
      height = conversion(i);
      printf("%dライン\n",height);
    }
    else if(i == 29){
      printf("\n<1画素あたりのビット数>\n");     
      bits = conversion(i);
      printf("%dビット\n",bits);
    }
  }
  byte = filesize - offset - width * height * (bits / 8);
  printf("\n<挿入ビット数>\n");
  printf("%dバイト\n",byte);  
  
  for(i = height-1;i >= 0;i--){
    for(j = 0;j < width;j++){
      for(k = 2;k >= 0;k--)
	imgin[k][i][j] = fgetc(fp);
    }
  }

  fclose(fp);
  printf("ファイルをクローズしました。\n");

}

void rgb_to_ybr(){
  int i,j,k;
  float conversion[3][3] = {{0.2990,0.5870,0.1140},
			    {-0.1687,-0.3313,0.5000},
			    {0.5000,-0.4187,-0.0813}};  
  double tmp[3][512][512];

  for(k=0;k<3;k++){    
      for(i=0;i<height;i++){
	for(j=0;j<width;j++){
	  tmp[k][i][j] = conversion[k][0] * imgin[0][i][j] + conversion[k][1] * imgin[1][i][j] + conversion[k][2] * imgin[2][i][j];
	  tmp[k][i][j] = round_out(tmp[k][i][j]);

	if(k!=0){
	  tmp[k][i][j] += 128;
	  if (tmp[k][i][j] > 255)
	    tmp[k][i][j] = 255;
	  else  if (tmp[k][i][j] < 0)
	    tmp[k][i][j] = 0;	  
	}
      }
    }
  }

  for(k=0;k<3;k++){
   for(i=0;i<height;i++){
      for(j=0;j<width;j++){
        imgin[k][i][j] = tmp[k][i][j];
      }
    }
  }


}

int round_out(double data){
  double offset;
  
  if (data >= 0.0)
    offset=0.5;
  else
    offset=-0.5;
  data += offset;

 return data;
}

int conversion(int n){
  int ans=0,i,j;

  if(n == 29)
    ans = header[n] * pow(2,8) +  header[n-1] * pow(2,0);
  else{
    for(i=0,j=24; i<4; i++,j-=8)
      ans += (header[n-i] * pow(2,j));
  }

  return ans;
}
void processing(void){
  int i,j,k,level[256]={},l_max,no_max;
  double n_level[256]={};

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      for(k=0;k<256;k++){
        if(imgin[0][i][j] == k){
          level[k]++;
        }
      }
    }
  }

  printf("\n<度数表>\n");
  l_max = level[0];
  for(i=0;i<256;i++){
    if(l_max < level[i]){
      l_max = level[i];
      no_max = i;
    }
    printf("level%4d : %5d\n",i,level[i]);
  }

  printf("\n<最大度数>\n");
  printf("level%4d : %5d\n",no_max,level[no_max]);

  printf("\n<度数表>\n");
  for(i=0;i<256;i++){
    n_level[i] = ((double)level[i] * 100 / (double)l_max);
    printf("level%4d : %5d ---> %4.0f\n",i,level[i],n_level[i]);
  }
  
  for(k=0;k<3;k++){
    for(i=height-100;i<height;i++){
      for(j=0;j<256;j++){
	if(k==0)
	  imgin[k][i][j] = 0;
	else if(k == 1)
	  imgin[k][i][j] = 128;
	else
	  imgin[k][i][j] = 128;
      }
    }
  }

  for(k=0;k<3;k++){
    for(j=0;j<256;j++){
      for(i=height;i>height-n_level[j];i--){
	if(k==0)
	  imgin[k][i][j] = 0;
	else if(k == 1)
	  imgin[k][i][j] = 128;
	else
	  imgin[k][i][j] = 255;
      }
    }
  }  

  for(k=0;k<3;k++){
    for(i=0;i<height;i++){
      for(j=0;j<width;j++)
	imgout[k][i][j] = imgin[k][i][j];
    }
  }

  printf("\n出力画像データを作成しました。\n");
  
}

void ybr_to_rgb(void){
  int i,j,k;
  float r_conversion[3][3] = {{1.0000,0.0000,1.4020},
			      {1.0000,-0.3441,-0.7141},
			      {1.0000,1.7720,0.0000}};
  double tmp[3][512][512];

  for(k=0;k<3;k++){
    for(i=0;i<height;i++){
      for(j=0;j<width;j++){
	if(k==0)
	  tmp[k][i][j] = r_conversion[k][0] * imgout[0][i][j] + r_conversion[k][1] * (imgout[1][i][j]-128) + r_conversion[k][2] * (imgout[2][i][j]-128);
	else
	  tmp[k][i][j] = r_conversion[k][0] * (imgout[0][i][j]-128) + r_conversion[k][1] * (imgout[1][i][j]-128) + r_conversion[k][2] * (imgout[2][i][j]-128);
	tmp[k][i][j] = round_out(tmp[k][i][j]);
	
	if(k!=0){
	  tmp[k][i][j] += 128;
	  if (tmp[k][i][j] > 255)
	    tmp[k][i][j] = 255;
	  else  if (tmp[k][i][j] < 0)
	    tmp[k][i][j] = 0;
	}	    	
      }
    }
  }
  
  for(k=0;k<3;k++){
    for(i=0;i<height;i++){
      for(j=0;j<width;j++)
	imgout[k][i][j] = tmp[k][i][j];      
    }  
  }
     
}

void put_data(void){
  int i,j,k;
  char name[100];
  FILE *fp;

  printf("\n出力ファイル名を入力してください。:");
  scanf("%s",name);

  fp = fopen(name,"wb");
  if(fp == NULL){
    printf("ファイルをオープンできませんでした。\n");
    exit(1);
  }
  printf("フィルをオープンしました。\n");

  for(i=0;i<54;i++)
    fputc(header[i],fp);
  for(i = height-1;i >= 0;i--){
    for(j = 0;j < width;j++){
      for(k = 2;k >= 0;k--)
	fputc(imgout[k][i][j],fp);
    }
  }

  fclose(fp);
  printf("ファイルをクローズしました。\n");

}
