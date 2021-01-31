#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/pmf/CLionProjects/mhRad/assets/braid2.bmp");
    AntColony a(m, 20, 7, 0.7f, 1.0f);
    SimulatedAnnealing s(m, 60);
    StopWatch sw;
    Maze::MazePath<int> solution = a.solve(15);
    auto timeAnt = sw.getElapsedTime();
    sw.reset();
    Maze::MazePath<int> longestSim = s.longestPath();
    auto timeLongestSim = sw.getElapsedTime();
    sw.reset();
    Maze::MazePath<int> shortestSim = s.shortestPath();
    auto timeShortestSim = sw.getElapsedTime();
    m.modifyImage(solution.parentMap, {183, 64, 20}, "ant.bmp");
    m.modifyImage(longestSim.parentMap, {23, 164, 20}, "simanLongest.bmp");
    m.modifyImage(shortestSim.parentMap, {23, 164, 20}, "simanShortest.bmp");
    sw.reset();
    Maze::MazePath<int> BFSsolution = BFS(m);
    auto timeBFS = sw.getElapsedTime();
    sw.reset();
    Maze::MazePath<int> DFSsolution = DFS(m);
    auto timeDFS = sw.getElapsedTime();
    m.modifyImage(BFSsolution.parentMap, {48, 34, 213}, "bfs.bmp");
    m.modifyImage(DFSsolution.parentMap, {200, 34, 213}, "dfs.bmp");
    std::cout << "Ant time: " << timeAnt.count() << ", ant len:" << solution.length << std::endl;
    std::cout << "Sim shortest time: " << timeShortestSim.count() << ", sim len:" << shortestSim.length << std::endl;
    std::cout << "Sim longest time: " << timeLongestSim.count() << ", sim len:" << longestSim.length << std::endl;
    std::cout << "BFS time: " << timeBFS.count() << ", bfs len:" << BFSsolution.length << std::endl;
    std::cout << "DFS time: " << timeDFS.count() << ", bfs len:" << DFSsolution.length << std::endl;
    return 0;
}
