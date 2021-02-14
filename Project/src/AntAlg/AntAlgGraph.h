//
// Created by mislav on 2/4/21.
//

#ifndef MHRAD_ANTALGGRAPH_H
#define MHRAD_ANTALGGRAPH_H

#include "Maze/MatrixMaze.h"
#include "Maze/Graph.h"
#include "util/Random.h"

#include <vector>
#include <memory>
#include <stack>
#include <utility>
#include <set>
#include <cmath>
#include <map>

namespace mh {
    class AntColonyGraph
    {
    public:
        AntColonyGraph(const std::string& filepath, int numOfAnts, int subsetLen, double p, double startPheromones);
        Path solve(int numOfIterations);

    private:
        void createSolution(std::map<int, int>& parentMap);
        void getPath(std::map<int, int>& parentMap, std::vector<Path>& paths);
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap);
        void getSubset(std::vector<Path>& path);
        void updatePheromones(std::vector<Path>& path);
        void increasePheromones(const Path &path);

        double probability(int cell)
        {
            return std::pow(mPheromones[cell], 2) * std::pow(heuristics(cell), 3);
        }

        double heuristics(int cell)
        {
            return (double) 1 / (double)(std::abs((mMaze->getEnd() % mMaze->getMazeWidth()) - (cell % mMaze->getMazeWidth()))
                 + std::abs((mMaze->getEnd() / mMaze->getMazeWidth()) - (cell / mMaze->getMazeWidth())));
        }

    private:
        std::shared_ptr<MazeInterface> mMaze;

        std::map<int, double> mPheromones;
        std::map<int, double> mAllPheromones;

        double mDecreaseFactor;

        Path mBestPath;

        int mSubsetLen;
        int mNumOfAnts;

        Random<std::mt19937> mRandomEngine;
    };
}

#endif //MHRAD_ANTALGGRAPH_H
