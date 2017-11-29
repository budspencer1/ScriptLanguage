/*
* Project:				Stack (template class to store elements like in a list or vector)
* File Name:			Pair.hpp
* Author:				Sebastian <3
* Date:					07, 2017
*
* Description:			Define Template Class "Pair" and its operators and members
*/


#pragma once

#ifndef PAIR_HPP
#define PAIR_HPP

#define NULL 0
#define ONE 1


template <class F, class S>
struct Pair
{
	Pair() { };
	Pair(const F &First_, const S &Second_)
	{
		First = First_;
		Second = Second_;
	}
	Pair(const Pair<F, S> &Reference)
	{
		First = Reference.First;
		Second = Reference.Second;
	}

	void operator = (const Pair<F, S> &Reference)
	{
		First = Reference.First;
		Second = Reference.Second;
	}

	Pair<F, S> &Swap(const Pair<F, S> &Other)
	{
		Pair<F, S> CopyOfThis = *this;
		First = Other.First;
		Second = Other.Second;
		Other = CopyOfThis;
		return *this;
	}

	bool operator == (const Pair<F, S> &Second) { return (Second.First == First && Second.Second == Second); }
	bool operator != (const Pair<F, S> &Second) { return (Second.First != First || Second.Second != Second); }

	F First;
	S Second;
};

template <class F, class S>
const Pair<F, S> ConstructPair(const F &First, const S &Second)
{
	Pair<F, S> Ans;
	Ans.First = First;
	Ans.Second = Second;
	return Ans;
}

#endif


