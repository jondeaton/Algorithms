

def isPalindrome(ll):
	return isPali(ll, ll)[0]


def isPali(reverse, forward):

	if (reverse.next is None):
		return (reverse.value == forward.value, forward.next)

	match, fwd = isPali(reverse.next, forward)

	if not match:
		return (False, None)
	else:
		return (reverse.value == fwd.value, fwd.next)