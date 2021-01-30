#ifndef MHRAD_SIMANN_H
#define MHRAD_SIMANN_H

#include "Maze/Maze.h"
#include "util/Random.h"
#include <vector>
#include <map>
#include <stack>


namespace mh {

    class SimulatedAnnealing
    {
    public:
        SimulatedAnnealing(const std::string& filepath, int maxIter);
        SimulatedAnnealing(const Maze& m, int maxIter);
        SimulatedAnnealing(Maze&& m, int maxIter);
        Maze::MazePath<int> solve();

    private:
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap);
        void pickRandom(int cell, std::queue<int>& toVisit, std::map<int, int>& parentMap);
        void createInitialSolution();
        void simAnn();

        static double temperature(double t) { return std::exp(-t); }

        int heuristics(const std::pair<int, int>& cell) const 
        { 
            return mMaze.width() + mMaze.height() - std::abs(cell.first - mMaze.end().first) + std::abs(cell.second - mMaze.end().second);
        }
        
        int heuristics(int num) const 
        {
            std::pair<int, int> a = mMaze.intToPair(num);
            return heuristics(a);
        }

        int heuristics(const Maze::MazePath<int>& state) const
        {
            return mMaze.width() * mMaze.height() - state.length;
        }

        Maze::MazePath<int> getNeighbor(Maze::MazePath<int>& state);
        bool findPath(int intersection, Maze::MazePath<int>& newPath, Maze::MazePath<int>& currentPath);

    private:
        Maze mMaze;

        int mMaxIter;
        double mStep;

        Maze::MazePath<int> mSolution;
        std::pair<int, int> mGoal;
    };
}

#endif //MHRAD_SIMANN_H