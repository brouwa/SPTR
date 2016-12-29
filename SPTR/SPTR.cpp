// SPTR.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include "math.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc == 1) return 255;
	const char * rfile = argv[1],
		*pfile = "points.js";
	
	
	RoadNetwork *rn = new RoadNetwork;
	rn->readfromfile(rfile, (float)48.848096, (float)2.344330);
	Vertex *sr = rn->select_vertex_id(470134);
	if (sr != nullptr)
	{
		rn->Dijkstra2(sr);
		//rn->printroadto(rn->select_vertex_rand(), pfile);
		rn->printinfile2(pfile);
		std::cout << "Done!" << endl;
	}
	delete rn;

	system("PAUSE");
	return EXIT_SUCCESS;
}


