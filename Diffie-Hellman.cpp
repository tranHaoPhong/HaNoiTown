#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int prime(int num) 
{
    int i;
    for (i = 2; i*i <= num; ++i)
        if (num % i == 0)
            return 0;
    return 1;
}

int mod(int base, int expo, int num) 
{
    int res = 1;
    int i;
    for (i = 1; i <= expo; ++i)
        res = (res * base) % num;
    return res;
}

int main() 
{
    int p, g, a, b, i, j, r1, r2, k1, k2, k3;
    srand(time(NULL));
    p:
        printf("\n(Cong khai) Gia tri p và g: ");
        scanf("%d %d", &p, &g);
    if (!prime(p) || !prime(g)) 
	{
        printf("\nCác giá tri nhap không phai nguyên to... Vui lòng nhap lai...");
        goto p;
    } 
	else 
	{
        srand(time(NULL));
        a = rand() % 50;
        b = rand() % 50;
        printf("\(Bi mat) Alice chon keyA la %d; Bob chon keyB la %d", a, b);
        r1 = mod(g, a, p); // g^a mod p
        r2 = mod(g, b, p); // g^b mod p
        printf("\n(Cong khai) Alice gui %d^%d(mod %d)= %d\n(Cong khai) Bob gui %d^%d(mod %d)= %d\n", g,a,p,r1, g,b,p,r2);
        k1 = mod(r2, a, p); // r2^a mod p
        k2 = mod(r1, b, p); // r1^b mod p
        
        printf("\nKhoa bi mat chung tinh duoc boi Alice: %d^%d(mod %d)=%d", r2,a,p,k1);
        printf("\nKhoa bi mat chung tinh duoc boi Bob:  %d^%d(mod %d)=%d", r1,b,p,k2);
        //k3 = mod(g, a * b, p); // g^a*b mod p
        //printf("\n//Kiem tra Khoa bi mat chung: %d", k3); // phai giong k1 và k2
    }
    printf("");scanf("%ld",&p);
	return 0;
}

