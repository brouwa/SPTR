#include "stdafx.h"
#include "FibonacciHeap.h"


template <typename T> FibonacciHeap<T>::~FibonacciHeap()
{
	if (nodeDeg != nullptr) delete[] nodeDeg;
	if (nodes != nullptr) clean(nodes);
}

template <typename T> void FibonacciHeap<T>::clean(FHChain<T*> *d)
{
	FHChain<T*> *c = d;
	do
	{
		if (c->childs != nullptr)clean(c->childs);
		c = c->next;
	} while (c != d);
	delete d;
}

template <typename T> void FibonacciHeap<T>::add(T* el, int p)
{
	el->t = p;
	if (nodes == nullptr) 
	{
		el->myFHc = new FHChain<T*>(el);
		nodes = el->myFHc;
		nodes->prev = nodes;
		nodes->next = nodes;

		minnode = nodes;
	}
	else
	{
		el->myFHc = new FHChain<T*>(el, nodes->prev, nodes);
		nodes->prev->next = el->myFHc;
		nodes->prev = el->myFHc;

		if (el->t < minnode->v->t) minnode = el->myFHc;
	}
	n++;
	nbnodes++;
}

template <typename T> void FibonacciHeap<T>::generate_nodeDeg(int size)
{
	maxnodesnb = (int)(log(sqrt(5)*size) / log(phi));
	if (nodeDeg != nullptr) delete[] nodeDeg;
	nodeDeg = new FHChain<T*>*[maxnodesnb];
	for (int i = 0; i < maxnodesnb; i++) nodeDeg[i] = nullptr;
}

template <typename T> bool FibonacciHeap<T>::isEmpty()
{
	return nodes == nullptr;
}



template<> Vertex *FibonacciHeap<struct Vertex>::ext_min()
{
	//Save
	FHChain<struct Vertex*> *cmin = minnode;
	Vertex *vmin = minnode->v;

	//Add min childs
	minnode->unlink(nodes);
	nbnodes--;
	n--;

	FHChain<struct Vertex*> *d = minnode->childs, *c = d;
	if (d != nullptr)
	{
		do
		{
			nbnodes++; c->father = nullptr;
			c = c->next;
		} while (c != d);
	}

	if (minnode->childs != nullptr) minnode->childs->insertaslist(nodes);

	//Clean (unique degree)
	minnode = nodes;
	int nbnodes_pr = nbnodes;
	FHChain<struct Vertex*> *next;
	for (FHChain<struct Vertex*> *c = nodes; nbnodes_pr--; c = next)
	{
 		if (c->v->t < minnode->v->t)
			minnode = c;

		next = c->next;

		while (nodeDeg[c->deg] != nullptr) 
		{
			FHChain<struct Vertex*> *cd = nodeDeg[c->deg];
			
			//cd de plus petite value
			if (cd->v->t > c->v->t)
			{
				nodeDeg[c->deg] = c;
				c = cd;
				cd = nodeDeg[c->deg];
			}
			if (minnode == c) minnode = cd;

			//déref
			nodeDeg[c->deg] = nullptr;

			c->unlink(nodes);
			c->insert(cd->childs);
			c->father = cd;
			c->marked = false;
			cd->deg++;

			nbnodes--;
			c = cd;
		}
		nodeDeg[c->deg] = c;
	}

	//Clean nodeDeg
	nbnodes_pr = nbnodes;
	for (FHChain<struct Vertex*> *c = nodes; nbnodes_pr--; c = c->next)	nodeDeg[c->deg] = nullptr;

	delete cmin;
	return vmin;
}

template<> void FibonacciHeap<struct Vertex>::set_pr(Vertex *el, int p)
{
	el->t = p;

	FHChain<struct Vertex*> *cel = el->myFHc;
	if (el->t < minnode->v->t) minnode = cel;

	if (cel->father != nullptr && cel->father->v->t > el->t)
	{
		FHChain<struct Vertex*> *f;

		do
		{
			cel->marked = false;
			cel->unlink(cel->father->childs);
			cel->insert(nodes);
			nbnodes++;
			f = cel->father;
			cel->father = nullptr;
			if (f->deg == cel->deg+1) f->deg--;

			if (!f->marked) { f->marked = true; break; };

			el = f->v;
		} while (cel->father != nullptr);
	}
}

template<> void FibonacciHeap<struct Vertex>::print(FHChain<struct Vertex*> *d, int i)
{
	if (d == nullptr) return;
	FHChain<struct Vertex*> *c = d;
	do
	{
		for (int k = i; k; k--)  std::cout << '\t';
		std::cout << c->v->id << ":" << c->v->t << std::endl;
		print(c->childs, i + 1);
	} while ((c = c->next) != d);


}

template<> void FibonacciHeap<struct Vertex>::print()
{
	print(nodes, 0);
	std::cout << std::endl;
	system("PAUSE");
}

template class FibonacciHeap<struct Vertex>;