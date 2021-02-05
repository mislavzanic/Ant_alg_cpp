//
// Created by mislav on 2/4/21.
//

#ifndef MHRAD_ANTALGGRAPH_H
#define MHRAD_ANTALGGRAPH_H

#include "Maze/Maze.h"
#include "util/Random.h"

#include <vector>
#include <stack>
#include <utility>
#include <set>
#include <cmath>
#include <map>

namespace mh {
    class AntColonyGraph
    {
    public:
        AntColonyGraph(const Maze& maze, int numOfAnts, int subsetLen, double p, double startPheromones);
        Maze::MazePath<int> solve(int numOfIterations);

    private:
        void createSolution(std::map<int, int>& parentMap);
        Maze::MazePath<int> getMazePath();
        void getPath(std::map<int, int>& parentMap, std::vector<Graph::GraphPath>& paths);
        void pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap);

        double probability(int cell)
        {
            return std::pow(mPheromones[cell], 2) * std::pow(heuristics(cell), 3);
        }

        double heuristics(int cell)
        {
            return (double) 1 / (double)(std::abs((mGraph.end() % mMazeWidth) - (cell % mMazeWidth))
                 + std::abs((mGraph.end() / mMazeWidth) - (cell / mMazeWidth)));
        }

    private:
        Graph mGraph;

        int mMazeWidth;

        std::map<int, double> mPheromones;
        std::map<int, double> mAllPheromones;

        double mDecreaseFactor;

        Graph::GraphPath mBestPath;

        int mSubsetLen;
        int mNumOfAnts;

        Random<std::mt19937> mRandomEngine;

        void getSubset(std::vector<Graph::GraphPath>& path);

        void updatePheromones(std::vector<Graph::GraphPath>& path);

        void increasePheromones(const Graph::GraphPath &path);
    };
}

#endif //MHRAD_ANTALGGRAPH_H
