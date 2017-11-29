#pragma once

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Errors.hpp"
#include "Lexer.hpp"
#include "Ident.hpp"
#include "Functions.hpp"

#include <cmath>
#include <sstream>
#include <algorithm>

class Interpreter {
public:
	explicit Interpreter(vector<string> Code);
	inline void __cdecl GenerateCode() { Scanner.GenerateCode(); }
	~Interpreter() {}

	inline vector<Ident> __cdecl CompileArglist(Token Arglist);
	inline unsigned int __cdecl CompileFunctionDecl(Token Arglist);
	inline Ident __cdecl ExecuteBuiltin(Ident Command, vector<Ident> Stack);
	inline Ident __cdecl ExecuteFunction(Ident Command);
	inline void __cdecl RunCode(vector<Token> Code);

	inline string __cdecl Vector2String(Token Vector);

	inline double __cdecl CompileNumber(Token Number);
	inline Ident __cdecl CompileLookup(Token Lookup);
	inline string __cdecl CompileString(Token String);
	inline vector<string> __cdecl CompileVector(Token Vector);
	inline Ident __cdecl CompileBody(vector<Token> Body);
	inline Ident __cdecl CompileSwitchStatement(Token Object);
	inline void __cdecl CompileCaseSequence(Ident Id, vector<Token> Block);
	inline void __cdecl CompileLoopSequence(Ident Iter, unsigned int Count, vector<Token> Block);
	inline void __cdecl CompileEnumeration(vector<Ident> Args, vector<Token> Block);

private:
	Ident LastReturn;
	Lexer Scanner;
	Token CurrentToken;

};

inline bool __cdecl IsSpace(char Character) {
	return (Character == ' ' || Character == '\t'
		|| Character == '\r' || Character == '\n');
}

inline bool __cdecl IsSmallLetter(char Letter) {
	switch (Letter) {
	case 'a': case 'b': case 'c': case 'd': case 'e':
	case 'f': case 'g': case 'h': case 'i': case 'j':
	case 'k': case 'l': case 'm': case 'n': case 'o':
	case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y':
	case 'z': 
		return true;
	}
	return false;
}

inline string __cdecl Number2String(double Number) {
	stringstream Stream;
	Stream << Number;
	return string(Stream.str());
}

#endif
