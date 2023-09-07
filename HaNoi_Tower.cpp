#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define MAXDISK 8
int Col[MAXDISK+1][3];
int Mark[3];
int put,cursor;
void set_color ( int code )
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}
void Start()
{
	for(int i=1;i<=MAXDISK;i++)
	{
		Col[i][0]=MAXDISK+1-i;
		Col[i][1]=0;
		Col[i][2]=0;
	}
	Col[0][0]=MAXDISK+1;Mark[0]=MAXDISK;
	Col[0][1]=MAXDISK+1;Mark[1]=0;
	Col[0][2]=MAXDISK+1;Mark[2]=0;
	put=0;cursor=0;
}
void Dislay()
{
	system("cls");
	set_color(0x07);
	printf("Game HaNoiTower(Number Version)\n");
	printf("(+)Press <- or -> to move\n");
	printf("(+)Press ENTER to pick up/put down Number\n");
	printf("(+)Press SPACE to watch AI play\n\n");
	set_color(0x01);
	for(int i=0;i<=2;i++)
	{
		printf("\t");
		if(i==cursor)
		{
			printf("[");
			if(put!=0){printf("%d",put);}
			else{printf(" ");}
			printf("]");
		}
		else{printf("   ");}
	}
	printf("\n");
	for(int j=MAXDISK;j>=1;j--)
	{
		set_color(0x0E);
		if(Col[j][0]>0){printf("\t %d ",Col[j][0]);}
		else{printf("\t   ");}
		if(Col[j][1]>0){printf("\t %d ",Col[j][1]);}
		else{printf("\t   ");}
		if(Col[j][2]>0){printf("\t %d \n",Col[j][2]);}
		else{printf("\t   \n");}
	}
	set_color(0x0C);
	printf("\t[A]\t[B]\t[C]");
}
void MOVE(int m, int n)
{
	if(Mark[m]>0 && Col[Mark[m]][m]<Col[Mark[n]][n])
	{
		cursor=m;Dislay();Sleep(300);
		put=Col[Mark[m]][m];
		Col[Mark[m]][m]=0;Mark[m]--;Dislay();Sleep(300);
		cursor=n;Dislay();Sleep(300);
		Mark[n]++;Col[Mark[n]][n]=put;put=0;Dislay();Sleep(300);
	}
}
void Solution(int n, int Source, int Dest, int Aux)
{
	if(n==0){return;}
	Solution(n-1,Source,Aux,Dest);
	MOVE(Source,Dest);
	Solution(n-1,Aux,Dest,Source);
}
void Play()
{
	switch(getch())
	{
		case 13:
			{
				if(put!=0)
		        {
			        if(put<Col[Mark[cursor]][cursor])
			        {
				        Mark[cursor]++;
				        Col[Mark[cursor]][cursor]=put;
				        put=0;
			        }
		        }
		        else
		        {
			        if(Mark[cursor]>0)
			        {
				        put=Col[Mark[cursor]][cursor];
				        Col[Mark[cursor]][cursor]=0;
				        Mark[cursor]--;
			        }
		        }
		        break;
			}
		case 32:
			{
				Start();Dislay();
				Solution(MAXDISK,0,2,1);
				set_color(0x07);printf("\n");
				system("pause");
				Start();
				break;
			}
		default:
			{
				switch(getch())
			    {
				    case 75:if(cursor>0){cursor--;}break;
				    case 77:if(cursor<2){cursor++;}break;
			    }
			    break;
			}	
	}
}
int main()
{
	Start();
	while(1)
	{
		Dislay();
		Play();
	}
	return 0;
}
