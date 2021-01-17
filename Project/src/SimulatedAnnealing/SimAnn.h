//
// Created by mislav on 12/26/20.
//

#ifndef MHRAD_SIMANN_H
#define MHRAD_SIMANN_H

#include "Maze/Maze.h"
#include "util/Random.h"
#include <vector>
#include <map>
#include <stack>


namespace mh {

    class SimAnn
    {
    public:
        SimAnn(const std::string& filepath, double minTemp, double maxTemp, double step);
        SimAnn(const Maze& m, double minTemp, double maxTemp, double step);
        SimAnn(Maze&& m, double minTemp, double maxTemp, double step);
        std::map<int, int> solve();
        int heuristics(const std::pair<int, int>& a, const std::pair<int, int>& b) const {return abs(a.first - b.first) + abs(a.second - b.second); }

    private:
        int pickRandom(std::pair<int, int> cell);

    private:
        Maze mMaze;

        double mCurrentTemp;
        double mFinalTemp;
        double mStep;

        std::pair<int, int> mSolution;
        std::pair<int, int> mGoal;

        std::map<int, int> mPath;
    };
}


#endif //MHRAD_SIMANN_H
