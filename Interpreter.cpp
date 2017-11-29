#include "Interpreter.hpp"


inline bool __cdecl CompileCondition(vector<Ident> Results) {
	if (SCRIPT_AND(Results).GetValue()->GetNumber())
		return true;
	return false;
}

inline Ident __cdecl SCRIPT_EXEC(vector<Ident> Stack) {
	vector<string> CurrentCode;
	for (Ident Id : Stack) {
		CurrentCode = ReadFile(Id.GetValue()->GetString().c_str());
		if (CurrentCode.size()) Interpreter Scanner(CurrentCode);
	}
	return Ident("Res", 0.0);
}

inline Ident __cdecl SCRIPT_CONDEXPR(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	vector<Ident> Condition; Condition.push_back(Stack[0]);
	return (CompileCondition(Condition) ? Stack[1] : Stack[2]);
}


inline void __cdecl InitBuiltins() {
	/* Basic */
	ADDBUILTIN("push", 2, SCRIPT_PUSH);
	ADDBUILTIN("set", 2, SCRIPT_SET);
	ADDBUILTIN("pop", -1, SCRIPT_POP);
	ADDBUILTIN("return", 1, SCRIPT_RETURN);
	ADDBUILTIN("?", 3, SCRIPT_CONDEXPR);
	/* IO */
	ADDBUILTIN("input", 1, SCRIPT_INPUT);
	ADDBUILTIN("output", -1, SCRIPT_OUTPUT);
	ADDBUILTIN("execute", -1, SCRIPT_EXEC);
	/* CONVERSION */
	ADDBUILTIN("str2num", 1, SCRIPT_STR2NUM);
	ADDBUILTIN("num2str", 1, SCRIPT_NUM2STR);
	/* MATH */
	ADDBUILTIN("add", -1, SCRIPT_ADD);
	ADDBUILTIN("sub", -1, SCRIPT_SUB);
	ADDBUILTIN("mul", -1, SCRIPT_MUL);
	ADDBUILTIN("div", -1, SCRIPT_DIV);
	ADDBUILTIN("mod", 2, SCRIPT_MOD);
	ADDBUILTIN("abs", 1, SCRIPT_ABS);
	ADDBUILTIN("neg", 1, SCRIPT_NEG);
	ADDBUILTIN("fact", 1, SCRIPT_FACT);
	ADDBUILTIN("ceil", 1, SCRIPT_CEIL);
	ADDBUILTIN("floor", 1, SCRIPT_FLOOR);
	ADDBUILTIN("trunc", 1, SCRIPT_TRUNC);
	ADDBUILTIN("sqrt", 1, SCRIPT_SQRT);
	ADDBUILTIN("cbrt", 1, SCRIPT_CBRT);
	ADDBUILTIN("pow", 2, SCRIPT_POW);
	ADDBUILTIN("exp", 1, SCRIPT_EXP);
	ADDBUILTIN("ln", 1, SCRIPT_LN);
	ADDBUILTIN("log10", 1, SCRIPT_LOG10);
	ADDBUILTIN("log", 2, SCRIPT_LOG);
	ADDBUILTIN("sin", 1, SCRIPT_SINUS);
	ADDBUILTIN("cos", 1, SCRIPT_COSINUS);
	ADDBUILTIN("tan", 1, SCRIPT_TANGENS);
	ADDBUILTIN("cot", 1, SCRIPT_COTANGENS);
	ADDBUILTIN("sec", 1, SCRIPT_SEC);
	ADDBUILTIN("csc", 1, SCRIPT_CSC);
	ADDBUILTIN("asin", 1, SCRIPT_ASINUS);
	ADDBUILTIN("acos", 1, SCRIPT_ACOSINUS);
	ADDBUILTIN("atan", 1, SCRIPT_ATANGENS);
	ADDBUILTIN("atan2", 2, SCRIPT_ATANGENS2);
	ADDBUILTIN("acot", 1, SCRIPT_ACOTANGENS);
	ADDBUILTIN("asec", 1, SCRIPT_ASEC);
	ADDBUILTIN("acsc", 1, SCRIPT_ACSC);
	ADDBUILTIN("sinh", 1, SCRIPT_SINH);
	ADDBUILTIN("cosh", 1, SCRIPT_COSH);
	ADDBUILTIN("tanh", 1, SCRIPT_TANH);
	ADDBUILTIN("coth", 1, SCRIPT_COTH);
	ADDBUILTIN("sech", 1, SCRIPT_SECH);
	ADDBUILTIN("csch", 1, SCRIPT_CSCH);
	ADDBUILTIN("asinh", 1, SCRIPT_ASINH);
	ADDBUILTIN("acosh", 1, SCRIPT_ACOSH);
	ADDBUILTIN("atanh", 1, SCRIPT_ATANH);
	ADDBUILTIN("acoth", 1, SCRIPT_ACOTH);
	ADDBUILTIN("asech", 1, SCRIPT_ASECH);
	ADDBUILTIN("acsch", 1, SCRIPT_ACSCH);
	/* STATISTICS */
	ADDBUILTIN("min", -1, SCRIPT_MIN);
	ADDBUILTIN("max", -1, SCRIPT_MAX);
	ADDBUILTIN("average", -1, SCRIPT_AVERAGE);
	ADDBUILTIN("random", 0, SCRIPT_RAND);
	/* LOGICAL */
	ADDBUILTIN("==", 2, SCRIPT_EQUAL);
	ADDBUILTIN("!=", 2, SCRIPT_NOTEQUAL);
	ADDBUILTIN(">", 2, SCRIPT_GREATER);
	ADDBUILTIN("<", 2, SCRIPT_LESS);
	ADDBUILTIN(">=", 2, SCRIPT_GREATEREQUAL);
	ADDBUILTIN("<=", 2, SCRIPT_LESSEQUAL);
	ADDBUILTIN("&&", -1, SCRIPT_AND);
	ADDBUILTIN("||", -1, SCRIPT_OR);
	ADDBUILTIN("!", 1, SCRIPT_NOT);
	/* BITWISE */
}

