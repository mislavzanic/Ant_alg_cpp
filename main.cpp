#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/pmf/CLionProjects/mhRad/assets/segment1.bmp");
    //AntAlg a(m, 10, 4, 0.7f, 1.3f);
    SimAnn s(m, 0.0f, 20.0f, 0.9f);
    StopWatch sw;
    //std::map<int, int> solution = a.solve(10);
    auto timeAnt = sw.getElapsedTime();
    std::map<int, int> solutionSim = s.solve();
    //m.modifyImage(solution, {123, 64, 200}, "ant.bmp");
    m.modifyImage(solutionSim, {123, 64, 200}, "siman.bmp");
    sw.reset();
    std::map<int, int> BFSsolution = BFS(m);
    auto timeBFS = sw.getElapsedTime();
    m.modifyImage(BFSsolution, {0, 0, 255}, "bfs.bmp");
    //std::cout << "Ant: " << timeAnt.count() << ", BFS: " << timeBFS.count() << std::endl;
    return 0;
}
