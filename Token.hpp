#pragma once

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <vector>
#include <string>

#include "Code.hpp"

using namespace std;

class Token {
public:
	Token() : Type(TOKEN_UNKNOWN), NumberVal(0.0), StringVal("") {}
	explicit Token(const unsigned int Type) 
		: Type(Type), NumberVal(0.0), StringVal("") {}
	explicit Token(const unsigned int Type, const double Number) 
		: Type(Type), NumberVal(Number), StringVal("") {}
	explicit Token(const unsigned int Type, const string String) 
		: Type(Type), StringVal(String), NumberVal(0.0) {}
	explicit Token(const unsigned int Type, vector<Token> Vector) 
		: Type(Type), VectorVal(Vector), NumberVal(0.0), StringVal("") {}
	explicit Token(const unsigned int Type, string Name, vector<Token> Stack)
		: Type(Type), StringVal(Name), VectorVal(Stack), NumberVal(0.0) {}
	explicit Token(const unsigned int Type, string Name, vector<Token> Args, vector<Token> Body)
		: Type(Type), StringVal(Name), NumberVal(0.0), VectorVal(Args), VectorVal2(Body) {}
	~Token() {}

	const unsigned int __cdecl GetType() const { return Type; }
	double __cdecl GetNumberValue() const { return NumberVal; }
	string __cdecl GetStringValue() const { return StringVal; }
	vector<Token> __cdecl GetVectorValue() const { return VectorVal; }
	vector<Token> __cdecl GetVectorValue2() const { return VectorVal2; }

	bool __cdecl Compare(const unsigned int Ty) { return (Type == Ty); }

private:
	unsigned int Type;
	double NumberVal;
	string StringVal;
	vector<Token> VectorVal;
	vector<Token> VectorVal2;
};

#endif