Interpreter::Interpreter(vector<string> Code) : Scanner(Code), LastReturn("RET", 0.0) {
	srand((unsigned)time((time_t)0));
	Scanner.GenerateCode();
	InitBuiltins();
	RunCode(Scanner.GetGeneratedCode());
	Scanner.GetGeneratedCode().clear();
}

inline vector<Ident> __cdecl Interpreter::CompileArglist(Token Arglist) {
	Ident TempRes, HelperId;
	string CommandName = "";
	vector<Ident> Args, Stack, InternStack;
	unsigned int Pos = 0;
	for (; Pos < Arglist.GetVectorValue().size();) {
		switch (Arglist.GetVectorValue()[Pos].GetType()) {
		case TOKEN_NUMBER: Args.push_back(Ident("", CompileNumber(Arglist.GetVectorValue()[Pos++]))); break;
		case TOKEN_STRING: Args.push_back(Ident("", CompileString(Arglist.GetVectorValue()[Pos++]))); break;
		case TOKEN_BLOCK: Args.push_back(Ident("", CompileVector(Arglist.GetVectorValue()[Pos++]))); break;
		case TOKEN_IDENTIFIER: 
			CommandName = Arglist.GetVectorValue()[Pos].GetStringValue();
			if (Arglist.GetVectorValue()[++Pos].Compare(TOKEN_LIST)) {
				Stack = CompileArglist(Arglist.GetVectorValue()[Pos]);
				if (BuiltinExists(CommandName)) {
					HelperId = GetIdent(CommandName);
					if (Stack.size() < HelperId.GetCount() && HelperId.GetCount() != -1) {
						cout << "Error: Command \"" << CommandName << "\" expected " 
							<< HelperId.GetCount() << " Parameters instead of " << Stack.size() << "." << endl;
						TempRes = Ident("", 0.0);
					} else { TempRes = ExecuteBuiltin(GetIdent(CommandName), Stack); }
				} else if (FunctionExists(CommandName)) {
					TempRes = ExecuteFunction(GetIdent(CommandName));
				} else {
					TempRes = Ident("", 0.0);
					cout << "Error: Command \"" << CommandName << "\" wasn't found." << endl;
				}
				Args.push_back(TempRes);
			} else { ++Pos; Args.push_back(Ident("", CommandName)); } break;
		case TOKEN_LOOKUP:
			CommandName = Arglist.GetVectorValue()[Pos++].GetStringValue();
			if (IdentExists(CommandName)) {
				TempRes = GetIdent(CommandName);
				Args.push_back(TempRes);
			} else {
				cout << "Error: Identifier (Lookup) \"" << CommandName << "\" wasn't found." << endl;
				Args.push_back(Ident("", 0.0));
				continue;
			} break;
		default: ++Pos; break;
		}
	}
	return Args; 
}

