#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
long int gcd(long int a, long int b)
{
	if(b==0) return a;
	else return gcd(b, a%b);
}
int prime(long int num) //kiem tra so nguyen to
{
    int i;
    for (i = 2; i*i <= num; ++i)
        if (num%i == 0)
            return 0;
    return 1;
}
long int mod(long int base, long int expo, long int num) //base^expo (mod num)
{
    long int res = 1;
    long int i;
    for (i = 1; i <= expo; i++)
        res = (res*base)%num;
    return res;
}
void extended_gcd(long int a, long int b, long int *x, long int *y)//ax + by = gcd(a,b)
{
	//ax + by = gcd(a, b)
	//gcd(a, b) = gcd(b%a, a)
	//gcd(b%a, a) = (b%a)x1 + ay1
	//ax + by = (b%a)x1 + ay1
	//ax + by = (b – [b/a] * a)x1 + ay1
	//ax + by = a(y1 – [b/a] * x1) + bx1

	//x = y1 – ?b/a? * x1
 	//y = x1
 	
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
	long int p,q,EulerN,N,encryt,decryt,code,m,cache,M;
	srand(time(NULL));
	
    test1:
        printf("\n(Bi mat) Gia tri p và q: ");
        scanf("%ld %ld", &p, &q);
    if (!prime(p) || !prime(q)) 
	{
        printf("\np, q khong phai nguyen to... Vui long nhap lai...");
        goto test1;
    }
    
    N=p*q;
    EulerN=(p-1)*(q-1);
    printf("\n(Cong khai) Gia tri n = p*q = %ld",N);
    printf("\n(Bi mat) Gia tri Euler(n) = (p-1)*(q-1) = %ld",EulerN);
    printf("\n(Van Ban bi mat) Doan ma bi mat : ");
    scanf("%ld", &m);
    
    test2:
    printf("\n(Cong khai) Khoa encryt: ");
    scanf("%ld", &encryt);
    if(gcd(encryt, EulerN)!=1 || encryt>=EulerN || encryt<=1)
    {
    	printf("\nEncryt khong hop le... Vui long nhap lai...");
        goto test2;
	}
	
	decryt=ReverseMod2(encryt,EulerN);//decryt*encryt = 1 (mod EulerN)
	
	code = mod(m,encryt,N);//code = m^encryt (mod N)
	M = mod(code,decryt,N);//m = code^decryt (mod N)
	printf("\n(Cong khai) Gia tri code: %ld (=%ld^%ld (mod %ld))\n",code,m,encryt,N);
	
	
	printf("\n(Bi mat) Khoa decryt: %ld (decryt*encryt = 1 (mod EulerN))",decryt);
	
	printf("\n(Giai ma) Doan ma bi mat = %ld^%ld (mod %d) = %ld",code,decryt,N,M);
	printf("");scanf("%ld",&p);
	return 0;
}


