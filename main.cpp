#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/pmf/CLionProjects/mhRad/assets/braid2.bmp");
    AntColonyMaze a(m, 10, 3, 0.5f, 1.0f);
    SimulatedAnnealing s(m, 60);

    //for (auto v : g.mGraph)
    //{
    //    std::cout << v.first << " ";
    //    for (auto vv : v.second)
    //    {
    //        std::cout << vv.first << " ";
    //    }
    //    std::cout << std::endl;
    //}

    StopWatch sw;
    Maze::MazePath<int> BFSsolution = BFS(m);
    auto timeBFS = sw.getElapsedTime();
    m.modifyImage(BFSsolution.parentMap, {48, 34, 213}, "bfs.bmp");
    std::cout << "BFS time: " << timeBFS.count() << ", bfs len:" << BFSsolution.length << std::endl;

    AntColonyGraph ag(m, 20, 6, 0.5f, 1.0f);
    sw.reset();
    auto solutionAntGraph = ag.solve(15);
    auto tt = sw.getElapsedTime();
    std::cout << tt.count() << " " << solutionAntGraph.length << std::endl;
    sw.reset();

    //Maze::MazePath<int> solution = a.shortestPathMaze(15);
    auto timeAnt = sw.getElapsedTime();

    sw.reset();
    //Maze::MazePath<int> longestSim = s.longestPath();
    auto timeLongestSim = sw.getElapsedTime();

    sw.reset();
    //Maze::MazePath<int> shortestSim = s.shortestPath();
    auto timeShortestSim = sw.getElapsedTime();

    sw.reset();
    Maze::MazePath<int> DFSsolution = DFS(m);
    auto timeDFS = sw.getElapsedTime();

    //m.modifyImage(solution.parentMap, {183, 64, 20}, "ant.bmp");
    //m.modifyImage(longestSim.parentMap, {23, 164, 20}, "simanLongest.bmp");
    //m.modifyImage(shortestSim.parentMap, {23, 164, 20}, "simanShortest.bmp");
    m.modifyImage(DFSsolution.parentMap, {200, 34, 213}, "dfs.bmp");
    //std::cout << "Ant time: " << timeAnt.count() << ", ant len:" << solution.length << std::endl;
    //std::cout << "Sim shortest time: " << timeShortestSim.count() << ", sim len:" << shortestSim.length << std::endl;
    //std::cout << "Sim longest time: " << timeLongestSim.count() << ", sim len:" << longestSim.length << std::endl;
    std::cout << "DFS time: " << timeDFS.count() << ", bfs len:" << DFSsolution.length << std::endl;

    return 0;
}
