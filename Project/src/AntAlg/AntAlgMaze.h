#ifndef MHRAD_ANTALGMAZE_H
#define MHRAD_ANTALGMAZE_H

#include "Maze/MatrixMaze.h"
#include "util/Random.h"

#include <vector>
#include <stack>
#include <utility>
#include <set>
#include <cmath>
#include <map>


namespace mh {
    class AntColonyMaze
    {
    public:
        AntColonyMaze(const std::string& filepath, int numOfAnts, int subsetLen, double p, double startPheromones);
        AntColonyMaze(const Maze& maze, int numOfAnts, int subsetLen, double p, double startPheromones);

        Maze::MazePath<int> shortestPathMaze(int numOfIterations);

    private:

        template<class Probability>
        Maze::MazePath<int> solveMaze(int numOfIterations, Probability P);

        template <typename Probability>
        void createSolution(std::map<int, int>& path, Probability P);

        void getPath(std::map<int, int>& newPath, std::vector<std::set<int>>& paths);

        template <typename Probability>
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap, Probability P);

        void getSubset(std::vector<std::set<int>>& paths) const;

        void updatePheromones(const std::vector<std::set<int>>& bestPaths);
        void increasePheromones(const std::set<int>& path);
        void decreasePheromones(int Ant);

        double probability(int cell) { return mPheromones[cell] * std::pow(heuristics(cell), 3); }

        int heuristics(int cell) { return mMaze.width() + mMaze.height() - std::abs((cell % mMaze.width()) - mMaze.end().first) + std::abs((cell / mMaze.width()) - mMaze.end().second); }

    private:
        Maze mMaze;

        int mSubsetLen;
        int mNumOfAnts;

        double *mPheromones;
        double *mAllPheromones;
        double mDecreaseFactor;

        Random<std::mt19937> mRandomEngine;

        Maze::MazePath<int> mBestPath;
    };
}


#endif //MHRAD_ANTALGMAZE_H
