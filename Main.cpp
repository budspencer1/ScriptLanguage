#include "Interpreter.hpp"
#include "Ident.hpp"

int main(int argc, char **argv) {
	string End = "";
	vector<string> Code = ReadFile("Test2.sap");
	if (Code.size()) {
		Interpreter *Inter = new Interpreter(Code);
		delete Inter; Inter = nullptr;
		Idents.clear(); Code.clear();
	}
	cin >> End;
	return 0;
}