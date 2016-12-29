#include "stdafx.h"
#include "KeyList.h"


template <typename T, typename K> KeyList<T,K>::~KeyList()
{
	while (!isEmpty())
	{
		Entry<T, K> *e = pop();
		delete e->value;
		delete e;
	}
}

template <typename T, typename K> Entry<T, K> *KeyList<T, K>::find(K key)
{
	int i = n;
	Chain<struct Entry<T, K>*> *c = first;
	while (i--)
	{
		if (c->var->key == key) return c->var;
		c = c->next;
	}
	return nullptr;
}

template <typename T, typename K> Entry<T, K> *KeyList<T, K>::pop()
{
	if (n == 0) return nullptr;
	Chain<struct Entry<T, K>*> *c = first;
	Entry<T, K> *e = c->var;
	first = first->next;
	if (--n == 0) last = first;
	delete c;
	return e;
}

template <typename T, typename K> bool KeyList<T, K>::isEmpty()
{
	return n == 0;
}

template <typename T, typename K> bool KeyList<T, K>::add(Entry<T, K> *e)
{
	if (find(e->key)) return false;
	first = new Chain<struct Entry<T, K>*>(e, first);
	if (n++ == 0) last = first;
	return true;
}

template <typename T, typename K> bool KeyList<T, K>::del(K key)
{
	Chain<struct Entry<T, K>*> *c = first;
	if (first->var->key == key)
	{
		first = first->next;
		if (--n == 0) last = first;
		delete c;
		return true;
	}
	else
	{
		int i = n;
		while (--i)
		{
			if (c->next->var->key == key)
			{
				Chain<struct Entry<T, K>*> *cf = c->next;
				c->next = cf->next;
				delete cf;
				return true;
			}
			c = c->next;
		}
	}
	return false;
}

template class KeyList<struct Vertex, unsigned int>;