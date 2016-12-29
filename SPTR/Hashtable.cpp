#include "stdafx.h"
#include "Hashtable.h"

template <typename T, typename K> Hashtable<T,K>::~Hashtable()
{
	delete[] E;
}

template <typename T, typename K> int Hashtable<T, K>::size()
{
	return n;
}

template <typename T, typename K> void Hashtable<T, K>::add(T* value, K key)
{
	if (E[(*hashCode)(key, N)].add(new Entry<T, K>(key, value)) && (++n > N >> 1)) resize(1);
}

template <typename T, typename K> void Hashtable<T, K>::add(Entry<T, K> *e)
{
	E[(*hashCode)(e->key, N)].add(e);
}

template <typename T, typename K> void Hashtable<T, K>::del(K key)
{
	if (E[(*hashCode)(key, N)].del(key) && (--n < N >> 2)) resize(-1);
}

template <typename T, typename K> T *Hashtable<T, K>::find(K key)
{
	Entry<T, K> *e = E[(*hashCode)(key, N)].find(key);
	return e != nullptr ? e->value : nullptr;
}

template <typename T, typename K> void Hashtable<T, K>::resize(int f)
{
	int pN = N;
	KeyList<T, K> *pE = E;

	N <<= f;
	E = new KeyList<T, K>[N];
	for (int i = 0; i<pN; i++)
	{
		E[i] = KeyList<T, K>();
	}

	KeyList<T, K> *cL = pE;
	while(pN--)
	{
		while (!cL->isEmpty())
		{
			add(cL->pop());
		}
		cL++;
	}

	delete[] pE;
}

template <typename T, typename K> float Hashtable<T, K>::mls()
{
	int m = 0;
	int nb = 0;

	for (int i = 0; i < N; i++)
	{
		if (E[i].n != 0)
		{
			m += E[i].n+1;
			nb++;
		}
	}
	return ((float)m / (float)nb / 2);
}

template class Hashtable<struct Vertex, unsigned int>;