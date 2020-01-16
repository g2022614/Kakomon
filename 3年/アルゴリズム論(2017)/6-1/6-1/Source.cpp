#include <stdio.h>
#include <stdlib.h>

#define NUM 8

struct harea { /* �f�[�^���i�[����\���́@*/
	int flag; /* �f�[�^�i�[�̏�� 0:�� 1:�L�@*/
	int data;/* �f�[�^�@*/
};

void hash_add(struct harea a[], int hsize, int key);
int hash_search(struct harea a[], int hsize, int key);

int main(void){
	int i, ky, idx;
	int x[NUM];
	int hsize = 1.5*8;
	struct harea ha[12];/* �f�[�^�i�[�ꏊ */

	for (i = 0; i < hsize; i++)
		ha[i].flag = ha[i].data = 0;
	printf(" Input integer number %d times \n", NUM);
	
	for (i = 0; i < NUM; i++) {
		printf("x[%d]:", i);
		scanf_s("%d", &x[i]);
	}

	for (i = 0; i < NUM; i++) 
		hash_add(ha, hsize, x[i]);
	
	printf("Number to search:");
	scanf_s("%d", &ky);
	idx = hash_search(ha, hsize, ky);
	
	if (idx == -1)
		printf("Searching was failed!\n");
	else
		printf("%d is located at %d \n", ky, idx);

	for (i = 0;i<NUM;i++)
		printf("%d.%d\n",i,ha[i].data);
	return 0;
}

void hash_add(struct harea a[], int hsize, int key){
	int pos;
	pos = key % hsize; /* �n�b�V���֐��@*/
	while (a[pos].flag != 0) {
		if (a[pos].flag>0) {
			if (a[pos].data == key)
				return;
		}
		pos = (pos + 1) % hsize;/* �I�[�v���A�h���X�@*/
	}
	a[pos].flag = 1; /* �f�[�^�i�[�̏�ԁ@*/
	a[pos].data = key; /* �f�[�^�i�[�@*/
}

int hash_search(struct harea a[], int hsize, int key){
	int pos, ret;
	pos = key % hsize; /* �n�b�V���֐��@*/
	ret = -1; /* �T�����ʁ@�����l�@*/
	while (a[pos].flag != 0) {
		if (a[pos].flag>0) {
			if (a[pos].data == key) {
				ret = pos;
				break;
			}
		}
		pos = (pos + 1) % hsize; /* �I�[�v���A�h���X�@���`�T���@*/
	}
	return ret; /* �T�����ʁ@ -1: ���s�@*/
}