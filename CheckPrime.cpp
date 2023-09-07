#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
bool CheckPrime(int numberCheck)
	{
		if(numberCheck <= 1 || numberCheck == 4 || numberCheck == 6)
			return false;
		else if(numberCheck < 7)
			return true;
		else
		{
			if(numberCheck%6 != 1 && numberCheck%6 != 5)
				return false;
			int LimCheck = sqrt(numberCheck);
			if(numberCheck % LimCheck == 0)
				return false;
			else
			{
				int check1 = 5, check2 = 7;
				while(1)
				{
					if(check1 <= LimCheck)
						if(numberCheck % check1 == 0)
							return false;
						else
							check1 = check1 + 6;
					else
						return true;
						
					if(check2 <= LimCheck)
						if(numberCheck % check2 == 0)
							return false;
						else
							check2 = check2 + 6;
					else
						return true;
				}
			}
		}
	}
int main()
{
	int numberCheck = 123;
	bool KQ = CheckPrime(numberCheck);
	if (KQ == true)
		printf("%d la So nguyen to",numberCheck);
	else
		printf("%d Khong phai so nguyen to",numberCheck);
	return 0;
}


