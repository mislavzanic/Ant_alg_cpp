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

        int heuristics(const std::pair<int, int>& cell) const 
        { 
            return mMaze.width() + mMaze.height() - std::abs(cell.first - mMaze.end().first) + std::abs(cell.second - mMaze.end().second); 
        }

        int heuristics(int num) const 
        {
            std::pair<int, int> a = mMaze.intToPair(num);
            return heuristics(a);
        }

    private:
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap);
        void createInitialSolution();
        void simulatedAnnealing();

    private:
        Maze mMaze;

        double mCurrentTemp;
        double mFinalTemp;
        double mStep;

        std::map<int, int> mSolution;
        std::pair<int, int> mGoal;
    };
}


#endif //MHRAD_SIMANN_H
