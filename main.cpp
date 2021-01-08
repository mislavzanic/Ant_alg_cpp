#include "Project.h"

using namespace mh;

int main()
{
    Maze m("/home/mislav/CLionProjects/mhRad/assets/m1.bmp");
    AntAlg a(m, 10, 3, 0.1f);
    std::map<int, int> solution = a.solve(20);
    return 0;
}
