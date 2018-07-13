/*2048*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 4

//int board[SIZE][SIZE]={0};
//int board2[SIZE][SIZE]={0};

void initial(int board[SIZE][SIZE]);				//初始化游戏 
void PrintHelp();									//打印帮助 
void Printboard(int board[SIZE][SIZE]);				//打印游戏面板 
int Victory(int board[SIZE][SIZE]);					//游戏面板里有2048
int Gameover(int board[SIZE][SIZE]); 				//->无法继续移动(上下左右都不行)，游戏结束
   
int MoveUp(int board[SIZE][SIZE]);					//
int MoveLeft(int board[SIZE][SIZE]);				// 
int MoveRight(int board[SIZE][SIZE]);				//
int MoveDown(int board[SIZE][SIZE]);				//
void addnumber(int board[SIZE][SIZE]);				//->产生随机数

int main()
{
	printf("Welcome to 2048~     \n");
	int board[SIZE][SIZE]={0};
	initial(board);		//初始化游戏板 
	PrintHelp();
	Printboard(board);
	while( Victory(board)==0 && Gameover(board)==0 ) //2048了 或者 继续不了gameover跳出循环 Victory()==0 && Gameover()==0
	{
		char c;
		scanf("%c",&c);
		if( c == 'q' )
		{
			exit(0);
		}
		else if( c == 'w' )
		{
			MoveUp(board);
			PrintHelp();
			Printboard(board);
		}
		else if( c == 'a' )
		{
			MoveLeft(board);
			PrintHelp();
			Printboard(board);
		}
		else if( c == 'd' )
		{
			MoveRight(board);
			PrintHelp();
			Printboard(board);
		}
		else if( c == 's' )
		{
			MoveDown(board);
			PrintHelp();
			Printboard(board);
		}
		/*
		if( Victory()==1)
			break;
		//board2[SIZE][SIZE]=board[SIZE][SIZE];
		if( Gameover()==1 )
			break;
		*/
	}
	
	if( Victory(board) == 1)
	{
		printf("2048~You win the Game!!!\n");
		exit(0);
	}
	else if( Gameover(board)==1 )
	{
		printf("Sorry~You lose the game...\n");
		exit(0);
	}
	return 0;
}






void initial(int board[SIZE][SIZE])
{
	board[1][2]=board[2][1]=2;
}



void PrintHelp()
{
	printf("Enter w to moveup, a to moveleft, d to moveright, s to movedown Or q to quit the game\n");
}



void Printboard(int board[SIZE][SIZE])
{
	int i,j;
	printf(" - - - - - - - - - - - - - - - \n");
	for( i=0 ; i<SIZE ; i++)
	{
		printf("| ");
		for( j=0 ; j<SIZE ; j++)
		{
			if( board[i][j]==0 )
				printf("%6c",'.');
			else
				printf("%6d",board[i][j]);
		}
		printf("     |\n\n");
	}
	printf(" - - - - - - - - - - - - - - - \n");
}



int Victory(int board[SIZE][SIZE])
{
	int i,j;
	for( i=0 ; i<SIZE ; i++)
	{
		for( j=0 ; j<SIZE ; j++)
		{
			if( board[i][j]==2048 ) return 1;
		}
	}
	return 0;
}



int Gameover(int board[SIZE][SIZE])
{ 
	int copyboard[SIZE][SIZE];
	for(int i=0;i<SIZE;i++)  
    {  
        for(int j=0;j<SIZE;j++)  
        {  
            copyboard[i][j]=board[i][j];  
        }  
    }  
	if( MoveRight(copyboard)==0 && MoveLeft(copyboard)==0 && MoveUp(copyboard)==0 && MoveDown(copyboard)==0 )
		return 1;
	else
		return 0;
}



