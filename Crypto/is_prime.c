#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int is_prime(int number)
{
	if (!(number % 2))
	{
		if (number == 2)
			return 1;
		else
			return 0;
	}
	else
	{
		for (int k = 3; k <= sqrt(number); k += 2)
		{
			if (!(number % k))
				return 0;
		}
	}
	if (number <= 1)
		return 0;
	else
		return 1;
}

int main(int argc, char* argv[])
{
	int number = atoi(argv[1]);
	printf("%d: ", number);
	if (is_prime(number))
		printf("True\n");
	else
		printf("False\n");

}