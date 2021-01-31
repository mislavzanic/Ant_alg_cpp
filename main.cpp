#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/pmf/CLionProjects/mhRad/assets/m2.bmp");
    AntColony a(m, 20, 7, 0.7f, 1.0f);
    SimulatedAnnealing s(m, 60);
    StopWatch sw;
    Maze::MazePath<int> solution = a.solve(15);
    auto timeAnt = sw.getElapsedTime();
    sw.reset();
    Maze::MazePath<int> solutionSim = s.solve();
    auto time_sim = sw.getElapsedTime();
    m.modifyImage(solution.parentMap, {183, 64, 20}, "ant.bmp");
    m.modifyImage(solutionSim.parentMap, {23, 164, 20}, "siman.bmp");
    sw.reset();
    Maze::MazePath<int> BFSsolution = BFS(m);
    auto timeBFS = sw.getElapsedTime();
    m.modifyImage(BFSsolution.parentMap, {48, 34, 213}, "bfs.bmp");
    std::cout << "Ant time: " << timeAnt.count() << ", ant len:" << solution.length << std::endl;
    std::cout << "Sim time: " << time_sim.count() << ", sim len:" << solutionSim.length << std::endl; 
    std::cout << "BFS time: " << timeBFS.count() << ", bfs len:" << BFSsolution.length << std::endl;
    return 0;
}
