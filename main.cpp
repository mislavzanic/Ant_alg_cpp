#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    MatrixMaze m("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp");
    auto path = BFS(m);
    int a = 0;
    for (auto x : path.vertices)
    {
        a++;
    }
    writeImage("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", "a.bmp", {0, 0, 200}, m.getParentMap(path));
    std::cout << a << std::endl;

    return 0;
}
