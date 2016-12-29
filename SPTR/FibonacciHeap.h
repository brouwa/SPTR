#pragma once
#define phi (1 + sqrt(5)) / 2

#include "FHChain.h"

template <typename T> class FibonacciHeap
{
public:
	int n;
	FibonacciHeap() : n(0), nodes(nullptr), nodeDeg(nullptr), maxnodesnb(0) {}
	~FibonacciHeap();
	void add(T* el, int p);
	bool isEmpty();
	T *ext_min();
	void set_pr(T *el, int p);
	void generate_nodeDeg(int size);
	int maxnodesnb;

	void print();
private:
	FHChain<T*> *nodes;
	FHChain<T*> *minnode;
	FHChain<T*> **nodeDeg;
	int nbnodes;
	void print(FHChain<T*> *d, int i);
	static void clean(FHChain<T*> *d);
};

