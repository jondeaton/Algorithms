//1
#include <iostream>
#include <vector>
using namespace std;
vector<string> program = {
	R"(//1)",
	R"(#include <iostream>)",
	R"(#include <vector>)",
	R"(using namespace std;)",
	R"(vector<string> program = {)",
	R"(@)",
	R"(};)",
	R"(int main() {)",
	R"(	for(string line : program) {)",
	R"(		if (line == "@") {)",
	R"(			for (string l : program) {)",
	R"(				if (l == "//1") cout << "\tR\"(//2)\"," << endl;)",
	R"(				else if (l == "//2") cout << "\tR\"(//3)\"," << endl;)",
	R"(				else if (l == "//3") cout << "\tR\"(//4)\"," << endl;)",
	R"(				else if (l == "//4") cout << "\tR\"(//1)\"," << endl;)",
	R"(				else cout << "\tR\"(" + l + ")\"," << endl;)",
	R"(			} )",
	R"(		})",
	R"(		else if (line == "//1") cout << "//2" << endl;)",
	R"(		else if (line == "//2") cout << "//3" << endl;)",
	R"(		else if (line == "//3") cout << "//4" << endl;)",
	R"(		else if (line == "//4") cout << "//1" << endl;)",
	R"(		else cout << line << endl;)",
	R"(	})",
	R"(	return 0;)",
	R"(})",
};
int main() {
	for(string line : program) {
		if (line == "@") {
			for (string l : program) {
				if (l == "//1") cout << "\tR\"(//2)\"," << endl;
				else if (l == "//2") cout << "\tR\"(//3)\"," << endl;
				else if (l == "//3") cout << "\tR\"(//4)\"," << endl;
				else if (l == "//4") cout << "\tR\"(//1)\"," << endl;
				else cout << "\tR\"(" + l + ")\"," << endl;
			} 
		}
		else if (line == "//1") cout << "//2" << endl;
		else if (line == "//2") cout << "//3" << endl;
		else if (line == "//3") cout << "//4" << endl;
		else if (line == "//4") cout << "//1" << endl;
		else cout << line << endl;
	}
	return 0;
}
