# Quine Loop

Problem Statement:

Write four different programs with the following properties:<br />
	- Running the first program prints the complete source code of the second program.<br />
	- Running the second program prints the complete source code of the third program.<br />
	- Running the third program prints the complete source code of the fourth program.<br />
	- Running the fourth program prints the complete source code of the first program.<br />
	- None of the programs perform any kind of file reading.<br />

In other words, make a collection of four different programs, each of which prints the 
complete source of the next one in the sequence, wrapping back around at the end.

## Solution
My solution to this problem comes in the form of four C++ programs `one.cpp`, `two.cpp`, `three.cpp`, and `four.cpp`. These programs differ only in the comment on the first line, and in the vector of program lines.

## Usage
To generate `two.cpp`, `three.cpp`, and `four.cpp` given only `one.cpp` run:<br />
`$ make` <br />
on the command line. To test that indeed these programs meet the requirements of the problem run:<br />
`$ ./test.sh`
