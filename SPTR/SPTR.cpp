// SPTR.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include "RoadNetwork.h"
#include "Hashtable.h"
#include<time.h>

using namespace std;


int hashCode(std::string mystr, int N);
int hashCodeui(unsigned int n, int N);

int main()
{

	RoadNetwork rn;
	Vertex *source;

	ifstream myfile;
	myfile.open("C:\\Users\\Benoît\\Desktop\\RoadNetworks\\data\\france.in");
	
	unsigned id;
	int lat, lon;
	unsigned int p1, p2;
	int t;

	double temps;
	clock_t start;

	cout << "Lecture du fichier de donnees..." << endl;
	start = clock();
	if (myfile.is_open())
	{
		do
		{
			switch (myfile.get())
			{
			case 'v':
				myfile >> id >> lat >> lon;
				rn.addV(id, lat, lon);
				break;
			case 'a':
				myfile >> p1 >> p2 >> t;
				rn.addA(p1, p2, t);
				break;
			}
			myfile.get();
		} while (!myfile.eof());
	}
	myfile.close();

	temps = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Lecture terminee, en ";
	cout << temps;
	cout << " secondes" << endl;

	
	//rn.Dijkstra(rn.select_first());
	// france rn.Dijkstra(rn.select_vertex(2363100, 48842841));
	// malte source = rn.select_vertex_coords(14288652, 36023845);
	source = rn.select_vertex_id(1760418226);
	if (source == nullptr)	source = rn.select_first();

	rn.Dijkstra(source);


	system("PAUSE");
	return EXIT_SUCCESS;
}

int hashCode(std::string mystr, int N)
{
	int h = 0;
	int n = mystr.size();
	while (--n) h = (h + (mystr)[n]) % N;
	return h;
}

int hashCodeui(unsigned int n, int N)
{
	return n%N;
}


