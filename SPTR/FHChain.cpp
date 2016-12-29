#include "stdafx.h"
#include "FHChain.h"

/*FHChain::~FHChain()
{
}*/

template <typename T> void FHChain<T>::unlink(FHChain *&from)
{
	if (next == this) from = nullptr;
	else
	{
		if (from == this) from = next;
		prev->next = next;
		next->prev = prev;
	}
}

template <typename T> void FHChain<T>::insert(FHChain *&in)
{
	if (in == nullptr)
	{
		in = this;
		next = this;
		prev = this;
	}
	else
	{
		prev = in->prev;
		next = in;
		in->prev->next = this;
		in->prev = this;
	}
}

template <typename T> void FHChain<T>::insertaslist(FHChain *&in)
{
	if (in == nullptr) in = this;
	else
	{
		in->prev->next = this;
		prev->next = in;

		FHChain *tmp = prev;
		prev = in->prev;
		in->prev = tmp;
	}
}

template class FHChain<struct Vertex*>;