#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int byte_32(int a,int b,int c,int d);
int round_off(double data);

void get_data(void);
void rgb_to_ybr(void);
void processing(void);
void ybr_to_rgb(void);
void put_data(void);

unsigned char header[54] = {};
unsigned char imgin[3][512][512] = {},imgout[3][512][512] = {};
int width,height,byte_insert;
int value = 96;

int main(void){

  get_data();
  rgb_to_ybr();
  processing();
  ybr_to_rgb();
  put_data();
  
  return 0;
}

void get_data(void){
  FILE *fp;
  int c,i,a,b,j,filesize,offset,bits;
  char filename[100];

  fp = fopen("books.bmp","rb");
  
  if(fp == NULL){
    printf("ファイルをオープンできません。\n");
    exit(1);
  }
  printf("ファイルをオープンしました。\n");

  c = fgetc(fp);
  for(i=0;i<54;i++){
    header[i] = c;
    c = fgetc(fp);
  }
  
  filesize = byte_32(header[2],header[3],header[4],header[5]);
  offset = byte_32(header[10],header[11],header[12],header[13]);
  width = byte_32(header[18],header[19],header[20],header[21]);
  height = byte_32(header[22],header[23],header[24],header[25]);
  bits = header[28] * pow(2,0) + header[29] * pow(2,8);
  byte_insert = filesize - offset - width * height * (bits/8);

  for(a = height - 1; a >= 0; a--){
    for(b = 0;b < width; b++){
      for(j = 2; j >= 0; j--){
        imgin[j][b][a] = c;
        c = fgetc(fp);
      }
    }
  }

  fclose(fp);
  printf("ファイルをクローズしました。\n\n");

}

void rgb_to_ybr(void){
  int i,j,k;
  double col_space[3][512][512] = {};
  double color[3][3] = {{0.2990,0.5870,0.1140},
                        {-0.1687,-0.3313,0.5000},
                        {0.5000,-0.4187,-0.0813}};

  for(k=0;k<3;k++){  
    for(i=0;i<height;i++){
      for(j=0;j<width;j++){
	col_space[k][j][i] = color[k][0] * imgin[0][j][i] + color[k][1] * imgin[1][j][i] + color[k][2] * imgin[2][j][i];

	col_space[k][j][i] = round_off(col_space[k][j][i]);

	if(k!=0)
	  col_space[k][j][i] += 128;
	if(col_space[k][j][i] > 255)
	  col_space[k][j][i] = 255;
	else if(col_space[k][j][i] < 0)
	  col_space[k][j][i] = 0;
      }
    }
  }

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      for(k=2;k>=0;k--)
	imgin[k][i][j] = col_space[k][i][j];
    }
  }
  
}
  
int byte_32(int a,int b,int c,int d){
  int result=0;

  result = a * pow(2,0) + b * pow(2,8) + c * pow(2,16) + d * pow(2,24);

  return result;
}

int round_off(double data){
  double offset;
  int result;

  if(data >= 0.0)
    offset = 0.5;
  else
    offset = -0.5;

  result = (int)(data + offset);

  return result;
}

void processing(void){
  int i,j,k,l,m,n=0,cnt=0,h_1=8,w_1=8;
  int x,y,tmp[3][512][512];
  int h_split = height/16,w_split = width/16;  
  double p=0,filter[3][3] = {{0,-1,0},
                             {-1,5,-1},
                             {0,-1,0}};


  while(cnt < height){
    for(i=0;i<16;i++){
      for(j=0;j<16;j++)
	if(value > tmp[0][i][j])
	  tmp[0][m][n] = imgin[0][k+i][l+j];
	else
	  tmp[0][m][n] = imgin[0][k+i][l+j];
    }
    n++;
    k+=16;

    if(k>width){
      k = 0;
      n = 0;
      l+=16;
      m++;
      cnt+=16;
    }
  }

  for(k=1;k<3;k++){
    for(i=0;i<height;i++){
      for(j=0;j<width;j++)    
	tmp[k][i][j] = 128;
    }
  }

  for(k=0;k<3;k++){
    for(i=0;i<height;i++){
      for(j=0;j<width;j++)      
	imgout[k][i][j] = tmp[k][i][j];      
    }
  }

}

void ybr_to_rgb(void){
  int i,j,k;
  double out_rgb[3][512][512] = {};
  double re_color[3][3] = {{1.0000,0.0000,1.4020},
                           {1.0000,-0.3441,-0.7141},
                           {1.0000,1.7720,0.0000}};
  
  for(k=0;k<3;k++){
    for(i=0;i<height;i++){
      for(j=0;j<width;j++){
	out_rgb[k][j][i] = re_color[k][0] * imgout[0][j][i] + re_color[k][1] * (imgout[1][j][i] - 128) + re_color[k][2] * (imgout[2][j][i] - 128);
	out_rgb[k][j][i] = round_off(out_rgb[k][j][i]);
	if(out_rgb[k][j][i] > 255)
	  out_rgb[k][j][i] = 255;
	else if(out_rgb[k][j][i] < 0)
	  out_rgb[k][j][i] = 0;
      }
    }
  }

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      for(k = 2;k >= 0; k--)
        imgout[k][j][i] = out_rgb[k][j][i];
    }
  }

}

void put_data(void){
  FILE *fp;
  int i,j,a,b;
  char filename[100];

  printf("出力ファイル名を入力して下さい：");
  scanf("%s",filename);

  fp = fopen(filename,"wb");
  if(fp == NULL){
    printf("ファイルをオープンできません。\n");
    exit(1);
  }
  printf("ファイルをオープンしました。\n");

  for(i=0;i<54;i++)
    fputc(header[i],fp);

  for(a = height - 1; a >= 0; a--){
    for(b = 0;b < width; b++){
      for(j = 2; j >= 0; j--){
        fputc(imgout[j][b][a],fp);
      }
    }
  }

  fclose(fp);
  printf("ファイルをクローズしました。\n");

}
