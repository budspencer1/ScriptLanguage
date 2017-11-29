#include "Ident.hpp"

Ident::Ident()
	: Type(ID_NUMBER), Name(""), Val(new IdentValue(0.0)) {
}

Ident::Ident(string Name, IdentValue Value, bool Macro)
	: Type(ID_NUMBER), Name(Name), Macro(Macro) {
	Val = &Value; // bs
}

Ident::Ident(string Name, double Number, bool Macro)
	: Type(ID_NUMBER), Name(Name), Val(new IdentValue(Number)), Macro(Macro), Count(0) {
}

Ident::Ident(string Name, string String, bool Macro)
	: Type(ID_STRING), Name(Name), Val(new IdentValue(String)), Macro(Macro), Count(0) {
}

Ident::Ident(string Name, vector<string> Vector, bool Macro)
	: Type(ID_VECTOR), Name(Name), Val(new IdentValue(Vector)), Macro(Macro), Count(0) {
}

Ident::Ident(string Name, void *Builtin, bool Macro)
	: Type(ID_BUILTIN), Name(Name), Val(new IdentValue(0.0)), Macro(Macro), Count(0) {
	Cmd = (void (*) (vector<Ident *>))Builtin;
}

Ident::Ident(string Name, unsigned int Count, vector<Token> Body, bool Macro)
	: Type(ID_FUNCTION), Name(Name), Body(Body), Macro(Macro), Count(Count) {
}


