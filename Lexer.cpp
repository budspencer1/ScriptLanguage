#include "Lexer.hpp"


Token Lexer::Start(TOKEN_START);
Token Lexer::End(TOKEN_END);
Token Lexer::EOL(TOKEN_EOL);

Lexer::Lexer(const vector<string> Code)
	: Code(Code), Position(0), VectorPosition(0), NestingLevel(0), CompilePosition(0) {
		CurrentLine = this->Code[0];
		CurrentChar = CurrentLine[0];
		GenerateCode();
};

inline void __cdecl Lexer::GenerateCode() {
	GeneratedCode.push_back(Start);
	for (string Line : Code) {
		GenerateLine();
		Position = 0;
		if (VectorPosition < (Code.size() - 1)) {
			CurrentLine = Code[++VectorPosition];
			CurrentChar = CurrentLine[0];
			Position = 0;
		}
	}
	GeneratedCode.push_back(End);
	OptimizeGeneratedCode();
}

inline void __cdecl Lexer::GenerateLine() {
	Token CurrentToken = ReadToken();
	while (!CurrentToken.Compare(TOKEN_EOL)) {
		GeneratedCode.push_back(CurrentToken);
		CurrentToken = ReadToken();
	}
}

inline void __cdecl Lexer::ReadChar() {
	if (Position >= CurrentLine.length()) {
		CurrentChar = 0; 
		return;
	}
	CurrentChar = CurrentLine[++Position];
}

inline void __cdecl Lexer::SkipSpaces() {
	while (CurrentChar == ' ' || CurrentChar == '\t'
		|| CurrentChar == '\r' || CurrentChar == '\n') {
		ReadChar();
	}
}

inline Token __cdecl Lexer::GetNextToken(bool Peek) {
	if (VectorPosition < GeneratedCode.size()) {
		if (!Peek) {
			return GeneratedCode[CompilePosition++];
		}
		return GeneratedCode[CompilePosition];
	}
	return Token(TOKEN_END);
}

inline void __cdecl Lexer::SwitchLine() {
	CurrentLine = Code[++VectorPosition];
	CurrentChar = CurrentLine[0];
	Position = 0;
}

inline Token __cdecl Lexer::GetToken(const unsigned int Pos) {
	if (Pos >= GeneratedCode.size()) {
		return Token(TOKEN_UNKNOWN);
	}
	return GeneratedCode[Pos];
}

inline void __cdecl Lexer::OptimizeGeneratedCode() {
	vector<Token> NewCode;
	Token &Tok = GeneratedCode[0];
	Token HelperToken;
	string IdentName = "";
	unsigned int CurrentPosition = 0;
	for (; !Tok.Compare(TOKEN_END);) {
		switch (Tok.GetType()) {
		case TOKEN_START: Tok = GetToken(CurrentPosition++); break;
		case TOKEN_END: Tok = GetToken(CurrentPosition++); break; 
		case TOKEN_LBRAK: 
			HelperToken = ParseBlock(CurrentPosition, Tok); 
			NewCode.push_back(HelperToken); break;
		case TOKEN_LBODY:
			HelperToken = ParseBody(CurrentPosition, Tok);
			NewCode.push_back(HelperToken); break;
		case TOKEN_LPAREN:
			HelperToken = ParseList(CurrentPosition, Tok);
			NewCode.push_back(HelperToken); break;
		case TOKEN_COMMENT: Tok = GetToken(CurrentPosition++); break;
		default: NewCode.push_back(Tok); Tok = GetToken(CurrentPosition++); break;
		}
	}
	//NewCode.push_back(End);
	GeneratedCode = NewCode;
	OptimizeFunctions();
}

inline void __cdecl Lexer::OptimizeFunctions() {
	vector<Token> NewCode, Arglist, Body;
	Token &Tok = GeneratedCode[0];
	Token HelperToken;
	string IdentName = "";
	unsigned int Pos = 0;
	for (; Pos < GeneratedCode.size();) {
		if (GeneratedCode[Pos].GetStringValue() == "function" 
			&& GeneratedCode[Pos].Compare(TOKEN_IDENTIFIER)) {
			++Pos; 
			IdentName = GeneratedCode[Pos++].GetStringValue();
			Arglist = GeneratedCode[Pos++].GetVectorValue();
			Body = GeneratedCode[Pos++].GetVectorValue();
			HelperToken = Token(TOKEN_FUNCTION, IdentName, Arglist, Body);
			NewCode.push_back(HelperToken);
		} else {
			NewCode.push_back(GeneratedCode[Pos++]); 
		}
	}
	GeneratedCode = NewCode;
}

