/* v2 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// #include <conio.h>
#include <conio4linux.h>

int score=0, board[4][4]={0};


void putBoard()
{
	//'clc' for windows, 'clear' for linux
	if (system("cls") != 0) system("clear");
	printf("\n2048  by正逍遥0716\ngithub.com/zhengxiaoyao0716\n当前分数%8d\n", score);
	printf("\n____________________________\n");
	int x, y;
	for (x=0; x<=3; x++)
	{
		for (y=0; y<=3; y++)
		{
			if (board[x][y]) printf("|%d\t",board[x][y]);
			else printf("|\t");
		}
		printf("\n____________________________\n");
	}
} 


void change(char action)
{
	int x, y;
	switch (action)
	{
		case 'w':
		case '2': break;
		case 'a':
		case '4':
		{
			for (x=0; x<=2; x++)
			{
				for (y=x+1; y<=3; y++)
				{
					board[x][y]+=board[y][x];
					board[y][x]=board[x][y]-board[y][x];
					board[x][y]-=board[y][x];
				}
			}
			break;
		}
		case 'd':
		case '6':
		{
			for (x=0; x<=2; x++)
			{
				for (y=0; y<=2-x; y++)
				{
					board[x][y]+=board[3-y][3-x];
					board[3-y][3-x]=board[x][y]-board[3-y][3-x];
					board[x][y]-=board[3-y][3-x];
				}
			}
			break;
		}
		case 's':
		case '8':
		{
			for (x=0; x<=1; x++)
			{
				for (y=0; y<=3; y++)
				{
					board[x][y]+=board[3-x][y];
					board[3-x][y]=board[x][y]-board[3-x][y];
					board[x][y]-=board[3-x][y];
				}
			}
			break;
		}
		default: exit(0);
	}
}


void merge()
{
	int x, y, i;
	for (y=0; y<=3; y++)
	{
		i=0;
		int temp[5]={0};
		for (x=0; x<=3; x++)
		{
			if (board[x][y])
			{
				temp[i]=board[x][y];
				board[x][y]=0;
				i++;
			}
		}
		x=0;
		for (i=0; i<=3; i++)
		{
			if (temp[i]==temp[i+1])
			{
				temp[i]+=temp[i+1];
				score+=temp[i];
				temp[i+1]=0;
			}
			if (temp[i])
			{
				board[x][y]=temp[i];
				x++;
			}
		}
	}
}


int giveNew()
{
	int x, y, i=0, *temp[16];
	for (x=0; x<=3; x++ )
	{
		for (y=0; y<=3; y++)
		{
			if (!board[x][y])
			{
				temp[i]=&board[x][y];
				i++;
			}
		}
	}
	if (!i) return 0;
	else
	{
		i=rand()%i;
		*temp[i]=(rand()%2+1)*2;
		return 1;
	}
}


int gameOver()
{
	int x;
	for (x=0; x<=3; x++)
	{
		if ((board[x][0]==board[x][1])||(board[x][1]==board[x][2])||(board[x][2]==board[x][3]))
		{
			return 0;
		}
	}
	return 1;
}


int main()
{
	int aim=1024;
	srand(time(NULL));
	giveNew();
	putBoard();
	char action;
	while (1)
	{
		action=getch();
		change(action);
		merge();
		if (!giveNew())
		{
			if (gameOver())
			{
				printf("游戏结束，请按下任意键退出\n");
				getch();
				return (score-aim>=0);
			}
		}
		change(action);
		putBoard();
	}
}