#pragma once

#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <iostream>
#include <cmath>
#include "Token.hpp"
using namespace std;

class Ident;
static vector<Ident> Idents;

class IdentValue {
public:
	IdentValue() : Number(0.0), String("") {}
	explicit IdentValue(double Number) : Number(Number), String("") {}
	explicit IdentValue(string String) : Number(0.0), String(String) {}
	explicit IdentValue(vector<string> Vector) : Number(0.0), String(""), Vector(Vector) {}
	explicit IdentValue(vector<Token> Function) : Number(0.0), String(""), Function(Function) {}

	inline double __cdecl GetNumber() const { return Number; }
	inline string __cdecl GetString() const { return String; }
	inline vector<string> __cdecl GetVector() const { return Vector; }

	inline void __cdecl SetNumber(double Value) { Number = Value; }
	inline void __cdecl SetString(string Value) { String = Value; }
	inline void __cdecl SetVector(vector<string> Value) { Vector = Value; }
	inline void __cdecl SetFunction(vector<Token> Value) { Function = Value; }

private:
	double Number;
	string String;
	vector<string> Vector;
	vector<Token> Function;

};

class Ident {
public:
	Ident();
	explicit Ident(string Name, IdentValue Val, bool Macro = false);
	explicit Ident(string Name, double Number, bool Macro = false);
	explicit Ident(string Name, string String, bool Macro = false);
	explicit Ident(string Name, void *Builtin, bool Macro = false);
	explicit Ident(string Name, vector<string> Vector, bool Macro = false);
	explicit Ident(string Name, vector<Token> Function, bool Macro = false);
	explicit Ident(string Name, unsigned int Count, vector<Token> Body, bool Macro = false);

	inline string GetName() const { return Name; }
	inline unsigned int GetType() const { return Type; }
	inline unsigned int GetCount() const { return Count; }
	inline IdentValue *GetValue() const { return Val; }

	inline vector<Token> __cdecl GetBody() const { return Body; }

	inline Ident __cdecl Builtin(vector<Ident> Stack) {
		Ident(*Func)(vector<Ident>);
		Func = (Ident(*)(vector<Ident>))Cmd;
		return Func(Stack); /* run builtin-function */
	}

	inline void __cdecl SetName(string Value) { Name = Value; }
	inline void __cdecl SetType(unsigned int Value) { Type = Value; }
	inline void __cdecl SetBody(vector<Token> Value) { Body = Value; }

	inline void __cdecl SetNumber(double Value) { Type = ID_NUMBER; Val->SetNumber(Value); }
	inline void __cdecl SetString(string Value) { Type = ID_STRING; Val->SetString(Value); }
	inline void __cdecl SetVector(vector<string> Value) { Type = ID_VECTOR; Val->SetVector(Value); }
	inline void __cdecl SetStack(vector<Ident> Value) { Stack = Value; }
	inline void __cdecl SetCount(unsigned int Value) { Count = Value; }

private:
	string Name;
	unsigned int Type;
	unsigned int Count;
	IdentValue *Val;
	vector<Token> Body;
	vector<Ident> Stack;
	void *Cmd;
	bool Macro;

};

static inline Ident __cdecl ConstructIdent(unsigned int Type, string Name, vector<Token> Body) {
	Ident NewId;
	NewId.SetType(Type);
	NewId.SetName(Name);
	NewId.SetBody(Body);
	return NewId;
}

#define ADDBUILTIN(Name, Count, Function) { \
	Ident Command(Name, Function); \
	Command.SetCount(Count); \
	Idents.push_back(Command); \
}

#define ADDMACRO(Name, Value) { \
	Ident Macro(Name, Value, true); \
	Idents.push_back(Macro); \
}

#define ADDFUNCTION(Name, Count, Body) { \
	Ident Function(Name, Count, Body); \
	Idents.push_back(Function); \
}

inline bool __cdecl IdentExists(string Name) {
	for (Ident Id : Idents)
		if (Name == Id.GetName())
			return true;
	return false;
}

inline bool __cdecl InternIdentExists(string Name, vector<Ident> Stack) {
	for (Ident Id : Stack)
		if (Name == Id.GetName())
			return true;
	return false;
}

inline bool __cdecl BuiltinExists(string Name) {
	for (Ident Id : Idents)
		if (Name == Id.GetName()
			&& Id.GetType() == ID_BUILTIN)
			return true;
	return false;
}

inline bool __cdecl FunctionExists(string Name) {
	for (Ident Id : Idents)
		if (Name == Id.GetName()
			&& Id.GetType() == ID_FUNCTION)
			return true;
	return false;
}

inline Ident __cdecl GetIdent(string Name) {
	for (Ident Id : Idents)
		if (Name == Id.GetName()) 
			return Id;
	return Ident("Res", 0.0);
}

inline Ident __cdecl GetInternIdent(string Name, vector<Ident> Stack) {
	for (Ident Id : Stack)
		if (Name == Id.GetName())
			return Id;
	return Ident("Res", 0.0);
}

inline unsigned int __cdecl FindIdent(string Name) {
	unsigned int Res = 0;
	for (Ident Id : Idents) {
		if (Id.GetName() == Name
			&& Id.GetType() != ID_BUILTIN
			&& Id.GetType() != ID_MACRO) {
			return Res;
		}
		++Res;
	}
	return Res;
}

inline bool __cdecl	CompareIdents(Ident Left, Ident Right) {
	unsigned int Type = Left.GetType();
	switch (Type) {
	case ID_NUMBER: return (Left.GetValue()->GetNumber() == Right.GetValue()->GetNumber());
	case ID_STRING: return (Left.GetValue()->GetString() == Right.GetValue()->GetString());
	case ID_VECTOR: return (Left.GetValue()->GetVector() == Right.GetValue()->GetVector());
	default: return false;
	}
	return false;
}

inline double __cdecl GetIdentAsNumber(Ident Id) {
	double Res = 0.0;
	switch (Id.GetType()) {
	case ID_NUMBER: Res = Id.GetValue()->GetNumber(); break;
	case ID_STRING: Res = (double)Id.GetValue()->GetString().length(); break;
	case ID_VECTOR: Res = (double)Id.GetValue()->GetVector().size(); break;
	default: break;
	}
	return Res;
}

#endif
