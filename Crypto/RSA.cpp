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

// Binary Search Algorithm 
// Used on sorted vectors of integers
int binary_search(vector<int> &sorted, int query, int start, int end)
{
	//println("start: " + to_string(start) + ", end: "+ to_string(end));
	if(start == end)
	{
		if(sorted[start] == query)
			return start;
		else
			return -1;
	}
	else
	{
		int median = start + (end - start) / 2;
		//println("Median: " + to_string(sorted[median]) + ", query: " + to_string(query));
		if (sorted[median] > query)
			return binary_search(sorted, query, start, median);
		else if (sorted[median] < query)
			return binary_search(sorted, query, median + 1, end);
		else
			return median;

	}
}

// Checks to see if a n integer is within a vector of sorted integers
bool isin(vector<int> &sorted, int query)
{
	return binary_search(sorted, query, 0, sorted.size()) != -1;
	
}

// Returns a random integer between min (inclusive) and max (exclusive)
int random_integer(int min, int max)
{
	// Random number generator from min (inclusive) to max (exclusive)
	return rand() % (max - min) + min;
}

// Returns a random odd integer between min (inclusive) and max (exclusive)
int random_odd(int min, int max)
{
	int low = (min - 1) / 2;
	int high = (max - 1) / 2;
	return 2 * random_integer(low, high) + 1;
}

// Integer Exponentiation
int ipow(int base, int power)
{
	int result = 1;
	while (power)
	{
		if (power & 1)
			result *= base;
		power >>= 1;
		base *= base;
	}
	return result;
}

// Modular Exponentiation
// returns (base ^ power) % modulus
long long mod_pow(long long base, long long power, long long modulus)
{
	long long c = 1;
	while (power > 0)
	{
		if (power % 2 == 1)
			c = (c * base) % modulus;
		base = (base * base) % modulus;
		power = power >> 1;
	}
    return c;
}

// Fermat Primality Test
// False if candidate is definitely composite, True if candidate is probably prime
bool fermat_primality(int candidate, int k=70)
{
	for(int i = 0; i < k; i++)
	{
		int a = random_integer(2, candidate - 2);
		if(mod_pow(a, candidate - 1, candidate) != 1)
			return false;
	}
	return true;
}

// Miller-Rabin Primality Test
// False if candidate is definitely composite, True if candidate is probably prime
bool miller_rabin(int candidate, int k=70)
{
	if (candidate <= 7)
	{
		bool low_results [8] = {false, false, true, true, false, true, false, true};
		return low_results[candidate];
	}

	if (candidate % 2 == 0)
		return false;

	// Candidate = d * 2^s + 1
    int s = 0;
    int d = candidate - 1;
    // Factor 2 out of n - 1 until d is odd
    while (d % 2 == 0)
    {
    	d /= 2;
        s++;
    }

    // Check k number of times
    for(int i=0; i < k; i++)
    {
    	int a = random_integer(2, candidate - 2);
        int x = mod_pow(a, d, candidate);
        if (x == 1 || x + 1 == candidate)
            continue;

        for (int r = 1; i < s; r++)
        {
        	x = mod_pow(x, 2, candidate);
            if (x == 1)
                return false;
            if (x == candidate - 1)
                continue;
        }
        return false;
    }
    return true;
}

// Returns a list of all primes below a given integer
vector<int> primes_below(int number)
{
	vector<int> primes;
	primes.push_back(2);
	for(int n = 3; n < number; n += 2)
	{
		bool is_prime = true;
		for(int i=0; i < primes.size(); i++)
		{
			if(0 == n % primes[i])
			{
				is_prime = false;
				break;
			}
		}

		if(is_prime)
		{
			primes.push_back(n);
		}
	}
    return primes;
}

// Returns a number that is probably prime between high and low
int probably_prime(int low, int high)
{
	vector<int> low_primes = primes_below(1000);
	bool found = false;
	int candidate = low;
	while(!found)
	{
		candidate = random_odd(low, high);
		if (isin(low_primes, candidate))
		{
			found = true;
			break;
		}

		bool div_by_prime = false;
		for (int i=0; i < low_primes.size(); i++)
		{
			if (candidate % low_primes[i] == 0)
			{
				div_by_prime = true;
				break;
			}
		}
		if (div_by_prime)
		{
			continue;
		}

		if (fermat_primality(candidate) && miller_rabin(candidate))
		{
			found = true;
		}
		else
		{
			candidate += 2;
			if (candidate >= high)
			{
				if (low & 2)
					candidate = low;
				else
					candidate = low + 1;
			}
		}
		
	}
	return candidate;
}

