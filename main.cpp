#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    AntColonyGraph ag("/home/mislav/pmf/CLionProjects/mhRad/assets/m2.bmp", 20, 6, 0.5f, 1.0f);
    SimAnnGraph sg("/home/mislav/pmf/CLionProjects/mhRad/assets/m2.bmp", 60);
    std::unique_ptr<MazeInterface> g = std::make_unique<Graph>("/home/mislav/pmf/CLionProjects/mhRad/assets/m2.bmp");
    StopWatch sw;
    auto path = ag.solve(15);
    auto time = sw.getElapsedTime();
    std::cout << path.length << " " << time.count() << std::endl;



    /*
    int current = *path.vertices.begin();
    int end = path.parentMap[current];
    int length = path.edgeLengthMap[end];
    std::stack<std::pair<int, int>> S;
    S.push({current,0 });
    while (!S.empty())
    {

    }
    */
    sw.reset();
    path = sg.solve();
    time = sw.getElapsedTime();
    std::cout << path.length << " " << time.count() << std::endl;

    writeImage("/home/mislav/pmf/CLionProjects/mhRad/assets/m2.bmp", "test.bmp", {200, 39, 56}, g->getParentMap(path));
    return 0;
}
