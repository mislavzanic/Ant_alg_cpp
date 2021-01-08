//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_ANTALG_H
#define MHRAD_ANTALG_H

#include "Maze/Maze.h"
#include "util/Random.h"

#include <vector>
#include <stack>
#include <utility>
#include <set>
#include <map>


namespace mh {

    class AntAlg
    {
    public:
        AntAlg(const std::string& filepath, int numOfAnts, int subsetLen, double p);
        AntAlg(const Maze& maze, int numOfAnts, int subsetLen, double p);
        std::map<int, int> solve(int numOfIterations);

    private:
        void createSolution(std::map<int, int>& path);
        void initialSolution();

        void getPath(std::map<int, int>& newPath, std::vector<std::set<int>>& paths);
        void pickRandom(int cell, std::stack<int>& toVisit);
        void getSubset(std::vector<std::set<int>>& paths) const;

        void updatePheromone(const std::vector<std::set<int>>& bestPaths);
        void increasePheromones(const std::set<int>& path);
        void decreasePheromones(int Ant);

    private:
        Maze mMaze;

        int mSubsetLen;
        int mNumOfAnts;
        bool mFirstTraverse;

        double *mPheromones;
        double *mAllPheromones;
        double mDecreaseFactor;

        std::map<int, int> mBestPath;
        int mBestPathLen;

        Random<std::mt19937> mRandEngine;
    };

}


#endif //MHRAD_ANTALG_H
