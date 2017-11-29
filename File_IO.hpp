#pragma once

#ifndef FILE_IO
#define FILE_IO 

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

extern const vector<string> __cdecl ReadFile(const char *FileName);
extern void __cdecl WriteLine(const char *FileName, string Line);

extern void __cdecl CreateFile(const char *FileName);
extern void __cdecl ClearFile(const char *FileName);
extern void __cdecl DeleteFile(const char *FileName);

extern const unsigned int __cdecl FileLength(const char *FileName);

extern bool __cdecl FileEmpty(ifstream &File);
extern bool __cdecl FileExists(ifstream &File);

#endif	

