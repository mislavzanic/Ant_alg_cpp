//
// Created by mislav on 2/10/21.
//

#include "Maze/Maze.h"
#include "util/Random.h"
#include <vector>
#include <map>
#include <stack>

#ifndef MHRAD_SIMANNGRAPH_H
#define MHRAD_SIMANNGRAPH_H

namespace mh {

    class SimAnnGraph
    {
    public:

        SimAnnGraph(const Maze& m, int maxIter);
        SimAnnGraph(Maze&& m, int maxIter);
        Graph::GraphPath shortestPath();

    private:

        void simAnn();
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap);
        void createInitialSolution();
        Graph::GraphPath getNeighbor(Graph::GraphPath& state);
        bool findPath(int intersection, Graph::GraphPath& newPath, Graph::GraphPath& currentPath);

        static double temperature(double t) { return std::exp(-t); }

        double heuristics(int cell)
        {
            return (double) 1 / (double)(std::abs((mGraph.end() % mMazeWidth) - (cell % mMazeWidth))
                                         + std::abs((mGraph.end() / mMazeWidth) - (cell / mMazeWidth)));
        }

        int pathHeuristics(Graph::GraphPath& first)
        {
            return mMazeWidth * mMazeHeight - first.length;
        }

    private:

        Graph mGraph;

        int mMaxIter;
        int mMazeWidth;
        int mMazeHeight;

        Graph::GraphPath mSolution;

        Random<std::mt19937> mRandomEngine;

    };

}


#endif //MHRAD_SIMANNGRAPH_H