inline unsigned int __cdecl Interpreter::CompileFunctionDecl(Token Arglist) {
	return (unsigned int)(Arglist.GetVectorValue()[0].GetNumberValue());
}

inline Ident __cdecl Interpreter::ExecuteBuiltin(Ident Command, vector<Ident> Stack) {
	return (Command.Builtin(Stack));
}

inline Ident __cdecl Interpreter::ExecuteFunction(Ident Command) {
	unsigned int StartIdents = (unsigned int)Idents.size();
	unsigned int EndIdents = 0;
	unsigned int Pos = 1;
	unsigned int Position = 1;
	Ident ReturnVal;
	ReturnVal = CompileBody(Command.GetBody());
	EndIdents = (unsigned int)Idents.size();
	Pos = (EndIdents - StartIdents);
	while (Pos--) {
		Idents.pop_back();
	}
	return ReturnVal;
}

inline double __cdecl Interpreter::CompileNumber(Token Number) {
	return (Number.GetNumberValue());
}

inline string __cdecl Interpreter::CompileString(Token String) {
	string CompiledString = "";
	unsigned int Pos = 0;
	for (; Pos < String.GetStringValue().length();) {
		switch (String.GetStringValue()[Pos]) {
		case '#': ++Pos; 
			if (!IsSmallLetter(String.GetStringValue()[Pos])) {
				switch (String.GetStringValue()[Pos]) {
				case '#': CompiledString += '#'; ++Pos; break;
				case 'N': CompiledString += '\n'; ++Pos; break;
				case 'T': CompiledString += '\t'; ++Pos; break;
				case 'R': CompiledString += '\r'; ++Pos; break;
				case '0': CompiledString += '\0'; ++Pos; break;
				case ' ': CompiledString += ' '; ++Pos; break;
				default: CompiledString += String.GetStringValue()[Pos++]; break;
				} break;
			}
			CompiledString += '#';
			CompiledString += String.GetStringValue()[Pos++]; break;
		default: CompiledString += String.GetStringValue()[Pos++]; break;
		}
	}
	return CompiledString;
}

inline vector<string> Interpreter::CompileVector(Token Vector) {
	vector<string> CompiledVector;
	vector<Ident> Stack;
	string TempValue = "";
	Ident Lookup;
	for (Token Tok : Vector.GetVectorValue()) {
		switch (Tok.GetType()) {
		case TOKEN_NUMBER: CompiledVector.push_back(::Number2String(Tok.GetNumberValue())); break;
		case TOKEN_STRING: CompiledVector.push_back(Tok.GetStringValue()); break;
		case TOKEN_BLOCK: CompiledVector.push_back(Vector2String(Tok)); break;
		case TOKEN_LOOKUP:
			Lookup = CompileLookup(Tok);
			switch (Lookup.GetType()) {
			case ID_NUMBER: CompiledVector.push_back(::Number2String(Lookup.GetValue()->GetNumber())); break;
			case ID_STRING: CompiledVector.push_back(Lookup.GetValue()->GetString()); break;
			case ID_VECTOR: CompiledVector.push_back(Vector2String(Tok)); break;
			default: break;
			}
			break;
		default: break;
		}
	}
	return CompiledVector;
}

inline Ident __cdecl Interpreter::CompileLookup(Token Lookup) {
	Ident Answer;
	if (IdentExists(Lookup.GetStringValue())) {
		return GetIdent(Lookup.GetStringValue());
	}
	return (Ident("", 0.0));
}

inline string __cdecl Interpreter::Vector2String(Token Vector) {
	string VectorString = "";
	Ident Lookup;
	for (Token Tok : Vector.GetVectorValue()) {
		switch (Tok.GetType()) {
		case TOKEN_NUMBER: VectorString += ::Number2String(Tok.GetNumberValue()); break;
		case TOKEN_STRING: VectorString += Tok.GetStringValue(); break;
		case TOKEN_BLOCK: VectorString += Vector2String(Tok); break;
		case TOKEN_LOOKUP:
			Lookup = CompileLookup(Tok);
			switch (Lookup.GetType()) {
			case ID_NUMBER: VectorString += ::Number2String(Lookup.GetValue()->GetNumber()); break;
			case ID_STRING: VectorString += Lookup.GetValue()->GetString(); break;
			case ID_VECTOR: VectorString += Vector2String(Tok); break;
			default: break;
			}
		default: break;
		}
		if (!Tok.Compare(TOKEN_COMMA)) { VectorString += ' '; }
	}
	return VectorString;
}

