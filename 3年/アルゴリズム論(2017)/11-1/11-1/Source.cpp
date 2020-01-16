#include <stdio.h>

#pragma warning(disable:4996)

int count = 0; /* 比較回数カウンタ　*/
int simple_match(char txt[], char pat[]); /* 関数プロトタイプ */

int main(void){
	int idx; /* 照合位置　*/
	char s1[80];/* テキスト　*/
	char s2[80]; /* パターン　*/

	printf(" Input text :"); /* テキスト入力　*/
	scanf("%s", s1);
	printf(" Input pattern :"); /* パターン入力　*/
	scanf("%s", s2);
	idx = simple_match(s1, s2); /* 単純法関数　*/
	if (idx == -1) /* 結果表示　*/
		printf(" No pattern found in the text\n");
	else
		printf(" Pattern was found at %d \n", idx + 1);
	printf(" Number of comparison=%d\n", count); /* 比較回数表示　*/
	
	return 0;
}

int simple_match(char txt[], char pat[]){
	int pt = 0; /* テキスト　カーソル　*/
	int pp = 0; /* パターン　カーソル　*/

	while (txt[pt] != '\0' && pat[pp] != '\0') { /* 照合 */
		if (txt[pt] == pat[pp]) { /* 一致　*/
			pt++;
			pp++;
			count++;
		}
		else { /* 不一致　*/
			pt = pt - pp + 1;
			pp = 0;
			count++;
		}
	}
	if (pat[pp] == '\0')
		return (pt - pp);/* 戻り値：照合結果　*/
	
	return -1;
}