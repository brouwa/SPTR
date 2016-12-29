#pragma once

#include "KeyList.h"

template <typename T, typename K>
class Hashtable
{
public:
	Hashtable(int(*hashCode)(K, int), int N = 1) : n(0), N(N), hashCode(hashCode) { E = new KeyList<T, K>[N]; for (int i = 0; i < N; i++) E[i] = KeyList<T, K>(); };
	~Hashtable();
	int size();
	void add(T *value, K key);
	void add(Entry<T, K> *e);
	void del(K key);
	T* find(K key);
	float mls();
	KeyList<T, K> *E;

	int n;
	int N;
private:
	void resize(int f);
	int(*hashCode)(K, int);
};


