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
        Maze::MazePath<int> shortestPath();
        Maze::MazePath<int> longestPath();

    private:

        template<typename Heuristics>
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap, Heuristics h);

        template<typename Heuristics>
        void createInitialSolution(Heuristics h);

        template<typename Heuristics>
        void simAnn(Heuristics h);

        static double temperature(double t) { return std::exp(-t); }

        Maze::MazePath<int> getNeighbor(Maze::MazePath<int>& state);
        bool findPath(int intersection, Maze::MazePath<int>& newPath, Maze::MazePath<int>& currentPath);

    private:
        Maze mMaze;

        int mMaxIter;

        Maze::MazePath<int> mSolution;
        std::pair<int, int> mGoal;
    };
}

#endif //MHRAD_SIMANN_H