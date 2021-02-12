#include <iostream>
#include "Project.h"

using namespace mh;

int main()
{
    AntColonyGraph ag("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", 20, 6, 0.5f, 1.0f);
    SimAnnGraph sg("/home/mislav/pmf/CLionProjects/mhRad/assets/braid1.bmp", 200);
    StopWatch sw;
    auto path = ag.solve(15);
    auto time = sw.getElapsedTime();
    std::cout << path.length << " " << time.count() << std::endl;

    sw.reset();
    path = sg.solve();
    time = sw.getElapsedTime();
    std::cout << path.length << " " << time.count() << std::endl;

    return 0;
}
