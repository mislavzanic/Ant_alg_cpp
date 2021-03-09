#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    AntColonyGraph ag("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", 20, 6, 0.5f, 1.0f);
    SimAnnGraph sg("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", 60);
    std::unique_ptr<MazeInterface> g = std::make_unique<Graph>("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp");
    StopWatch sw;
    auto path = ag.solve(15);
    auto time = sw.getElapsedTime();
    std::cout << path.length << " " << time.count() << std::endl;
    writeImage("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", "ant.bmp", {200, 39, 56}, g->getParentMap(path));

    sw.reset();
    path = sg.solve();
    time = sw.getElapsedTime();
    std::cout << path.length << " " << time.count() << std::endl;
    writeImage("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", "simann.bmp", {30, 200, 56}, g->getParentMap(path));

    sw.reset();
    path = BFS(*g);
    writeImage("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", "bfs.bmp", {50, 20, 200}, g->getParentMap(path));
    return 0;
}
