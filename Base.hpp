#pragma once

#ifndef BASE_HPP
#define BASE_HPP

#include <time.h>
#include <sstream>
#include "Ident.hpp"

inline Ident __cdecl SCRIPT_PUSH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	string Name = Stack[0].GetValue()->GetString();
	Ident V = Stack[1]; Ident Var; Var.SetName(Name);
	if (!IdentExists(Name)) {
		switch (V.GetType()) {
		case ID_NUMBER: Var.SetNumber(V.GetValue()->GetNumber()); break;
		case ID_STRING: Var.SetString(V.GetValue()->GetString()); break;
		case ID_VECTOR: Var.SetVector(V.GetValue()->GetVector()); break;
		default: break;
		}
		Idents.push_back(Var);
	} else { cout << "Error: Redefinition of Identifier \"" << Name << "\" is impossible." << endl; }
	return Var;
}

inline Ident __cdecl SCRIPT_RETURN(vector<Ident> Stack) {
	if (!Stack.size()) { return (Ident("RET", 0.0)); }
	return Stack[0];
}

inline Ident __cdecl SCRIPT_SET(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	string Name = "";
	if (!IdentExists(Name = Stack[0].GetValue()->GetString())) {
		cout << "Error: Identifier \"" << Name << "\" doesn't exist." << endl;
		return Ident("Res", 0.0);
	}
	switch (Stack[1].GetType()) {
	case ID_NUMBER: GetIdent(Stack[0].GetValue()->GetString()).SetNumber(Stack[1].GetValue()->GetNumber()); break;
	case ID_STRING: GetIdent(Stack[0].GetValue()->GetString()).SetString(Stack[1].GetValue()->GetString()); break;
	case ID_VECTOR: GetIdent(Stack[0].GetValue()->GetString()).SetVector(Stack[1].GetValue()->GetVector()); break;
	default: break;
	}
	return GetIdent(Name);
}

inline Ident __cdecl SCRIPT_POP(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	string Name = "";
	for (Ident Id : Stack) {
		if (!IdentExists(Name = Id.GetValue()->GetString())) {
			cout << "Error: Identifier \"" << Name << "\" doesn't exist." << endl;
			return Ident("Res", 0.0);
		}
		Idents.erase(Idents.begin() + FindIdent(Name));
	}
	return Ident("Res", 0.0);
}

inline Ident __cdecl SCRIPT_INPUT(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", ""); }
	string Name = Stack[0].GetValue()->GetString();
	string InputStr = ""; getline(cin, InputStr);
	GetIdent(Name).SetString(InputStr);
	return GetIdent(Name);
}

inline Ident __cdecl SCRIPT_OUTPUT(vector<Ident> Stack) {
	for (Ident Id : Stack) {
		switch (Id.GetType()) {
		case ID_NUMBER: cout << Id.GetValue()->GetNumber(); break;
		case ID_STRING: cout << Id.GetValue()->GetString(); break;
		case ID_VECTOR:
			for (string Str : Id.GetValue()->GetVector()) {
				cout << Str << " ";
			} cout << endl; break;
		default: break;
		}
	}
	return Ident("Res", 0.0);
}

inline Ident __cdecl SCRIPT_STR2NUM(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", ""); }
	return Ident("Res", atof(Stack[0].GetValue()->GetString().c_str()));
}

inline Ident __cdecl SCRIPT_NUM2STR(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", ""); }
	stringstream Number;
	Number << Stack[0].GetValue()->GetNumber();
	return Ident("Res", Number.str());
}


#endif