#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define WIDTH 8
#define HEIGHT 8
int WHITE,BLACK,white,black;
int turn,level;
int cells[HEIGHT+2][WIDTH+2][10],plus[HEIGHT+1][WIDTH+1];
int cursorX,cursorY;
void set_color ( int code ) 
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}
int Check(int m, int n, int turn, int p, int q, int d)
{
	int Point=0,i=1;
	if(cells[m][n][d]==0)
	{
		while(m+i*p <= HEIGHT+1 && n+i*q <=WIDTH+1 && m+i*p >= 0 && n+i*q >= 0)
		{
			if(cells[m+i*p][n+i*q][d]!=-turn)
			{
				if(cells[m+i*p][n+i*q][d]==0){Point=0;}
				break;
			}
			else{Point++;i++;}
		}
		return(Point);	
	}
	else{return(0);}
}
int Test(int m, int n, int turn, int d)
{
	int Test;
	Test=Check(m,n,turn,1,0,d)+Check(m,n,turn,0,1,d)+Check(m,n,turn,1,1,d)+Check(m,n,turn,1,-1,d);
	Test=Test+Check(m,n,turn,-1,0,d)+Check(m,n,turn,0,-1,d)+Check(m,n,turn,-1,-1,d)+Check(m,n,turn,-1,1,d);
	return(Test);
}
int TestMove(int C, int turn, int d)
{
	int m,n;
	if(C%WIDTH!=0){n=C%WIDTH;m=C/WIDTH+1;}
	else{n=WIDTH;m=C/WIDTH;}
	return(Test(m,n,turn,d));
}
void Set(int m, int n, int turn, int p, int q, int d)
{
	int i=1,j,z,x,y;
	while(m+i*p <= HEIGHT+1 && n+i*q <=WIDTH+1 && m+i*p >= 0 && n+i*q >= 0)	
	{
		if(cells[m+i*p][n+i*q][d]==-turn){i++;}
		else
		{
			if(cells[m+i*p][n+i*q][d]==turn)
	        {
		        for(j=i;j>=1;j--){cells[m+j*p][n+j*q][d]=turn;}
	        }
		    break;
		}
	}
}
void Othello(int m, int n, int turn, int d)
{
	cells[m][n][d]=turn;
	Set(m,n,turn,1,0,d);Set(m,n,turn,-1,0,d);
	Set(m,n,turn,0,1,d);Set(m,n,turn,0,-1,d);	
	Set(m,n,turn,1,1,d);Set(m,n,turn,-1,-1,d);
	Set(m,n,turn,1,-1,d);Set(m,n,turn,-1,1,d);
}
int SumPoint(int w, int d)
{
	int i,j,P=0;
	for(i=1;i<=HEIGHT;i++)
	{
		for(j=1;j<=WIDTH;j++)
		{
			if(cells[i][j][d]==w){P++;}
		}
	}
	return(P);
}
void ListPlus(int turn)
{
	int i,j,z,x,y;
	for(y=1;y<=HEIGHT;y++)
	{
		for(x=1;x<=WIDTH;x++)
		{
			if(Test(y,x,turn,0)>0){plus[y][x]=1;}
			else{plus[y][x]=0;}
		}
	}
	white=SumPoint(1,0);black=SumPoint(-1,0);
}
void Table()
{
	int i,j,z,x,y;
	system("cls");
	system("color 2E");
	printf("\t--GAME OTHELLO--\n\n");
	set_color(0x2F);printf("WHITE = %d\t\t",white);
	set_color(0x20);printf("BLACK = %d\n",black);
	for(z=1;z<=WIDTH;z++){set_color(0x28);printf("+---");}
	printf("+\n");
	for(y=1;y<=HEIGHT;y++)
	{
		for(x=1;x<=WIDTH;x++)
		{
			set_color(0x28);printf("|");
			if(x==cursorX && y==cursorY)
			{	
			    if(turn==1){set_color(0x2F);printf("[");}
				else{set_color(0x20);printf("[");}
				switch(cells[y][x][0])
				{
					case 1: set_color(0x2F);printf("0");break;
					case -1: set_color(0x20);printf("0");break;
					case 0:
						{
							set_color(0x2A);
							if(plus[y][x]==1){printf("+");}
					        else{printf(" ");};
					        break;
						}
				}
				if(turn==1){set_color(0x2F);printf("]");}
				else{set_color(0x20);printf("]");}
			}
			else
			{
				switch(cells[y][x][0])
				{
					case 1: set_color(0x2F);printf(" 0 ");break;
					case -1: set_color(0x20);printf(" 0 ");break;
					case 0:
						{
							set_color(0x2A);
							if(plus[y][x]==1){printf(" + ");}
						    else{printf("   ");};
							break;
						}
				}
			}
		}
		set_color(0x28);
		printf("|\n");
		for(z=1;z<=WIDTH;z++){printf("+---");}
		printf("+\n");
	}
}
void Start()
{
	int i,j,z,x,y;
	cells[4][4][0]=1;cells[5][5][0]=1;
	cells[4][5][0]=-1;cells[5][4][0]=-1;
	WHITE=1;BLACK=1;white=2;black=2;
	turn=1;level=1;cursorX=0;cursorY=0;
	srand((int)time(NULL));
	while(1)
	{
		int GO=0;
		Table();
		set_color(0x2E);printf("Choose level:\t");
	    for(i=1;i<=4;i++)
	    {
	    	set_color(0x2F);
		    if(level==i){printf("[%d]\t",i);}else{printf(" %d \t",i);}
	    }
		switch(getch())
		{
			case 13: GO=1;break;
			default:
				switch(getch())
				{
					case 75: if(level>1){level--;};break;
			        case 77: if(level<4){level++;};break;
				}
		}
		if(GO==1){break;}
	}
	cursorX=4;cursorY=3;
	ListPlus(1);
}
void Create(int m, int n)
{
	int i,j,z,x,y;
	for(i=1;i<=HEIGHT;i++)
	{
		for(j=1;j<=WIDTH;j++)
		{
			cells[i][j][n]=cells[i][j][m];
		}
	}
}
int CheckMove(int turn, int d)
{
	int i,j,z,x,y;
	for(y=1;y<=HEIGHT;y++)
	{
		for(x=1;x<=WIDTH;x++)
		{
			if(Test(y,x,turn,d)>0){return(1);}
		}
	}
	return(0);
}
void Move(int C, int turn, int m, int n)
{
	int Y,X;
	Create(m,n);
	if(C%WIDTH!=0){X=C%WIDTH;Y=C/WIDTH+1;}
	else{X=WIDTH;Y=C/WIDTH;}
	Othello(Y,X,turn,n);
}
void Player()
{
	while(1)
	{
		int GO=0;
		Table();set_color(0x2E);printf("LEVEL = %d\n",level);
		set_color(0x2F);printf("Turn of WHITE: Use UP, DOWN, LEFT, RIGHT then ENTER");
		switch(getch())
		{
			case 13: 
			    if(plus[cursorY][cursorX]==1)
				{
				    Othello(cursorY,cursorX,1,0);
				    GO=1;
				}
			    break;
			default:
				switch(getch())
				{
					case 72: if(cursorY>1){cursorY--;};break;
			        case 80: if(cursorY<HEIGHT){cursorY++;};break;
			        case 75: if(cursorX>1){cursorX--;};break;
			        case 77: if(cursorX<WIDTH){cursorX++;};break;
				}
		}
		if(GO==1){break;}
	}
}
int Think(int deep, int SPIN)
{
	int Ce[11],MARK[11],mark[11],spin[11];
	spin[deep]=SPIN;
	if(CheckMove(spin[deep],deep+1)==0)
	{
	    spin[deep]=-spin[deep];
	    if(CheckMove(spin[deep],deep+1)==0)
	    {
		    if(SumPoint(-1,deep+1)<SumPoint(1,deep+1)){return(0);}
		    else
		    {
			    if(SumPoint(-1,deep+1)==SumPoint(1,deep+1)){return(99);}
			    else{return(100);}
		    }
	    }
	}
	MARK[deep]=100*spin[deep];
	for(Ce[deep]=1;Ce[deep]<=HEIGHT*WIDTH;Ce[deep]++)
	{
		if(TestMove(Ce[deep],spin[deep],deep+1)>0)
		{
			Move(Ce[deep],spin[deep],deep+1,deep);
			if(deep==1){mark[1]=SumPoint(-1,1);}
			else{mark[deep]=Think(deep-1,-spin[deep]);}
			if(mark[deep]*spin[deep]<MARK[deep]*spin[deep]){MARK[deep]=mark[deep];}
		}
	}
	return(MARK[deep]);
}
int Brain(int deep)
{
	int Cell,Choose[HEIGHT*WIDTH+1],S[HEIGHT*WIDTH+1],s[HEIGHT*WIDTH+1],k=0,MAX=0,Max=0;
	for(Cell=1;Cell<=HEIGHT*WIDTH;Cell++)
	{
		s[Cell]=TestMove(Cell,-1,0);
		if(s[Cell]>0)
		{
			Move(Cell,-1,0,level+1);
			S[Cell]=Think(level,1);
			if(S[Cell]>Max){Max=S[Cell];}
		}
		else{S[Cell]=0;}
	}
	for(Cell=1;Cell<=HEIGHT*WIDTH;Cell++)
	{
		if(S[Cell]==Max){if(s[Cell]>MAX){MAX=s[Cell];}}
	}
	for(Cell=1;Cell<=HEIGHT*WIDTH;Cell++)
	{
		if(S[Cell]==Max && s[Cell]==MAX){k++;Choose[k]=Cell;}
	}
	k=(rand()%k)+1;
	return(Choose[k]);
}
void Computer()
{
	int Computer;
	set_color(0x2E);printf("LEVEL = %d\n",level);
	set_color(0x20);printf("Turn of BLACK: Computer is thinking ...");
	Sleep(500);
	Computer=Brain(level);
	if(Computer%WIDTH!=0){cursorX=Computer%WIDTH;cursorY=Computer/WIDTH+1;}
	else{cursorX=WIDTH;cursorY=Computer/WIDTH;}
	Table();set_color(0x2E);printf("LEVEL = %d\n",level);
	set_color(0x20);printf("Turn of BLACK: Computer is thinking ...");Sleep(700);
	Othello(cursorY,cursorX,-1,0);
}
void Game(int turn)
{
	if(turn==1)
	{
		Table();
		if(CheckMove(1,0)==1){Player();WHITE=1;}
		else{set_color(0x2C);printf("Turn of WHITE: [...]");WHITE=0;Sleep(3000);}
	}
	else
	{
		Table();
		if(CheckMove(-1,0)==1){Computer();BLACK=1;}
		else{set_color(0x2C);printf("Turn of BLACK: [...]");BLACK=0;Sleep(3000);}
	}
	ListPlus(-turn);
}
void Final()
{
	Table();set_color(0x2E);printf("LEVEL = %d\n",level);
	if(SumPoint(1,0)>SumPoint(-1,0)){set_color(0x2F);printf("=> WHITE win\n");}
	else
	{
		if(SumPoint(1,0)<SumPoint(-1,0)){set_color(0x20);printf("=> BLACK win\n");}
		else{set_color(0x2E);printf("=> WHITE draw BLACK\n");}
	}
	set_color(0x2E);
	system("pause");
}
int main()
{
	Start();
	while(1)
	{
		Game(turn);
		if(white+black==HEIGHT*WIDTH || white*black==0 || WHITE+BLACK==0){break;}
		turn=-turn;
	}
	Final();
	return(0);
}
