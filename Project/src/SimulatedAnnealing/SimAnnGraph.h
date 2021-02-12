//
// Created by mislav on 2/10/21.
//

#include "Maze/MatrixMaze.h"
#include "Maze/Graph.h"
#include "util/Random.h"
#include <vector>
#include <memory>
#include <map>
#include <stack>

#ifndef MHRAD_SIMANNGRAPH_H
#define MHRAD_SIMANNGRAPH_H

namespace mh {

    class SimAnnGraph
    {
    public:

        SimAnnGraph(const std::string& filepath, int maxIter);
        Path solve();

    private:

        void createInitialSolution();
        void simAnn();
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap);
        Path getNeighbor(Path& state);
        bool findPath(int intersection, Path& newPath, Path& currentPath);

        static double temperature(double t) { return std::exp(-t); }

        double heuristics(int cell)
        {
            return (double) 1 / (double)(std::abs((mMaze->getEnd() % mMaze->getMazeWidth()) - (cell % mMaze->getMazeWidth()))
                                         + std::abs((mMaze->getEnd() / mMaze->getMazeWidth()) - (cell / mMaze->getMazeWidth())));
        }

        int pathHeuristics(Path& first)
        {
            return mMaze->getMazeWidth() * mMaze->getMazeHeight() - first.length;
        }

    private:

        std::shared_ptr<MazeInterface> mMaze;

        int mMaxIter;

        Path mSolution;

        Random<std::mt19937> mRandomEngine;

    };

}


#endif //MHRAD_SIMANNGRAPH_H
