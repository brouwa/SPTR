#pragma once

template <typename T> class FHChain
{
public:
	FHChain(T v) : v(v), next(nullptr), father(nullptr), childs(nullptr), deg(0), marked(false) {}
	FHChain(T v, FHChain *prev, FHChain *next) : v(v), prev(prev), next(next), father(nullptr), childs(nullptr), deg(0), marked(false) {}
	void unlink(FHChain *&from);
	void insert(FHChain *&in);
	void insertaslist(FHChain *&in);

	T v;
	FHChain *prev, *next;
	FHChain *father;
	FHChain *childs;
	int deg;
	bool marked;
};



