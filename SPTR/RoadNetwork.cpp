#include "stdafx.h"
#include "RoadNetwork.h"
#include "KeyList.h"
#include<time.h>

//RoadNetwork::~RoadNetwork()
//{
//}
using namespace std;

int RoadNetwork::interpolation(int c1, int c2, int t1, int t2, int targetTime)
{
	float vitesse = (c2 - c1) / (t2 - t1);
	float expectedPoint = c1 + vitesse * (targetTime - t1);
	return int(expectedPoint);
}


void RoadNetwork::addV(unsigned int id, int lat, int lon)
{
	ht.add(new Vertex(id, lat, lon), id);
	n++;
}

bool RoadNetwork::addA(unsigned int frid, unsigned int toid, int t)
{
	Vertex *fr = ht.find(frid);
	if (fr == nullptr) return false;
	Vertex *to = ht.find(toid);
	if (to == nullptr) return false;
	fr->neighbors = new Chain<Arc>({ to, t }, fr->neighbors);
	m++;
	return true;
}

void RoadNetwork::Dijkstra(Vertex *sr)
{
	double temps;
	clock_t start;

	bool keepDijkstraGoing = true;

	sr->t = 0;
	sr->computed = true;

	FibonacciHeap<struct Vertex> fh;

	KeyList<Vertex, unsigned int> *E = ht.E;
	for (int N = ht.N; N-- ; E++)
	{
		for (Chain<struct Entry<Vertex, unsigned int>*> *c = E->first; c!= nullptr; c=c->next)
		{
			Vertex *u = c->var->value;
			if (u != sr) { u->t = INT_MAX;	u->computed = false; }
			fh.add(u, u->t);
		}
	}

	cout << "Debut du Dijkstra..." << endl;
	start = clock();

	fh.generate_nodedeg();
	int n = 0;
	while (!fh.isEmpty() && keepDijkstraGoing)
	{
		Vertex *u = fh.ext_min(ht);
		// Si on est déjà en dehors du cadre de nos recherches, on peut stopper l'exploration
		if (u->t > 2 * 3600 * 1000 + 120000)	keepDijkstraGoing = false;
		u->computed = true;
 		Chain<Arc> *c = u->neighbors;
		if (u->t != INT_MAX)
		{
			while (c != nullptr)
			{
				if (!c->var.to->computed)
				{
					int tu = u->t + c->var.t;
					Vertex *v = c->var.to;
					if (tu < v->t)
					{
						v->t = tu;
						fh.set_pr(v, tu);
					}
				}
				c = c->next;
			}
		}
	}

	temps = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Dijkstra termine, en ";
	cout << temps;
	cout << " secondes" << endl;

	cout << "Export des points d'interet..." << endl;
	start = clock();
	////...
	ofstream myfile;
	myfile.open("C:\\Users\\Benoît\\Desktop\\RoadNetworks\\vis\\points.js");
	myfile << endl << "var plottedPoints = [" << endl;
	E = ht.E;
	for (int N = ht.N; N--; E++)
	{
		for (Chain<struct Entry<Vertex, unsigned int>*> *c = E->first; c != nullptr; c = c->next)
		{
			Vertex *u = c->var->value;
			//cout << u->id << ":" << u->t << endl;
			if (2 * 3600 * 1000 - 120000 < u->t && u->t <2 * 3600 * 1000 + 120000)
			{
				myfile << "\t[" << (float)u->lon / 1000000 << "," <<  (float)u->lat / 1000000  << "]," << endl;
			}
			
		}
	}
	myfile << "];" << endl;
	myfile << endl << "var centralMarker =" << endl;
	myfile << "\t[" << (float)sr->lon / 1000000 << "," << (float)sr->lat / 1000000 << "]" << endl;
	myfile << ";" << endl;
	myfile.close();

	temps = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Export termine, en ";
	cout << temps;
	cout << " secondes" << endl;
}

