#pragma once

#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include <time.h>
#include "Ident.hpp"

inline Ident __cdecl SCRIPT_EQUAL(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = 0.0;
	return Ident("Res", (double)(CompareIdents(Stack[0], Stack[1]) ? 1.0 : 0.0));
}

inline Ident __cdecl SCRIPT_NOTEQUAL(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = 0.0;
	return Ident("Res", (double)(!CompareIdents(Stack[0], Stack[1]) ? 1.0 : 0.0));
}

inline Ident __cdecl SCRIPT_AND(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = 1.0;
	for (Ident Id : Stack) {
		switch (Id.GetType()) {
		case ID_NUMBER: if (Id.GetValue()->GetNumber() == 0.0) { Res = 0.0; } break;
		case ID_STRING: if (Id.GetValue()->GetString() == "") { Res = 0.0; } break;
		case ID_VECTOR: if (!Id.GetValue()->GetVector().size()) { Res = 0.0; } break;
		default: Res = 0.0; break;
		}
	}
	return Ident("Res", Res);
}

inline Ident __cdecl SCRIPT_OR(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = 0.0;
	for (Ident Id : Stack)
		if (GetIdentAsNumber(Id))
			Res = 1.0;
	return Ident("Res", Res);
}

inline Ident __cdecl SCRIPT_NOT(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (double)!(GetIdentAsNumber(Stack[0])));
}

inline Ident __cdecl SCRIPT_GREATER(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Val1 = GetIdentAsNumber(Stack[0]); 
	double Val2 = GetIdentAsNumber(Stack[1]);
	return Ident("Res", (double)(Val1 > Val2));
}

inline Ident __cdecl SCRIPT_LESS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Val1 = GetIdentAsNumber(Stack[0]);
	double Val2 = GetIdentAsNumber(Stack[1]);
	return Ident("Res", (double)(Val1 < Val2));
}

inline Ident __cdecl SCRIPT_GREATEREQUAL(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Val1 = GetIdentAsNumber(Stack[0]);
	double Val2 = GetIdentAsNumber(Stack[1]);
	return Ident("Res", (double)(Val1 >= Val2));
}

inline Ident __cdecl SCRIPT_LESSEQUAL(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Val1 = GetIdentAsNumber(Stack[0]);
	double Val2 = GetIdentAsNumber(Stack[1]);
	return Ident("Res", (double)(Val1 <= Val2));
}

#endif