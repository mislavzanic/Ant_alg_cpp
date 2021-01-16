#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/CLionProjects/mhRad/assets/m2.bmp");
    AntAlg a(m, 10, 4, 0.7f, 1.3f);
    //SimAnn s(m, 0.0f, 20.0f, 0.9f);
    std::map<int, int> solution = a.solve(30);
    //std::map<int, int> solutionSim = s.solve();
    m.modifyImage(solution, {123, 64, 200}, "ant.bmp");
    //m.modifyImage(solutionSim, {123, 64, 200}, "siman.bmp");
    solution = BFS(m);
    m.modifyImage(solution, {0, 0, 255}, "bfs.bmp");
    return 0;
}
