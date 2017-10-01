# Original Quine
if [[ $(./quine | diff quine.cpp -) ]]; then
	echo "Quine Failure"
	./quine | diff quine.cpp -
else
	echo "Quine Success"
fi

# One
if [[ $(./one | diff two.cpp -) ]]; then
	echo "One Failure:"
	./one | diff two.cpp -
else
	echo "One Success"
fi

# Two
if [[ $(./two | diff three.cpp -) ]]; then
	echo "Two Failure:"
	./two | diff three.cpp -
else
	echo "Two Success"
fi

# Three
if [[ $(./three | diff four.cpp -) ]]; then
	echo "Three Failure:"
	./three | diff four.cpp -
else
	echo "Three Success"
fi

# Four
if [[ $(./four | diff one.cpp -) ]]; then
	echo "Four Failure:"
	./four | diff one.cpp -
else
	echo "Four Success"
fi