inline Token __cdecl Lexer::ParseBlock(unsigned int &StartPos, Token &Token_End) {
	Token Tok = GetToken(StartPos++);
	vector<Token> BlockResult;
	unsigned int Position = StartPos;
	unsigned int StartNesting = NestingLevel;
	++NestingLevel;
	while (NestingLevel > StartNesting) {
		if (Tok.Compare(TOKEN_LBODY)) {
			BlockResult.push_back(ParseBody(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_LBRAK)) {
			BlockResult.push_back(ParseBlock(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_LPAREN)) {
			BlockResult.push_back(ParseList(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_RBRAK)) --NestingLevel;
		else if (NestingLevel > StartNesting) {
			BlockResult.push_back(Tok);
			Tok = GetToken(StartPos++);
		} else { Tok = GetToken(StartPos++); }
	}
	Tok = GetToken(StartPos++);
	Token_End = Tok;
	return Token(TOKEN_BLOCK, BlockResult);
}

inline Token __cdecl Lexer::ParseBody(unsigned int &StartPos, Token &Token_End) {
	Token Tok = GetToken(StartPos++);
	vector<Token> BlockResult;
	unsigned int Position = StartPos;
	unsigned int StartNesting = NestingLevel;
	++NestingLevel;
	while (NestingLevel > StartNesting) {
		if (Tok.Compare(TOKEN_LBRAK)) {
			BlockResult.push_back(ParseBlock(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_LBODY)) {
			BlockResult.push_back(ParseBody(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_LPAREN)) {
			BlockResult.push_back(ParseList(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_RBODY)) --NestingLevel;
		else if (NestingLevel > StartNesting) {
			BlockResult.push_back(Tok);
			Tok = GetToken(StartPos++);
		} else { Tok = GetToken(StartPos++); }
	}
	Tok = GetToken(StartPos++);
	Token_End = Tok;
	return Token(TOKEN_BODY, BlockResult);
}

inline Token __cdecl Lexer::ParseList(unsigned int &StartPos, Token &Token_End) {
	Token Tok = GetToken(StartPos++);
	vector<Token> BlockResult;
	unsigned int Position = StartPos;
	unsigned int StartNesting = NestingLevel;
	++NestingLevel;
	while (NestingLevel > StartNesting) {
		if (Tok.Compare(TOKEN_LBRAK)) {
			BlockResult.push_back(ParseBlock(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_LBODY)) {
			BlockResult.push_back(ParseBody(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_LPAREN)) {
			BlockResult.push_back(ParseList(StartPos, Tok));
		}
		else if (Tok.Compare(TOKEN_RPAREN)) --NestingLevel;
		else if (NestingLevel > StartNesting) {
			BlockResult.push_back(Tok);
			Tok = GetToken(StartPos++);
		} else { Tok = GetToken(StartPos++); }
	}
	Tok = GetToken(StartPos++);
	Token_End = Tok;
	return Token(TOKEN_LIST, BlockResult);
}

inline string __cdecl Lexer::ParseWord() {
	string Word = "";
	switch (CurrentChar) {
	case 'a': case 'b': case 'c': case 'd': case 'e':
	case 'f': case 'g': case 'h': case 'i': case 'j':
	case 'k': case 'l': case 'm': case 'n': case 'o':
	case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y':
	case 'z':
	case 'A': case 'B': case 'C': case 'D': case 'E':
	case 'F': case 'G': case 'H': case 'I': case 'J':
	case 'K': case 'L': case 'M': case 'N': case 'O':
	case 'P': case 'Q': case 'R': case 'S': case 'T':
	case 'U': case 'V': case 'W': case 'X': case 'Y':
	case 'Z': case '_':
		while (isalpha(CurrentChar) 
			|| CurrentChar == '_' 
			|| isdigit(CurrentChar)) {
			Word += CurrentChar;
			ReadChar();
		}
	}
	return Word;
}

inline string __cdecl Lexer::ParseString() {
	string Answer = "";
	while (CurrentChar != '"') {
		Answer += CurrentChar;
		ReadChar();
		if (CurrentChar == 0)
			if (VectorPosition < (Code.size() - 1)) 
				SwitchLine();
	}
	ReadChar();
	return Answer;
}

inline double __cdecl Lexer::ParseNumber(bool Negative) {
	string Temp = "0";
	while (isdigit(CurrentChar) && CurrentChar != '.') {
		Temp += CurrentChar; ReadChar();
	}
	if (CurrentChar == '.') {
		Temp += CurrentChar; ReadChar();
		while (isdigit(CurrentChar)) {
			Temp += CurrentChar; ReadChar();
		}
	}
	if (CurrentChar == 'e') {
		Temp += 'e'; ReadChar();
		Temp += CurrentChar; ReadChar();
		while (isdigit(CurrentChar)) {
			Temp += CurrentChar;
			ReadChar();
		}
	}
	return (Negative ? -(atof(Temp.c_str())) : atof(Temp.c_str()));
}

inline void __cdecl Lexer::ParseComment() {
	while (CurrentChar != '*') {
		ReadChar();
		if (!CurrentChar)
			if (VectorPosition < (Code.size() - 1))
				SwitchLine();
	}
	ReadChar();
}

inline Pair<string, bool> __cdecl Lexer::ParseLookup() {
	bool Intern = false; string Lookup = "";
	if (CurrentChar == '@') { ReadChar(); Intern = true; }
	Lookup = ParseWord();
	return ConstructPair<string, bool>(Lookup, Intern);
}

inline double __cdecl Lexer::ParseMinus() {
	double Number = ParseNumber(true);
	return Number;
}

inline double __cdecl Lexer::ParsePlus() {
	double Number = ParseNumber(false);
	return Number;
}

inline Token __cdecl Lexer::ParseOperator(char First) {
	string Oper = ""; Oper += First;
	while (IsOperator(CurrentChar)) {
		Oper += CurrentChar;
		ReadChar();
	}
	return Token(TOKEN_IDENTIFIER, Oper);
}

inline Token __cdecl Lexer::ReadToken() {
	string Temp = "";
	double Number = 0.0;
	Pair<string, bool> PairRes;
	char Tmp;
	SkipSpaces();
	switch (CurrentChar) {
	case ',': ReadChar(); return Token(TOKEN_COMMA);
	case ';': ReadChar(); return Token(TOKEN_SEMICOLON);
	case '(': ReadChar(); return Token(TOKEN_LPAREN);
	case ')': ReadChar(); return Token(TOKEN_RPAREN);
	case '[': ReadChar(); return Token(TOKEN_LBRAK);
	case ']': ReadChar(); return Token(TOKEN_RBRAK);
	case '{': ReadChar(); return Token(TOKEN_LBODY);
	case '}': ReadChar(); return Token(TOKEN_RBODY);
	case '+': ReadChar(); return Token(TOKEN_NUMBER, ParsePlus());
	case '-': ReadChar(); return Token(TOKEN_NUMBER, ParseMinus());
	case '"': ReadChar(); return Token(TOKEN_STRING, ParseString());
	case '=': case '>': case '<': case '&':
	case '^': case '!': case '~': case '|': case '?':
		Tmp = CurrentChar; ReadChar(); return ParseOperator(Tmp);
	case '*': ReadChar(); ParseComment(); return Token(TOKEN_COMMENT);
	case '@': ReadChar(); PairRes = ParseLookup(); return (PairRes.Second ?
		Token(TOKEN_INTERNLOOKUP, PairRes.First) : Token(TOKEN_LOOKUP, PairRes.First));
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': 
	case '.':
		return Token(TOKEN_NUMBER, ParseNumber());
	case 'a': case 'b': case 'c': case 'd': case 'e':
	case 'f': case 'g': case 'h': case 'i': case 'j':
	case 'k': case 'l': case 'm': case 'n': case 'o':
	case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y':
	case 'z':
	case 'A': case 'B': case 'C': case 'D': case 'E':
	case 'F': case 'G': case 'H': case 'I': case 'J':
	case 'K': case 'L': case 'M': case 'N': case 'O':
	case 'P': case 'Q': case 'R': case 'S': case 'T':
	case 'U': case 'V': case 'W': case 'X': case 'Y':
	case 'Z': case '_':
		while (isalpha(CurrentChar)
			|| CurrentChar == '_'
			|| isdigit(CurrentChar)) {
			Temp += CurrentChar;
			ReadChar();
		}
		/* if else structure */
		if (Temp == "if") return Token(BLOCK_IF, 0.0);
		if (Temp == "else") return Token(BLOCK_ELSE, 0.0);
		/* loop variants */
		if (Temp == "do") return Token(BLOCK_DO, 0.0);
		if (Temp == "loop") return Token(BLOCK_LOOP, 0.0);
		if (Temp == "while") return Token(BLOCK_WHILE, 0.0);
		/* case structure */
		if (Temp == "switch") return Token(BLOCK_SWITCH, 0.0);
		if (Temp == "case") return Token(BLOCK_CASE, 0.0);
		if (Temp == "default") return Token(BLOCK_DEFAULT, 0.0);
		/* other structures */
		if (Temp == "enumeration") return Token(BLOCK_ENUM, 0.0);
		return Token(TOKEN_IDENTIFIER, Temp);
	}
	return EOL;
}




