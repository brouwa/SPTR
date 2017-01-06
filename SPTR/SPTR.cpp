// SPTR.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include "math.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc == 1) return 255;
	const char * rfile = argv[1],	// Input data file
		*pfile = "points.js";		// Output file
	
	RoadNetwork *rn = new RoadNetwork;

	// targetTime is the time we want to draw the isochrone with. Defalut value : 1 hour
	rn->targetTime = 3600 * 1000;
	// If III is true, then we only look for points at exactly targetTime from the source,
	// but are on a way to reach a point at more than targetTimeHigh (question I3)
	// Default values : 2 hours and false
	rn->targetTimeHigh = 2 * 3600 * 1000;
	rn->III = false;

	// Starting point
	Vertex *sr;
	// Starting point Id (by default in the center of Paris)
	unsigned int id = 470134;
	// Do we select a starting point at random ?
	bool randomStart = false;

	/*
	Reading the options :
	-t1 n : sets targetTime value on n
	-t2 n : sets targetTimeHigh value on n
	-III : sets III value on true
	-startId n : sets the starting point id on n
	-randomStart : choose a random starting point
	*/
	for (int i = 2; i < argc; i++)
	{
		if(!strcmp(argv[i] , "-t1"))
		{
			rn->targetTime = stoi(argv[i + 1]);
			i++;
		}

		if (!strcmp(argv[i], "-t2"))
		{
			rn->targetTimeHigh = stoi(argv[i + 1]);
			i++;
		}

		if (!strcmp(argv[i], "-III"))
		{
			rn->III = true;
		}

		if (!strcmp(argv[i], "-startId n"))
		{
			id = stoi(argv[i + 1]);
			i++;
		}
		if (!strcmp(argv[i], "-randomStart"))
		{
			randomStart = true;
			std::cout << "Test" << endl;
		}
	}

	rn->readfromfile(rfile, (float)48.848096, (float)2.344330);

	// Choice of the starting point
	if(randomStart)
		sr = rn->select_vertex_rand();
	else
		sr = rn->select_vertex_id(id);
	if (sr != nullptr)
	{
		rn->Dijkstra(sr);
		// We can also trace the route to a specified point (here : random) with :
		//rn->printroadto(rn->select_vertex_rand(), pfile);
		rn->printinfile(pfile);
		std::cout << "Done!" << endl;
	}
	else
		std::cout << "Incorrect starting point" << endl;
	delete rn;

	system("PAUSE");
	return EXIT_SUCCESS;
}