inline Ident __cdecl Interpreter::CompileSwitchStatement(Token Object) {
	return CompileArglist(Object)[0];
}

inline void __cdecl Interpreter::CompileLoopSequence(Ident Iter, unsigned int Count, vector<Token> Block) {
	unsigned int C = 0;
	bool New = false;
	if (!IdentExists(Iter.GetName())) { New = true; Idents.push_back(Iter); }
	else { GetIdent(Iter.GetName()).SetNumber(0.0); }
	while (C++ < Count) {
		CompileBody(Block);
		GetIdent(Iter.GetName()).SetNumber((double)C);
	}
	if (New) { Idents.erase(Idents.begin() + FindIdent(Iter.GetName())); }
}

inline void __cdecl Interpreter::CompileCaseSequence(Ident Id, vector<Token> Block) {
	unsigned int Position = 0;
	Ident TempId;
	for (; Position < Block.size();) {
		switch (Block[Position].GetType()) {
		case BLOCK_CASE:
			++Position;
			TempId = CompileArglist(Block[Position++])[0];
			if (CompareIdents(Id, TempId)) {
				CompileBody(Block[Position++].GetVectorValue());
				return;
			}
			break;
		case BLOCK_DEFAULT:
			CompileBody(Block[++Position].GetVectorValue());
			++Position; return;
		default: ++Position; break;
		}
	}
}

inline void __cdecl Interpreter::CompileEnumeration(vector<Ident> Args, vector<Token> Block) {
	const double StartValue = (double)(!Args.size() ? 0 : Args[0].GetValue()->GetNumber());
	const double Step = (double)(Args.size() < 2 ? 1 : Args[1].GetValue()->GetNumber());
	double CurrentValue = StartValue;
	for (Token Tok : Block) {
		if (!Tok.Compare(TOKEN_COMMA)) {
			if ((Tok.Compare(TOKEN_IDENTIFIER) || Tok.Compare(TOKEN_STRING))) {
				if (!IdentExists(Tok.GetStringValue())) {
					Idents.push_back(Ident(Tok.GetStringValue(), CurrentValue));
					CurrentValue += Step;
				} else { cout << "Error: Identifier \"" << Tok.GetStringValue() << "\" already exists." << endl; }
			} else { cout << "Error: Expected \"Identifier\" or \"String\" as Parameter in Enumeration." << endl; }
		}
	}
}

inline Ident __cdecl Interpreter::CompileBody(vector<Token> Body) {
	unsigned int Position = 0;
	unsigned int Pos2 = 0;
	unsigned int Count = 0;
	string IdentName = "";
	vector<Ident> Args;
	vector<Token> Block;
	Ident ReturnVal, Id, Id2;
	bool Cond = false;
	for (; Position < Body.size();) {
		switch (Body[Position].GetType()) {
		case TOKEN_IDENTIFIER:
			IdentName = Body[Position++].GetStringValue();
			Args = CompileArglist(Body[Position++]);
			if (BuiltinExists(IdentName)) {
				Id = GetIdent(IdentName);
				if (Args.size() < Id.GetCount() && Id.GetCount() != -1) {
					cout << "Error: Command \"" << IdentName << "\" expected "
						<< Id.GetCount() << " Parameters instead of " << Args.size() << "." << endl;
					ReturnVal = Ident("", 0.0);
				} else { ReturnVal = ExecuteBuiltin(GetIdent(IdentName), Args); }
			} else if (FunctionExists(IdentName)) { ReturnVal = ExecuteFunction(GetIdent(IdentName)); }
			else { cout << "Error: Command \"" << IdentName << "\" wasn't found." << endl; }
			break;
		case BLOCK_IF:
			Cond = CompileCondition(CompileArglist(Body[++Position]));
			if (Cond != 0.0) { CompileBody(Body[++Position].GetVectorValue()); }
			else { ++Position; }
			if (Body[++Position].GetType() == BLOCK_ELSE) {
				if (Cond == 0.0) { CompileBody(Body[++Position].GetVectorValue()); }
				else { ++Position; }
			}
			break;
		case BLOCK_DO:
			Block = Body[++Position].GetVectorValue();
			if (Body[++Position].GetType() == BLOCK_WHILE) {
				++Position;
				do { CompileBody(Block); } 
				while (CompileCondition(CompileArglist(Body[Position])));
				++Position;
			}
			else { CompileBody(Block); /*++Position;*/ }
			break;
		case BLOCK_WHILE:
			Pos2 = ++Position;
			Block = Body[++Position].GetVectorValue();
			while (CompileCondition(CompileArglist(Body[Pos2]))) {
				CompileBody(Block);
			}
			++Position; break;
		case BLOCK_SWITCH:
			Id = CompileSwitchStatement(Body[++Position]);
			CompileCaseSequence(Id, Body[++Position].GetVectorValue());
			++Position;
			break;
		case BLOCK_LOOP:
			Id2.SetNumber(0.0);
			Args = CompileArglist(Body[++Position]);
			Id2.SetName(Args[0].GetValue()->GetString());
			Count = (unsigned int)Args[1].GetValue()->GetNumber();
			Block = Body[++Position].GetVectorValue();
			CompileLoopSequence(Id2, Count, Block);
			++Position; break;
		default: ++Position; break;
		}
	}
	return ReturnVal;
}

