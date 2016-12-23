#pragma once

#include "Chain.h"
#include "DLChain.h"
#include "Hashtable.h"
#include "FibonacciHeap.h"

struct Vertex
{
	unsigned int id;
	int lat, lon;

	int t;
	bool computed;
	Chain<struct Arc> *neighbors;
	DLChain<Vertex*> *me;
	DLChain<Vertex*> *FHfather;
	DLChain<Vertex*> *FHchilds;
	int deg;
	bool marked;

	// Rajout par moi, pour obtenir l'isochrone par interpolation :
	bool interpoledIsochrone;
	int interpoledIsochroneLat;
	int interpoledIsochroneLon;


	Vertex(int id, int lat, int lon) : id(id), lat(lat), lon(lon), computed(false), neighbors(nullptr), FHfather(nullptr), FHchilds(nullptr), deg(0), marked(false), me(nullptr), interpoledIsochrone(false), interpoledIsochroneLat(0), interpoledIsochroneLon(0) {}
	Vertex() {}
};

struct Arc
{
	Vertex *to;
	int t;

	Arc(Vertex *to, int t) : to(to), t(t) {};
};

class RoadNetwork
{
public:
	int n, m;
	RoadNetwork() : n(0), m(0), ht(&hashCode, 1024) { };
	//~RoadNetwork();
	void addV(unsigned int id, int lat, int lon);
	bool addA(unsigned int frid, unsigned int toid, int t);
	int interpolation(int c1,int c2,int t1,int t2,int targetTime);
	void Dijkstra(Vertex *v);
	void Dijkstra2(Vertex *v);
	Vertex *select_first();
	Vertex *select_vertex_coords(unsigned int lat, unsigned int lon);
	Vertex *select_vertex_id(unsigned int id);
private:
	Hashtable<Vertex, unsigned int> ht;
	static int hashCode(unsigned int n, int N);
};