void RoadNetwork::Dijkstra2(Vertex *sr)
{
	double temps;
	clock_t start;
	int targetTime = 3600*1000*2;

	sr->t = 0;
	sr->computed = true;

	FibonacciHeap<struct Vertex> fh;

	KeyList<Vertex, unsigned int> *E = ht.E;
	for (int N = ht.N; N--; E++)
	{
		for (Chain<struct Entry<Vertex, unsigned int>*> *c = E->first; c != nullptr; c = c->next)
		{
			Vertex *u = c->var->value;
			if (u != sr) { u->t = INT_MAX;	u->computed = false; }
			fh.add(u, u->t);
		}
	}

	cout << "Debut du Dijkstra..." << endl;
	start = clock();

	fh.generate_nodedeg();
	int n = 0;
	while (!fh.isEmpty())
	{
		Vertex *u = fh.ext_min(ht);
		u->computed = true;
		Chain<Arc> *c = u->neighbors;
		if (u->t != INT_MAX)
		{
			while (c != nullptr)
			{
				if (!c->var.to->computed)
				{
					int tu = u->t + c->var.t;
					Vertex *v = c->var.to;
					if (tu < v->t)
					{
						v->t = tu;
						fh.set_pr(v, tu);

						if(u->t < targetTime && v->t >= targetTime)
						{
							v->interpoledIsochrone = true;

							v->interpoledIsochroneLat = interpolation(u->lat, v->lat, u->t, v->t, targetTime);
							v->interpoledIsochroneLon = interpolation(u->lon, v->lon, u->t, v->t, targetTime);
						}
						else
						{
							v->interpoledIsochrone = false;
						}

					}
				}
				c = c->next;
			}
		}
	}

	temps = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Dijkstra termine, en ";
	cout << temps;
	cout << " secondes" << endl;

	cout << "Export des points d'interet..." << endl;
	start = clock();
	////...
	ofstream myfile;
	myfile.open("C:\\Users\\Benoît\\Desktop\\RoadNetworks\\vis\\points.js");
	myfile << endl << "var plottedPoints = [" << endl;
	E = ht.E;
	for (int N = ht.N; N--; E++)
	{
		for (Chain<struct Entry<Vertex, unsigned int>*> *c = E->first; c != nullptr; c = c->next)
		{
			Vertex *u = c->var->value;
			if (u->interpoledIsochrone)
			{
				myfile << "\t[" << (float)u->interpoledIsochroneLon / 1000000 << "," << (float)u->interpoledIsochroneLat / 1000000 << "]," << endl;
			}

		}
	}
	myfile << "];" << endl;
	myfile << endl << "var centralMarker =" << endl;
	myfile << "\t[" << (float)sr->lon / 1000000 << "," << (float)sr->lat / 1000000 << "]" << endl;
	myfile << ";" << endl;
	myfile.close();

	temps = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Export termine, en ";
	cout << temps;
	cout << " secondes" << endl;
}


int RoadNetwork::hashCode(unsigned int n, int N)
{
	return n%N;
}

Vertex *RoadNetwork::select_first()
{
	KeyList<Vertex, unsigned int> *L = ht.E;
	while (!L->n) L++;
	return L->first->var->value;
}


Vertex *RoadNetwork::select_vertex_coords(unsigned int lat,unsigned int lon)
{
	KeyList<Vertex, unsigned int> *E = ht.E;
	for (int N = ht.N; N--; E++)
	{
		for (Chain<struct Entry<Vertex, unsigned int>*> *c = E->first; c != nullptr; c = c->next)
		{
			Vertex *u = c->var->value;
			//cout << u->id << ":" << u->t << endl;
			if ( u->lat == lat && u->lon == lon)
			{
				return u;
			}

		}
	}
	return nullptr;

}

Vertex *RoadNetwork::select_vertex_id(unsigned int id)
{
	KeyList<Vertex, unsigned int> *E = ht.E;
	for (int N = ht.N; N--; E++)
	{
		for (Chain<struct Entry<Vertex, unsigned int>*> *c = E->first; c != nullptr; c = c->next)
		{
			Vertex *u = c->var->value;
			//cout << u->id << ":" << u->t << endl;
			if (u->id == id)
			{
				return u;
			}

		}
	}
	return nullptr;

}