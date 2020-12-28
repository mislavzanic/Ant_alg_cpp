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
        void initialSolution(std::map<int, int> &path);
        int getNeighbourPath(std::vector<int>& path);
        int pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& path);

    private:
        Maze mMaze;
        double mCurrentTemp;
        double mStep;
        int mSolution;
        std::vector<int> mPath;
        double mFinalTemp;

        Random<std::mt19937> mRandEngine;
    };
}


#endif //MHRAD_SIMANN_H