int MoveLeft(int board[SIZE][SIZE])
{
	int i,j,movable=-1;
	for( i=0 ; i<SIZE ; i++ )
	{
		for( j=0 ; j<SIZE ; j++ )
		{
			if( board[i][j]!=0 )
			{
				int k = j+1;
				while( k<SIZE	)
				{
					if( board[i][k]!=0 )
					{
						if( board[i][j]==board[i][k])
						{
							movable=0;
							board[i][j]*=2;
							board[i][k]=0;
						}
						k=SIZE;
						break;
					}
					k++;
				}
			}
		}
	}
	
	for( i=0 ; i<SIZE ; i++ )
	{
		for( j=0 ; j<SIZE-1 ; j++ )
		{
			if( board[i][j]==0 )
			{
				int k=j+1;
				while( k<SIZE )
				{
					if( board[i][k]!=0 )
					{
						movable=0;//可以移动
						board[i][j]=board[i][k];
						board[i][k]=0;
						k=SIZE;
					}
					k++;
				}
			}
		}
	}
	if( movable==0)
	{
		addnumber(board);
		return 1;
	}
	else 
		return 0;
				
}



int MoveRight(int board[SIZE][SIZE])
{
	int i,j,movable=-1;
	for( i=0 ; i<SIZE ; i++)
	{
		for( j=SIZE-1; j>=0; j--)
		{
			if( board[i][j]!=0)
			{
				int k=j-1;
				while(k>=0)
				{
					if( board[i][k]!=0)
					{
						if(board[i][k]==board[i][j])
						{
							movable=0;
							board[i][j]*=2;
							board[i][k]=0;
						}
						k=-1;
						break;
					}
					k--;
				}
			}
		}
	}
	
	for( i=0 ; i<SIZE ; i++)
	{
		for( j=SIZE-1 ; j>0 ; j--)
		{
			if( board[i][j]==0)
			{
				int k=j-1;
				while( k>=0 )
				{
					if( board[i][k]!=0)
					{
						movable=0;
						board[i][j]=board[i][k];
						board[i][k]=0;
						k=-1;
					}
					k--;
				}
			}
		}
	}
	if( movable==0 )
	{
		addnumber(board);
		return 1;
	}
	else
		return 0;
}



int MoveDown(int board[SIZE][SIZE])
{
	int i,j,movable=-1;
	for( i=SIZE-1; i>=0 ; i--)
	{
		for( j=0 ; j<SIZE ; j++)
		{
			if( board[i][j]!=0 )
			{
				int k=i-1;
				while( k>=0 )
				{
					if( board[k][j]!=0 )
					{
						if(board[i][j]==board[k][j])
						{
							movable=0;
							board[i][j]*=2;
							board[k][j]=0;
						}
						k=0;
						break;
					}
					k--;
				}
			}
		}
	}
	
	for( i=SIZE-1 ; i>0 ; i--)
	{
		for( j=0 ; j<SIZE ; j++)
		{
			if( board[i][j]==0)
			{
				int k=i-1;
				while( k>=0 )
				{
					if( board[k][j]!=0)
					{
						movable=0;
						board[i][j]=board[k][j];
						board[k][j]=0;
						k=0;
					}
					k--;
				}
			}
		}
	}
	if( movable==0)
	{
		addnumber(board);
		return 1;
	}
	else
		return 0;
}



int MoveUp(int board[SIZE][SIZE])
{
	int i,j,movable=-1;
	for( i=0 ; i<SIZE ; i++)
	{
		for( j=0 ; j<SIZE ; j++)
		{
			if( board[i][j]!=0)
			{
				int k=i+1;
				while( k<SIZE )
				{
					if( board[k][j]!=0)
					{
						if( board[k][j]==board[i][j] )
						{
							movable=0;
							board[i][j]*=2;
							board[k][j]=0;
						}
						k=SIZE;
						break;
					}
					k++;
				}
			}
		}
	}
	
	for( i=0 ; i<SIZE ; i++)
	{
		for( j=0 ;j<SIZE ; j++)
		{
			if( board[i][j]==0)
			{
				int k=i+1;
				while( k<SIZE )
				{
					if( board[k][j]!=0)
					{
						movable=0;
						board[i][j]=board[k][j];
						board[k][j]=0;
						k=SIZE;
					}
					k++;
				}
			}
		}
	}
	if( movable==0)
	{
		addnumber(board);
		return 1;
	}
	else
		return 0;
	
}



void addnumber(int board[SIZE][SIZE])
{
	srand((unsigned)time(0));
	int i,j;
	while(1)
	{
		i = rand() % 4;	//0-3
		j = rand() % 4;
		if( board[i][j]==0 )
		{
			board[i][j] = ( rand()%10 ? 2 : 4 );
			break;
		}
	}
}



	
