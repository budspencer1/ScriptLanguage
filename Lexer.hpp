#pragma once

#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include "File_IO.hpp"
#include "Pair.hpp"

class Lexer {
public:
	explicit Lexer(const vector<string> Code);
	~Lexer() {}

	char __cdecl GetCurrentChar() { return CurrentChar; }
	inline void __cdecl GenerateCode();
	inline void __cdecl GenerateLine();

	inline Token __cdecl GetNextToken(bool Peek = false);
	inline vector<Token> __cdecl GetGeneratedCode() const { return GeneratedCode; }

	static Token Start;
	static Token End;
	static Token EOL;

private:
	char CurrentChar;
	string CurrentLine;
	unsigned int Position;
	unsigned int VectorPosition;
	unsigned int NestingLevel;
	unsigned int OptimizePosition;
	unsigned int CompilePosition;
	vector<string> Code;
	vector<Token> GeneratedCode;

	inline void __cdecl SkipSpaces();
	inline void __cdecl ReadChar();
	inline Token __cdecl ReadToken();
	inline Token __cdecl GetToken(const unsigned int Pos);
	inline void __cdecl SwitchLine();
	inline void __cdecl OptimizeGeneratedCode();
	inline void __cdecl OptimizeFunctions();

	inline Token __cdecl ParseBlock(unsigned int &StartPos, Token &Token_End);
	inline Token __cdecl ParseBody(unsigned int &StartPos, Token &Token_End);
	inline Token __cdecl ParseList(unsigned int &StartPos, Token &Token_End);
	inline Token __cdecl ParseOperator(char First);
	inline string __cdecl ParseWord();
	inline string __cdecl ParseString();
	inline double __cdecl ParseNumber(bool Negative = false);
	inline void __cdecl ParseComment(); 
	inline Pair<string, bool> __cdecl ParseLookup();
	inline double __cdecl ParseMinus();
	inline double __cdecl ParsePlus();

};

inline bool __cdecl IsOperator(char C) {
	return (C == '=' || C == '>' || C == '<' || C == '|'
		|| C == '&' || C == '^' || C == '~' || C == '!' || C == '?');
}

#endif
