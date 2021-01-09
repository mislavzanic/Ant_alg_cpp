#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/CLionProjects/mhRad/assets/m2.bmp");
    AntAlg a(m, 10, 3, 0.1f);
    std::map<int, int> solution = a.solve(20);
    m.modifyImage(solution);
    return 0;
}
