#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<windows.h>
const int Col=8, High=8;
int A[High+1][Col+1],B[Col+1],p,w,c,cursor;
void Start()
{
	p=0;w=0;
	for(c=1;c<=Col;c++){B[c]=High+1;}
	srand((int)time(NULL));
	c=(rand()%2);
	if(c==1)
	{
		srand((int)time(NULL));
	    c=(rand()%Col)+1;
	    B[c]=B[c]-1;A[B[c]][c]=-1;p++;
	}
}
void set_color ( int code ) 
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}
void Table()
{
	int i,j;
	system("cls");
	set_color( 0x0E );
	printf("GAME CONNECT FOUR (PHONGS)\n");
	for(i=0;i<=High+1;i++)
	{
		if(i==High+1){printf("\n");}
		for(j=1;j<=Col;j++)
		{
			if(i==0){if(j==cursor){set_color( 0x0E );printf(" 0   ");}else{printf("     ",j);}}
			else
			{
				if(i==High+1)
			    {if(j==c){set_color( 0x0C );printf("[%d]  ",j);}else{set_color( 0x09 );printf("[%d]  ",j);}}
			    else
			    {
				    switch (A[i][j])
				    {
			            case 1: set_color( 0x0E );printf(" 0   ");break;
					    case -1: set_color( 0x0C );printf(" 0   ");break;
					    case 0: set_color( 0x07 );printf(" -   ");break;
					    case 2: set_color( 0x0E );printf("[0]  ");break;
					    case -2: set_color( 0x0C );printf("[0]  ");break;
				    }
			    }
			}
		}
		printf("\n\n");
	}
}
void Move(int c, int w)
{
	if(B[c]>1){B[c]=B[c]-1;A[B[c]][c]=w;}
}
void DelMove(int c)
{
	if(B[c]<=High){A[B[c]][c]=0;B[c]=B[c]+1;}
}
int MAX(int u, int v)
{
	if(u>v){return(u);}
	else{return(v);}
}
int MIN(int u, int v)
{
	if(u<v){return(u);}
	else{return(v);}
}
int Check(int m, int n, int P, int Q)
{
	int p=3,q=0,i,j,u=n,v=n;
	j=1;
	for(i=1;i<=3;i++)
	{
	   	if(m+i*P <= High && n+i*Q <= Col && m+i*P >= 1 && n+i*Q >= 1)
	   	{
	   	  	if(A[m][n]*A[m+i*P][n+i*Q]<0){break;}
	   	  	else
		    { 
	   	  		if(A[m][n]*A[m+i*P][n+i*Q]==0){p=p+j;u=n+i*Q;j=0;}
				if(A[m][n]*A[m+i*P][n+i*Q]>0){p=p+3*j;u=n+i*Q;}
			}
		}
		else{break;}
	}
	j=1;
	for(i=1;i<=3;i++)
	{
	   	if(m-i*P <= High && n-i*Q <= Col && m-i*P >= 1 && n-i*Q >= 1)
	   	{
	   	  	if(A[m][n]*A[m-i*P][n-i*Q]<0){break;}
	   	  	else
		    { 
	   	  		if(A[m][n]*A[m-i*P][n-i*Q]==0){q=q+j;v=n-i*Q;j=0;}
				if(A[m][n]*A[m-i*P][n-i*Q]>0){q=q+3*j;v=n-i*Q;}
			}
		}
		else{break;}
	}
	if((Q==0 && m==1 && p+q<12) || (Q!=0 && abs(u-v)<3)){return(0);}
	else{return(p+q);}
}
int Test(int m, int n)
{
	int T;
	T=MAX(MAX(Check(m,n,1,0),Check(m,n,0,1)),MAX(Check(m,n,1,1),Check(m,n,1,-1)));
    return(T);
}
int THINK(int w, int n)
{
	if(n==1)
	{
		int i,j,E,e=100,u;
	    for(i=1;i<=Col;i++)
	    {
		    E=0;
		    if(B[i]==1){continue;}
		    Move(i,w);
		    if(Test(B[i],i)>=12){e=-13;DelMove(i);break;}
		    for(j=1;j<=Col;j++)
		    {
			    if(B[j]==1){continue;}
		        Move(j,-w);
		        u=Test(B[j],j);
		        if(u>=12 || u>e){E=13;DelMove(j);break;}
			    E=MAX(u,E);
			    DelMove(j);
		    }
		    DelMove(i);
		    e=MIN(e,E);
	    }
	    return(e);
	}
	else
	{
		int i,j,E,e=100,u;
	    for(i=1;i<=Col;i++)
	    {
		    E=0;
		    if(B[i]==1){continue;}
		    Move(i,w);
		    if(Test(B[i],i)>=12){e=-13*n;DelMove(i);break;}
		    for(j=1;j<=Col;j++)
		    {
			    if(B[j]==1){continue;}
		        Move(j,-w);
		        if(Test(B[j],j)>=12){E=13*n;DelMove(j);break;}
		        u=THINK(w,n-1)+Test(B[j],j);
		        if(u>e || u-Test(B[j],j)==13*(n-1)){E=13*n;DelMove(j);break;}
			    E=MAX(u,E);
			    DelMove(j);
		    }
		    DelMove(i);
		    e=MIN(e,E);
	    }
	    return(e);
	}
}
int BRAIN()
{
	int n=4,i,j,E[Col+1],e=100,y=-100,Y[Col+1],k=0,S[Col+1],u=-100;
	for(i=1;i<=Col;i++)
	{
		E[i]=0;
		if(B[i]==1){E[i]=100;continue;}
		Move(i,-1);
		if(Test(B[i],i)>=12){E[i]=-13*n;DelMove(i);e=-13*n;break;}
		for(j=1;j<=Col;j++)
	    {
			if(B[j]==1){continue;}
		    Move(j,1);
		    if(Test(B[j],j)>=12){E[i]=13*n;DelMove(j);break;}
		    u=THINK(-1,n-1)+Test(B[j],j);
		    if(u>e || u-Test(B[j],j)==13*(n-1)){E[i]=13*n;DelMove(j);break;}
			E[i]=MAX(u,E[i]);
			DelMove(j);
		}
		DelMove(i);
		e=MIN(e,E[i]);
	}
	for(i=1;i<=Col;i++)
	{
		if(E[i]==e)
		{
			Move(i,-1);
			if(Test(B[i],i)>=12){Y[i]=13*n;y=13*n;}
			else
			{
				Y[i]=THINK(1,n-1)+Test(B[i],i);
				y=MAX(y,Y[i]);
			}
			DelMove(i);
		}
		else{Y[i]=-100;}
	}
	for(i=1;i<=Col;i++)
	{
		if(E[i]<=e && Y[i]>=y){k++;S[k]=i;}
	}
	srand((int)time(NULL));
	i=(rand()%k)+1;
	return(S[i]);
}
void Player()
{
	int v=0;
	if(p>0){cursor=c;}else{cursor=Col/2;}
	while(v==0)
	{
		Table();
		set_color( 0x0E );printf("(Player) Use LEFT or RIGHT then DOWN");
		getch();
		switch(getch())
		{
			case 75: if(cursor>1){cursor--;};break;
			case 77: if(cursor<Col){cursor++;};break;
			case 80: if(B[cursor]>1){B[cursor]=B[cursor]-1;A[B[cursor]][cursor]=1;v=1;};break;
		}
	}
	if(Test(B[cursor],cursor)>=12){w=1;A[B[cursor]][cursor]=2;}
	cursor=0;c=0;p++;
}
void Computer()
{
	Table();
	set_color( 0x0C );printf("(COMPUTER) [-_-] is thinking....");
	c=BRAIN();
	B[c]=B[c]-1;
	A[B[c]][c]=-1;
	if(Test(B[c],c)>=12){w=-1;A[B[c]][c]=-2;};
	p++;
}
void Final()
{
	Table();
	if(w==1){set_color( 0x0F );printf("=> Winner is ");set_color( 0x0E );printf("Player");}
	else
	{
	    if(w==-1){set_color( 0x0F );printf("=> Winner is ");set_color( 0x0C );printf("COMPUTER ");}
	    else
		{
		    set_color( 0x0F );printf("=> ");
			set_color( 0x0E );printf("Player ");
			set_color( 0x0F );printf("draw ");
			set_color( 0x0C );printf("COMPUTER ");
		}
	}
	set_color( 0x0F );
	printf("!!!\n");
	system("pause");
}
int main()
{
	Start();
	while(1)
	{
		Player();if(w==1 || p==Col*High){break;};
		Computer();if(w==-1 || p==Col*High){break;};
	}
	Final();
	return(0);
}
