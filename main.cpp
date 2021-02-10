#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp");
    AntColonyMaze a(m, 20, 6, 0.5f, 1.0f);
    SimulatedAnnealing s(m, 60);

    StopWatch sw;
    Maze::MazePath<int> BFSsolution = BFS(m);
    auto timeBFS = sw.getElapsedTime();
    m.modifyImage(BFSsolution.parentMap, {48, 34, 213}, "bfs.bmp");
    std::cout << "BFS time: " << timeBFS.count() << ", bfs len:" << BFSsolution.length << std::endl;

    SimAnnGraph sg(m, 200);
    sw.reset();
    auto solSimAnnGraph = sg.shortestPath();
    auto tt = sw.getElapsedTime();
    std::cout << tt.count() << " " << solSimAnnGraph.length << std::endl;
    return 0;
}
