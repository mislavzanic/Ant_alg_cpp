#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/CLionProjects/mhRad/assets/m2.bmp");
    AntAlg a(m, 15, 5, 0.3f);
    std::map<int, int> solution = a.solve(30);
    m.modifyImage(solution);
    return 0;
}
