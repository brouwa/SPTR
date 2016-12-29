#pragma once

#include "Chain.h"

struct Vertex;

template <typename T, typename K> struct Entry
{
	K key;
	T *value;
	Entry(K key, T *value) : key(key), value(value) {}
};

template <typename T, typename K>
class KeyList
{
public:
	int n;
	KeyList() : n(0), first(nullptr), last(nullptr) {};
	~KeyList();
	Entry<T, K> *find(K key);
	Entry<T, K> *pop();
	bool isEmpty();
	bool add(Entry<T, K> *e);
	bool del(K key);
	Chain<struct Entry<T, K>*> *first, *last;
private:
	
};