inline void __cdecl Interpreter::RunCode(vector<Token> Code) {
	unsigned int Position = 1;
	unsigned int Count = 0;
	unsigned int Pos2 = 0;
	bool Cond = false;
	Ident Id, Id2;
	string IdentName = "";
	vector<Ident> Args;
	vector<Token> Body;
	for (; Position < Code.size();) {
		switch (Code[Position].GetType()) {
		case TOKEN_IDENTIFIER:
			IdentName = Code[Position++].GetStringValue();
			Args = CompileArglist(Code[Position++]);
			if (BuiltinExists(IdentName)) {
				Id = GetIdent(IdentName);
				if (Args.size() < Id.GetCount() && Id.GetCount() != -1) {
					cout << "Error: Command \"" << IdentName << "\" expected "
						<< Id.GetCount() << " Parameters instead of " << Args.size() << "." << endl;
				} else { ExecuteBuiltin(GetIdent(IdentName), Args); }
			} else if (FunctionExists(IdentName)) {
				ExecuteFunction(GetIdent(IdentName));
			} else { cout << "Error: Command \"" << IdentName << "\" wasn't found." << endl; }
			break;
		case BLOCK_IF:
			Cond = CompileCondition(CompileArglist(Code[++Position]));
			if (Cond != 0.0) { CompileBody(Code[++Position].GetVectorValue()); }
			else { ++Position; }
			if (Code[++Position].GetType() == BLOCK_ELSE) {
				if (Cond == 0.0) { CompileBody(Code[++Position].GetVectorValue()); }
				else { ++Position; }
			}
			break;
		case BLOCK_DO:
			Body = Code[++Position].GetVectorValue();
			if (Code[++Position].GetType() == BLOCK_WHILE) {
				++Position;
				do { CompileBody(Body); } 
				while (CompileCondition(CompileArglist(Code[Position])));
				++Position;
			} else { CompileBody(Body); /*++Position;*/ }
			break;
		case BLOCK_WHILE: 
			Pos2 = ++Position;
			Body = Code[++Position].GetVectorValue();
			while (CompileCondition(CompileArglist(Code[Pos2]))) {
				CompileBody(Body);
			}
			++Position; break;
		case BLOCK_SWITCH:
			Id = CompileSwitchStatement(Code[++Position]);
			CompileCaseSequence(Id, Code[++Position].GetVectorValue());
			++Position;
			break;
		case BLOCK_LOOP:
			Id2.SetNumber(0.0);
			Args = CompileArglist(Code[++Position]);
			Id2.SetName(Args[0].GetValue()->GetString());
			Count = (unsigned int)Args[1].GetValue()->GetNumber();
			Body = Code[++Position].GetVectorValue();
			CompileLoopSequence(Id2, Count, Body); 
			++Position; break;
		case BLOCK_ENUM:
			Args = CompileArglist(Code[++Position]);
			Body = Code[++Position].GetVectorValue();
			CompileEnumeration(Args, Body);
			++Position; break;
		case TOKEN_FUNCTION:
			IdentName = Code[Position].GetStringValue();
			Body = Code[Position++].GetVectorValue2();
			Idents.push_back(Ident(IdentName, 0, Body));
			break;
		default: ++Position; break;
		}
	}
} 