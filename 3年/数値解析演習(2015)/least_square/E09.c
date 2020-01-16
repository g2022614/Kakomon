#include<stdio.h>
#include<math.h>
#define N  1
#define N1 N+1
#define M  3
#define TRUE 1
#define FALSE 0

float x[M]={ 1.0, 2.0, 3.0},
      f[M]={2.5, 3.5, 6.0},
      a[N1][N1],b[N1],c[N1];
int sw;

/*=====================================================================*/
/*** �ׂ�������߂� ***/
float gg(int j,
        float x)
{
  float wk;
  int i;

  wk = 1.0;
  for(i = 0; i<j; i++){
    wk = wk*x;
  }
  return(wk);
}

/*=====================================================================*/
/*** x = xx�̂Ƃ��̋ߎ��������̒l�����߂� ***/
float fvalue(float xx)
{
  float wk;
  int i;

  wk = 0.0;
  for(i = 0; i<N1; i++){
    wk = wk + c[i]*gg(i,xx);
  }
  return(wk);
}

/*=====================================================================*/
/*** �l�����ւ���D�i�����s�{�b�g�I��@�j ***/
void swap(float* wk1,
          float* wk2)
{
  float w;
  w= *wk1; *wk1=*wk2; *wk2=w;
}

/*=====================================================================*/
/*** �|���o���@ ***/
void sweep(int* sw){
  int i, j, k, ik;
  float ak, aik;
  float EPSILON = 1.0e-5;
  
  *sw = TRUE;

  for(k = 0; k < N1; k++){
    ak = a[k][k];

    /*>>> Pivotting ***/
    if(fabs(ak) <= EPSILON){
      ik = k + 1;
      while((ik < N1)&&(fabs(a[ik][k]) < EPSILON)) ik++;
      if(ik < N1){
        for(j = k; j < N1; j++){
          swap(&a[k][j], &a[ik][j]);
        }
	swap(&b[k], &b[ik]);
	ak = a[k][k];
      }
      else{
	printf("pivot is 0 !!\n");
	*sw = FALSE;
	return;
      }
    } /* end if(fabs(ak) <= EPSILON) */
    /*<<< Pivotting ***/

    for(j = k; j < N1; j++){
      a[k][j] /= ak;
    }
    b[k] /= ak;

    for(i = 0; i < N1; i++){
      if(i != k){
        aik = a[i][k];
        for(j = k; j < N1; j++){
          a[i][j] -= aik*a[k][j];
        } /* end j */
        b[i] -= aik*b[k];
      } /* end if(i!=k) */
    } /* end i */
  } /* end k */

  for(k = 0; k < N1; k++){
    c[k] = b[k];
  }
}

/*=====================================================================*/
/*** �ŏ����@ ***/
void leasqr(int* sw)
{
  float wk;
  int i, j, k;

  for(i = 0; i < N1; i++){
    for(j = i; j < N1; j++){
      wk = 0.0;
      for(k = 0; k < M; k++){
	wk += gg(i, x[k]) * gg(j, x[k]);
      }
      a[i][j] = wk;
      a[j][i] = wk;
    }
  }
  for(i = 0; i < N1; i++){
    wk = 0.0;
    for(k = 0; k < M; k++){
      wk += gg(i,x[k])*f[k];
    }
    b[i] = wk;
  }
  sweep(sw);
}

/*=====================================================================*/
/*** �ߎ��������֐��ɂ��f�[�^����o�� ***/
void output_result(void){
  int i;
  double interval;
  double num_point = 51; /* 51�_�o�� */
  double num_segment;
  double delta;
  FILE *outfile;

  num_segment = num_point - 1;

/*** Open output file ***/
  if((outfile = fopen("result.csv", "w")) == NULL){
    fprintf(stderr, "Can't open file \n");
    exit(2);
  }

  interval = x[M-1] - x[0];
  delta = interval / num_segment;
  for(i = 0; i < num_point; i++){
    double xx = x[0] + i * delta;
    double ff = fvalue(xx);
    fprintf(outfile, "%e, %e\n", xx, ff);
  }
  fclose(outfile);
}

/*=====================================================================*/
/*** ���̃f�[�^���o�� ***/
void output_data(void){
  int i;
  FILE *outfile;

/*** Open output file ***/
  if((outfile = fopen("data.csv", "w")) == NULL){
    fprintf(stderr, "Can't open file \n");
    exit(2);
  }

  for(i = 0; i < M; i++){
    fprintf(outfile, "%e, %e\n", x[i], f[i]);
  }
  fclose(outfile);
}
  
/*=====================================================================*/
int main(void)
{
  float xx;
  int i;

  sw = TRUE;
  leasqr(&sw);
  output_data();
  output_result();

  if(sw){
    printf("�֐��̌W�� =\n");
    for(i=0;i<N1;i++){
      printf("\n   c[%2d] = %12.6e",i,c[i]);
    }
    while(1){
      printf("\n x �̒l����͂��ĉ������B\n");
      scanf("%f", &xx);
      if((xx >= x[0]) && (xx <= x[M-1])){
        printf("\n �֐��̒l = %e \n",fvalue(xx));
      }
      else{
        return 0;
      }
    }
  }
  else{
    printf("\n �ߎ��������֐��͋��߂��܂���ł����B\n");
  }
}
