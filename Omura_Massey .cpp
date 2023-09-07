#include <stdio.h>
#include <stdlib.h>
long int mod(int base, int expo, int num) // base^expo (mod num)
{
    int res = 1;
    int i;
    for (i = 1; i <= expo; ++i)
        res = (res*base)%num;
    return res;
}
int prime(long int num) //kiem tra so nguyen to
{
    int i;
    for (i = 2; i*i <= num; ++i)
        if (num%i == 0)
            return 0;
    return 1;
}
long int gcd(long int a, long int b)
{
	if(b==0) return a;
	else return gcd(b, a%b);
}
long int ReverseMod1(long int a, long int M)	//a.b = 1 (mod M)
{
	long int b;
	loop:
		if((a*b-1)%M!=0)
		{
			b++;
			goto loop;
		}
	return b;
}
void extended_gcd(long int a, long int b, long int *x, long int *y)//ax + by = gcd(a,b)
{
    // Base case
    if (a == 0) 
	{
        *x = 0;
        *y = 1;
    }
    else
    {
    	// Recursive case
    	long int x1, y1;
    	extended_gcd(b%a, a, &x1, &y1);
    	
		//ax + by = gcd(a, b)
		//gcd(a, b) = gcd(b%a, a)
		//gcd(b%a, a) = (b%a)x1 + ay1
		//ax + by = (b%a)x1 + ay1
		//ax + by = (b – [b/a] * a)x1 + ay1
		//ax + by = a(y1 – [b/a] * x1) + bx1
	
		//x = y1 – (b/a) * x1
	 	//y = x1
    	// Update x and y using results of recursive call
    	*x = y1 - (b/a) * x1;
    	*y = x1;
	}
}
long int ReverseMod2(long int a, long int M)	//a.b = 1 (mod M)
{
	if(gcd(a,M)==1 && a<M)
	{
		long int b,cache;
		extended_gcd(a,M,&b,&cache);// a.b + M.cache = 1
		if(b<0)
			b=b+M;
		return b;
	}
	else return 0;
}
int main()
{
	long int p,a,M,m,M1,M2,M3;
	long int m1, m2, n1, n2;
    
    test1:
        printf("\n(Cong khai) Gia tri p = ");
        scanf("%ld", &p);
    if (!prime(p)) 
	{
        printf("\np không phai nguyên to... Vui lòng nhap lai...");
        goto test1;
    }
    
    printf("(Bi mat) Van ban M = ");scanf("%ld", &M);
    printf("Alice su dung khoa bi mat m1,m2\nBob su dung khoa bi mat n1,n2\n");
    test2:
	    printf("\n(Bi mat) Nhap m1 = ");scanf("%ld", &m1);
	    printf("(Bi mat) Nhap n1 = ");scanf("%ld", &n1);
	    if(gcd(m1,p-1)!=1 || gcd(n1,p-1)!=1)
	    	goto test2;
    m2 = ReverseMod2(m1,p-1);
    n2 = ReverseMod2(n1,p-1);
    printf("(Bi mat)=>\tm2 = %ld\n\t\tn2 = %ld\n\n",m2,n2);
    
    M1=mod(M,m1,p);//M1 = M^m1 (mod p)
    printf("(Cong khai) Alice ma hoa M thanh M1 gui cho Bob: M1 = M^m1 (mod p) = %ld^%ld (mod %ld) = %ld\n",M,m1,p,M1);
    M2=mod(M1,n1,p);//M2 = M1^n1 (mod p)
    printf("(Cong khai) Bob ma hoa M1 thanh M12 gui cho Alice: M2 = M1^n1 (mod p) = %ld^%ld (mod %ld) = %ld\n",M1,n1,p,M2);
    M3=mod(M2,m2,p);//M3 = M2^m2 (mod p)
    printf("(Cong khai) Alice ma hoa M2 thanh M3 gui cho Bob: M3 = M2^m2 (mod p) = %ld^%ld (mod %ld) = %ld\n",M2,m2,p,M3);
    m=mod(M3,n2,p);//M = M3^n2 (mod p)
    printf("(Giai ma) Bob giai ma M3 thanh M: M = M3^n2 (mod p) = %ld^%ld (mod %ld) = %ld\n",M3,n2,p,m);
    
    printf("");scanf("%ld",&p);
	return 0;
}


