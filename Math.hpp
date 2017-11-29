#pragma once

#ifndef MATH_HPP
#define MATH_HPP

#include <time.h>
#include "Ident.hpp"

#define CONSTANT_PI 3.14159265359

inline double __cdecl fact(double _X_) {
	if (_X_ <= 1) return 1;
	else return (_X_ * fact(_X_ - 1));
}

inline Ident __cdecl SCRIPT_ADD(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = 0.0;
	for (Ident Id : Stack)
		Res += Id.GetValue()->GetNumber();
	return Ident("Res", Res);
}

inline Ident __cdecl SCRIPT_SUB(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = Stack[0].GetValue()->GetNumber();
	vector<Ident> New = Stack; New.erase(begin(New));
	for (Ident Id : New)
		Res -= Id.GetValue()->GetNumber();
	return Ident("Res", Res);
}

inline Ident __cdecl SCRIPT_MUL(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = Stack[0].GetValue()->GetNumber();
	vector<Ident> New = Stack; New.erase(begin(New));
	for (Ident Id : New)
		Res *= Id.GetValue()->GetNumber();
	return Ident("Res", Res);
}

inline Ident __cdecl SCRIPT_DIV(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Res = Stack[0].GetValue()->GetNumber();
	vector<Ident> New = Stack; New.erase(begin(New));
	for (Ident Id : New)
		Res /= (Id.GetValue()->GetNumber() == 0 
			? 1 : Id.GetValue()->GetNumber());
	return Ident("Res", Res);
}

inline Ident __cdecl SCRIPT_SINUS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Degree = (Stack[0].GetValue()->GetNumber() * (CONSTANT_PI / 180.0));
	return Ident("Res", sin(Degree));
}

inline Ident __cdecl SCRIPT_COSINUS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Degree = (Stack[0].GetValue()->GetNumber() * (CONSTANT_PI / 180.0));
	return Ident("Res", cos(Degree));
}

inline Ident __cdecl SCRIPT_TANGENS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Degree = (Stack[0].GetValue()->GetNumber() * (CONSTANT_PI / 180.0));
	return Ident("Res", tan(Degree));
}

inline Ident __cdecl SCRIPT_COTANGENS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Degree = (Stack[0].GetValue()->GetNumber() * (CONSTANT_PI / 180.0));
	return Ident("Res", (cos(Degree) / sin(Degree)));
}

inline Ident __cdecl SCRIPT_SEC(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Degree = (Stack[0].GetValue()->GetNumber() * (CONSTANT_PI / 180.0));
	return Ident("Res", (1 / cos(Degree)));
}

inline Ident __cdecl SCRIPT_CSC(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Degree = (Stack[0].GetValue()->GetNumber() * (CONSTANT_PI / 180.0));
	return Ident("Res", (1 / sin(Degree)));
}