// Tests the primality of a number exhaustively
// Not used for RSA key-generation but interesting and useful in debugging
bool is_prime(int number)
{
	if (number % 2 == 0)
	{
		return false;
	}
	else
	{
		for(int n=3; n <= sqrt(number); n+=2)
		{
			if (number % n == 0)
			{
				return false;
			}
		}
		return true;
	}
}

// This is a subroutine of the Extended Eudlidian Algorithm
void euclidian_step(int* r[], int q)
{
	int next = (*r)[0] - (*r)[1] * q;
    (*r)[0] = (*r)[1];
    (*r)[1] = next;
}

// Extended Euclidian Algorithm
// Solves as + bt = gcd(a,b) for s,t given a,b
int* extended_euclidian_algorithm(int a, int b)
{
	int* r = new int[2];
	r[0] = a;
	r[1] = b;

	int* s = new int[2];
	s[0] = 1;
	s[1] = 0;

	int* t = new int[2];
	t[0] = 0;
	t[1] = 1;

	while (r[1] != 0)
	{
		int q = r[0] / r[1];
		euclidian_step(&r, q);
        euclidian_step(&s, q);
        euclidian_step(&t, q);
	}

	int* result = new int[2];
	result[0] = s[0];
	result[1] = t[0];
	
	delete [] r;
	delete [] s;
	delete [] t;

	return result;
}

// Modular Multiplicitave Inverse
// Returns d such that d*e = 1 (mod z)
// Method: rearranging the above: de - 1 = qz, thus de - qz = 1
int modular_multiplicitave_inverse(int e, int z)
{
	int* dq = extended_euclidian_algorithm(e, z);
    return dq[0];
}

// Euler's Toitent Function, phi(n) = (p-1)(q-1), if n = p * q
// Counts the positive integers less than or equal to n that are relatively prime to n
int toitent_function(int p, int q)
{
	return (p - 1) * (q - 1);
}

// Returns a public key, private key, and modulus for
// the RSA cryptosystem defined by p and q, which are two primes
int* get_keys(int p, int q)
{
	int n = p * q;
    int z = toitent_function(p, q);
    int e = 1;
    int d = e;
    while (d == e)
    {
    	e = probably_prime(7, z);
    	d = modular_multiplicitave_inverse(e, z);
    	if (d < 0)
    	{
    		d += z;
    	}
    }
    int* keys = new int[3];
    keys[0] = e;
    keys[1] = d;
    keys[2] = n;
    return keys;
}


// This function generates a new set of RSA keys
int* new_keyset(int high=10000000)
{
	int p = probably_prime(5, high);
	int q = p;
	while(q == p)
	{
		q = probably_prime(5, high);
	}
	println("Primes: " + to_string(p) + ", " + to_string(q));
	int* keys = get_keys(p, q);
	return keys;
}

// This function encrypts or decrypts a message x using
// public or p
int crypt(int x, int key, int modulus)
{
	return mod_pow(x, key, modulus);
}

int main(int argc, char* argv[])
{
	srand(time(0));

	int upper_bound = atoi(argv[1]);

	println("Generating Keys...");
	int* keys = new_keyset(upper_bound);
	int public_key = keys[0];
	int private_key = keys[1];
	int modulus = keys[2];

	println("Public:  " + to_string(public_key));
	println("Private: " + to_string(private_key));
	println("Modulus: " + to_string(modulus));

	int message = random_integer(1, upper_bound); 
	println("Message: " + to_string(message));

	int encrypted = crypt(message, public_key, modulus);
	println("Encrypted: " + to_string(encrypted));

	int decrypted = crypt(encrypted, private_key, modulus);
	println("Decrypted: " + to_string(decrypted));

	if (message == decrypted && message != encrypted)
		println("Encryption successful.");
	else
		println("Encryption failure.");

	return 0;
}