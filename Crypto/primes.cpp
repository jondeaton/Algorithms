#include <vector.h>
#include <iostream.h>
#include <math.h>

int pi_upper_bound(int n)
{
	return int(1.25506 * n / log(n));
}

void fill_primes(int upper_bound, int* primes)
{
	
}

int main(int argc, char* argv[])
{
	int upper_bound = atoi(argv[1]);
	int primes[pi_upper_bound(upper_bound)];
	fill_primes(upper_bound, &primes);
	for(int i=0; i < upper_bound; i++)
	{
		printf("%d, ", primes[i]);
	}
}