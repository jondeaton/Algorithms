#Greatest Common Divisor
#Uses Stein's Algorithm

def gcd(a,b):
        
	#Simple Cases
	if a == 0 or b == 0:
		return [a,b][b == 0]
	
	if a == b:
		return b
	
	#Both Even
	if a%2 == 0 and b%2 == 0:
		return 2*gcd(a/2,b/2)
	
	#One is Odd
	if (a%2 == 1)^(b%2 == 1):
		return gcd([a,b][b%2 == 0]/2,[a,b][b%2 != 0])
	else: #Both are Odd
		return gcd(abs(b-a)/2,[a,b][b<a])
