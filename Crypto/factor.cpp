#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
// compile with: g++ -std=c++11

void print(string input)
{
	cout << input;
}

void println(string input)
{
	print(input + "\n");
}

// This is a naive algorithm for integer factorization
vector<unsigned long long> factor_naive(unsigned long long N)
{
	vector<unsigned long long> factors;
	unsigned long long stop = 1 + N / 2;
	for (unsigned long long n = 2; n <= stop; n++)
	{
		while(N % n == 0)
		{
			factors.push_back(n);
			N /= n;
		}
	}
	if (factors.size() == 0)
	{
		factors.push_back(N);
	}

	return factors;
}

// This function checks a factorizaton of an integer
bool check_factorization(unsigned long long number, vector<unsigned long long> &factors)
{
	int product = 1;
	for(int i = 0; i < factors.size(); i ++)
	{
		product *= factors[i];
	}
	cout << "product: " << product << endl;
	return (product == number);
}

// This function prints all items in a list
void print_vector(vector<unsigned long long> &list_of_things)
{
	cout << list_of_things[0];
	for (int i = 1; i < list_of_things.size(); i++)
	{
		cout << ", " << list_of_things[i];
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	unsigned long long n = atoi(argv[1]);
	vector<unsigned long long> factors = factor_naive(n);
	print_vector(factors);
	
	if (check_factorization(n, factors))
		println("Verified");
	else
		println("Failure.");


	return 0;
}