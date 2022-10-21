#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "definition.h"

int a[YMAX][XMAX];//a[][]������������
void clear(void);//��ջ���
void scene(void);//��ӡ����
void first_spawn_target(void);//��ʼ��
int spawn_target(void);//����Ŀ�꣬����Ŀ��ĺ����꣨�ڵ�0�����ɣ�
void move_target(void);//Ŀ���ƶ�
int trans_input(char);//������ת��Ϊ����
_Bool judge_input(int);//�ж������Ƿ���ȷ
int score = 0;

int main()
{
	_Bool fir=true;
	srand((unsigned int)time(NULL));
	float cps;
	_Bool restart=true, loop,starting=true;
	char ch;
	int input;
	double time;
	clock_t start, end;
	clear();
	first_spawn_target();
	while(restart)
	{
		system("cls");
		scene();
		ch = getch(stdin);
		input=trans_input(ch);
		if (judge_input(input))
		{
			if(starting)
				start = clock();
			starting = false;
			fir = false;
			move_target();
			system("cls");
		}
		else
		{
			if (fir)
				start = clock();
			end = clock();
			time = ((double)end - start) / CLK_TCK;
			if (time == 0)
				cps = 0;
			else
				cps = score / time;
			printf("GAME OVER!\nSCORE:%d\nTIME:%.2lf s\n",score,time);
			printf("CPS: % .2lf\nRESTART ? (y / n)",cps);
			do
			{
				ch = getchar();
				while (getchar() != '\n')
					continue;
				if (ch == 'y')
				{
					score = 0;
					starting = true;
					restart = true;
					loop = false;
				}
				else if (ch == 'n')
				{
					restart = false;
					loop = false;
				}
				else
				{
					puts("Please Enter 'y'or'n'");
					loop = true;
				}
			} while (loop);
		}
	}
	return 0;
}
void clear(void)
{
	int i, j;
	for (i = 0; i < YMAX; i++)
	{
		for (j = 0; j < XMAX; j++)
			a[i][j] = BLANK;
	}
	return;
}
void scene(void)
{
	int i, j;
	for (i = 0; i < YMAX; i++)
	{
		puts("|\n+---+---+---+---+");
		for (j = 0; j < XMAX - 1; j++)
		{
			if (a[i][j] == BLANK)
				printf("|   ");
			else
				printf("| # ");
		}
	}
	printf("|\n");
	puts("+---+---+---+---+");
	return;
}
void first_spawn_target(void)
{
	int i,x;

	for (i = 0; i < YMAX; i++)
	{
		x = rand() % 4;
		a[i][x] = TARGET;
	}
	return;
}
int spawn_target(void)
{
	int x;

	x = rand() % 4;
	return x;
}
void move_target(void)
{
	int i,j,temp;
	for (i = YMAX - 2; i >= 0; i--)
	{
		temp = a[i][0];
		for (j = YMAX - 1; j >= 0; j--)
		{
			a[i + 1][j] = temp;//��һ�е�j��=temp
			temp = a[i][j-1];//temp=��һ�е�j+1�����´�ѭ����һ�е�j��
		}
	}
	for(j=0;j<XMAX;j++)
		a[0][j] = BLANK;
	a[0][spawn_target()] = TARGET;
	return;
}
int trans_input(char ch)
{
	int ret_val;
	switch (ch)
	{
	case 'd':
		ret_val = 0;
		break;
	case 'D':
		ret_val = 0;
		break;
	case 'f':
		ret_val = 1;
		break;
	case 'F':
		ret_val = 1;
		break;
	case 'g':
		ret_val = 2;
		break;
	case 'G':
		ret_val = 2;
		break;
	case 'h':
		ret_val = 3;
		break;
	case 'H':
		ret_val = 3;
		break;
	default:
		ret_val = 0;
		break;
	}
	return ret_val;
}
_Bool judge_input(int input)
{
	int i,ans;
	for (i = 0; i < XMAX-1; i++)
	{
		if (a[YMAX - 1][i] == TARGET)
			ans = i;
	}
	if (ans == input)
	{
		printf("\7");
		score++;
		return true;
	}
	else
		return false;
}