inline Ident __cdecl SCRIPT_ASINUS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (asin(Stack[0].GetValue()->GetNumber()) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_ACOSINUS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (acos(Stack[0].GetValue()->GetNumber()) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_ATANGENS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (atan(Stack[0].GetValue()->GetNumber()) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_ATANGENS2(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Y = Stack[0].GetValue()->GetNumber();
	double X = Stack[1].GetValue()->GetNumber();
	return Ident("Res", (atan2(Y, X) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_ACOTANGENS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (atan(1 / Stack[0].GetValue()->GetNumber()) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_ASEC(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Num = (Stack[0].GetValue()->GetNumber());
	return Ident("Res", (acos(1 / Num) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_ACSC(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Num = (Stack[0].GetValue()->GetNumber());
	return Ident("Res", (asin(1 / Num) * (180.0 / CONSTANT_PI)));
}

inline Ident __cdecl SCRIPT_SINH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", sinh(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_COSH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", cosh(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_TANH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", tanh(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_COTH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Num = (Stack[0].GetValue()->GetNumber());
	return Ident("Res", (cosh(Num) / sinh(Num)));
}

inline Ident __cdecl SCRIPT_SECH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (1 / cosh(Stack[0].GetValue()->GetNumber())));
}

inline Ident __cdecl SCRIPT_CSCH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", (1 / sinh(Stack[0].GetValue()->GetNumber())));
}

inline Ident __cdecl SCRIPT_ASINH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", asinh(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_ACOSH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", acosh(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_ATANH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", atanh(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_ACOTH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Num = (Stack[0].GetValue()->GetNumber());
	return Ident("Res", atanh(1 / Num));
}

inline Ident __cdecl SCRIPT_ASECH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Num = (Stack[0].GetValue()->GetNumber());
	return Ident("Res", acosh(1 / Num));
}

inline Ident __cdecl SCRIPT_ACSCH(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Num = (Stack[0].GetValue()->GetNumber());
	return Ident("Res", asinh(1 / Num));
}

inline Ident __cdecl SCRIPT_CEIL(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", ceil(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_FLOOR(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", floor(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_TRUNC(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", trunc(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_MIN(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double CurrentMin = Stack[0].GetValue()->GetNumber();
	vector<Ident> New = Stack; New.erase(begin(New));
	for (Ident Id : New)
		if (Id.GetValue()->GetNumber() < CurrentMin)
			CurrentMin = Id.GetValue()->GetNumber();
	return Ident("Res", CurrentMin);
}

inline Ident __cdecl SCRIPT_MAX(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double CurrentMax = Stack[0].GetValue()->GetNumber();
	vector<Ident> New = Stack; New.erase(begin(New));
	for (Ident Id : New)
		if (Id.GetValue()->GetNumber() > CurrentMax)
			CurrentMax = Id.GetValue()->GetNumber();
	return Ident("Res", CurrentMax);
}

inline Ident __cdecl SCRIPT_AVERAGE(vector<Ident> Stack) {
	double Sum = SCRIPT_ADD(Stack).GetValue()->GetNumber();
	Sum /= (!Stack.size() ? 1 : Stack.size());
	return Ident("Res", Sum);
}

inline Ident __cdecl SCRIPT_ABS(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Number = Stack[0].GetValue()->GetNumber();
	return Ident("Res", (Number < 0 ? -Number : Number));
}

inline Ident __cdecl SCRIPT_NEG(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Number = Stack[0].GetValue()->GetNumber();
	return Ident("Res", -Number);
}

inline Ident __cdecl SCRIPT_MOD(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double Number = Stack[0].GetValue()->GetNumber();
	double Denom = Stack[1].GetValue()->GetNumber();
	return Ident("Res", (Number - trunc(Number / Denom) * Denom));
}

inline Ident __cdecl SCRIPT_FACT(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", fact(floor(Stack[0].GetValue()->GetNumber())));
}

inline Ident __cdecl SCRIPT_SQRT(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", sqrt(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_CBRT(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", cbrt(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_POW(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double X = Stack[0].GetValue()->GetNumber();
	double Y = Stack[1].GetValue()->GetNumber();
	return Ident("Res", pow(X, Y));
}

inline Ident __cdecl SCRIPT_EXP(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", exp(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_LN(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", log(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_LOG10(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	return Ident("Res", log10(Stack[0].GetValue()->GetNumber()));
}

inline Ident __cdecl SCRIPT_LOG(vector<Ident> Stack) {
	if (!Stack.size()) { return Ident("Res", 0.0); }
	double X = Stack[0].GetValue()->GetNumber();
	double Y = Stack[1].GetValue()->GetNumber();
	return Ident("Res", (log(X) / log(Y)));
}

inline Ident __cdecl SCRIPT_RAND(vector<Ident> Stack) {
	double Res = (rand());
	double Min = (!Stack.size() ? 0 : Stack[0].GetValue()->GetNumber());
	double Max = (Stack.size() < 2 ? 0 : Stack[1].GetValue()->GetNumber());
	return Ident("Res", (Min + (Res / RAND_MAX) * (!(Max - Min) ? 1 : (Max - Min))));
}

#endif