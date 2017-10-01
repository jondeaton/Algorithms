#include <iostream>
#include <vector>
using namespace std;
vector<string> program = {
	R"(#include <iostream>)",
	R"(#include <vector>)",
	R"(using namespace std;)",
	R"(vector<string> program = {)",
	R"(@)",
	R"(};)",
	R"(int main() {)",
	R"(	for(string line : program))",
	R"(		if (line == "@") for(string l : program) cout << "\tR\"(" + l + ")\"," << endl;)",
	R"(		else cout << line << endl;)",
	R"(	return 0;)",
	R"(})",
};
int main() {
	for(string line : program)
		if (line == "@") for(string l : program) cout << "\tR\"(" + l + ")\"," << endl;
		else cout << line << endl;
	return 0;
}
