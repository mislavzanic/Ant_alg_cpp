//
// Created by mislav on 2/4/21.
//

#include "AntAlgGraph.h"
#include <cassert>
#include <algorithm>

namespace mh {

    AntColonyGraph::AntColonyGraph(const Maze& maze, int numOfAnts, int subsetLen, double p, double startPheromones)
        : mGraph(maze), mNumOfAnts(numOfAnts), mSubsetLen(subsetLen), mDecreaseFactor(p), mMazeWidth(maze.width()),
          mRandomEngine(maze.getEngine())
    {
        for (int vertex : mGraph.getAllVertices())
        {
            mPheromones[vertex] = startPheromones;
            mAllPheromones[vertex] = 0;
        }
        mBestPath.length = -1;
    }

    Maze::MazePath<int> AntColonyGraph::solve(int numOfIterations)
    {
        while (numOfIterations)
        {
            std::vector<Graph::GraphPath> paths;
            for (int i = 0; i < mNumOfAnts; ++i)
            {
                std::map<int, int> parentMap;
                createSolution(parentMap);
                getPath(parentMap, paths);
            }
            getSubset(paths);
            updatePheromones(paths);
            numOfIterations--;
        }

        return getMazePath();
    }

    void AntColonyGraph::createSolution(std::map<int, int>& parentMap)
    {
        int start = mGraph.start();
        int end = mGraph.end();
        std::stack<int> toVisit;
        std::map<int, int> visited;
        toVisit.push(start);

        int curr;
        while (!toVisit.empty())
        {
            curr = toVisit.top();
            toVisit.pop();
            if (curr == end) break;
            if (visited[curr]) continue;
            visited[curr] = true;
            pickRandom(curr, toVisit, parentMap);
        }
        assert(end == curr);
    }

    void AntColonyGraph::pickRandom(int cell, std::stack<int> &toVisit, std::map<int, int>& parentMap)
    {
        auto& neighbors = mGraph.getNeighbors(cell);
        std::set<int> neighborCells;
        double sum = 0;
        for (auto neighbor : neighbors)
        {
            if (mPheromones[neighbor.first] > 0)
            {
                if (parentMap[neighbor.first] == 0)
                    parentMap[neighbor.first] = cell;
                neighborCells.insert(neighbor.first);
            }
            sum += probability(neighbor.first);
        }

        int num = neighborCells.size();
        std::list<int> tempList;
        while (sum > 0 && num > 0)
        {
            double r = mRandomEngine.getDoubleInRange(0, sum);
            double total = 0;
            int pickedCell;
            for (int neighbor : neighborCells)
            {
                if (probability(neighbor) + total >= r)
                {
                    sum -= probability(neighbor);
                    num--;
                    pickedCell = neighbor;
                    tempList.push_front(pickedCell);
                    break;
                }
                total += probability(neighbor);
            }
            neighborCells.erase(pickedCell);
        }

        for (int neighbor : tempList) toVisit.push(neighbor);
    }

    Maze::MazePath<int> AntColonyGraph::getMazePath()
    {
        std::cout << mBestPath.length << std::endl;
        return Maze::MazePath<int>();
    }

    void AntColonyGraph::getPath(std::map<int, int> &parentMap, std::vector<Graph::GraphPath> &paths)
    {
        int start = mGraph.start(), end = mGraph.end();
        Graph::GraphPath path;
        while (end != start)
        {
            assert(end != 0);
            path.length += mGraph.getEdgeLength(end, parentMap[end]);
            path.vertices.insert(parentMap[end]);
            end = parentMap[end];
        }
        for (int cell : path.vertices) mAllPheromones[cell] += (double)1 / path.length;
        paths.push_back(path);

        if (path.length < mBestPath.length || mBestPath.length == -1)
        {
            mBestPath = path;
        }
    }

    void AntColonyGraph::getSubset(std::vector<Graph::GraphPath>& paths)
    {
        std::sort(paths.begin(), paths.end(), [](auto& a, auto& b){ return a.length < b.length; });
    }

    void AntColonyGraph::updatePheromones(std::vector<Graph::GraphPath>& paths)
    {
        for (int i = 0; i < mSubsetLen; ++i) increasePheromones(paths[i]);
        for (int vertices : mGraph.getAllVertices())
        {
            if (mPheromones[vertices] > 0) mPheromones[vertices] *= (1 - mDecreaseFactor);
            mAllPheromones[vertices] = 0;
        }
    }

    void AntColonyGraph::increasePheromones(const Graph::GraphPath& path)
    {
        for (auto cell : path.vertices) this->mPheromones[cell] += this->mAllPheromones[cell];
    }
}

