#include "File_IO.hpp"


const vector<string> __cdecl ReadFile(const char *FileName) {
	vector<string> Answer;
	string CurrentLine;
	ifstream SourceCode(FileName, 1);
	if (!FileExists(SourceCode)) {
		cout << "Warning: File \"" << FileName << "\" doesn't exist." << endl;
		return Answer;
	}
	if (FileEmpty(SourceCode)) {
		cout << "Warning: File \"" << FileName << "\" is empty." << endl;
		return Answer;
	}
	while (!SourceCode.eof()) {
		getline(SourceCode, CurrentLine);
		Answer.push_back(CurrentLine);
	}
	return Answer;
}

void __cdecl WriteLine(const char *FileName, string Line) {

}

void __cdecl CreateFile(const char *FileName) {

}

void __cdecl ClearFile(const char *FileName) {

}

void __cdecl DeleteFile(const char *FileName) {

}

bool __cdecl FileEmpty(ifstream &File) {
	return (File.peek() == std::ifstream::traits_type::eof());
}

bool __cdecl FileExists(ifstream &File) {
	return (!File.fail());
}