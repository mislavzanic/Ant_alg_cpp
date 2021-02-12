#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    /*
    Maze m("/home/mislav/pmf/CLionProjects/mhRad/assets/braid4.bmp");
    AntColonyMaze a(m, 20, 6, 0.5f, 1.0f);
    SimulatedAnnealing s(m, 60);

    StopWatch sw;
    Maze::MazePath<int> BFSsolution = BFS(m);
    auto timeBFS = sw.getElapsedTime();
    m.modifyImage(BFSsolution.parentMap, {48, 34, 213}, "bfs.bmp");
    std::cout << "BFS time: " << timeBFS.count() << ", bfs len:" << BFSsolution.length << std::endl;

    sw.reset();
    SimAnnGraph sg(m, 200);
    auto solSimAnnGraph = sg.shortestPath();
    auto tt = sw.getElapsedTime();
    std::cout << tt.count() << " " << solSimAnnGraph.length << std::endl;

    sw.reset();
    AntColonyGraph ag(m, 20, 6, 0.5f, 1.0f);
    auto solAntColonyGraph = ag.solve(15);
    tt = sw.getElapsedTime();
    std::cout << tt.count() << " " << solAntColonyGraph.length << std::endl;
    */
    return 0;
}
