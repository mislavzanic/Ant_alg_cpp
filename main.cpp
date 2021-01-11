#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/CLionProjects/mhRad/assets/m2.bmp");
    AntAlg a(m, 10, 4, 0.7f);
    std::map<int, int> solution = a.solve(30);
    m.modifyImage(solution, {123, 64, 200}, "ant.bmp");
    solution = BFS(m);
    m.modifyImage(solution, {0, 0, 255}, "bfs.bmp");
    return 0;
}
