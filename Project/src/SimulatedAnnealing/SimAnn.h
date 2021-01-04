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
        void solve();

    private:
        std::pair<int, int> pickRandom(int cell);

    private:
        Maze mMaze;
        double mCurrentTemp;
        double mStep;
        std::pair<int, int> mSolution;
        std::pair<int, int> mGoal;
        std::pair<int, int> mCurrentState;
        double mFinalTemp;

        Random<std::mt19937> mRandEngine;
    };
}


#endif //MHRAD_SIMANN_H
