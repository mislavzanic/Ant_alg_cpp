#include "AntAlgMaze.h"
#include <stack>
#include <algorithm>
#include <cassert>
#include <set>
#include <map>
#include <iostream>

namespace mh {

    AntColonyMaze::AntColonyMaze(const std::string &filepath, int numOfAnts, int subsetLen, double p, double startPheromones)
        : mMaze(filepath), mRandomEngine(mMaze.getEngine()),
          mNumOfAnts(numOfAnts), mSubsetLen(subsetLen),
          mDecreaseFactor(p), mPheromones(new double[mMaze.width() * mMaze.height()]),
          mAllPheromones(new double[mMaze.width() * mMaze.height()])
    {
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i)
        {
            mAllPheromones[i] = 0;
            mPheromones[i] = startPheromones;
        }
    }

    AntColonyMaze::AntColonyMaze(const Maze &maze, int numOfAnts, int subsetLen, double p, double startPheromones)
        : mMaze(maze), mRandomEngine(mMaze.getEngine()),
          mNumOfAnts(numOfAnts), mSubsetLen(subsetLen),
          mDecreaseFactor(p), mPheromones(new double[mMaze.width() * mMaze.height()]),
          mAllPheromones(new double[mMaze.width() * mMaze.height()])
    {
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i)
        {
            mPheromones[i] = startPheromones;
            mAllPheromones[i] = 0;
        }
    }

    Maze::MazePath<int> AntColonyMaze::shortestPathMaze(int numOfIterations)
    {
        return solveMaze(numOfIterations, [this](int cell) {
            return mPheromones[cell] *
                   std::pow(1, 3);
        });
    }

    template <typename Probability>
    Maze::MazePath<int> AntColonyMaze::solveMaze(int numOfIterations, Probability P)
    {
        while (numOfIterations)
        {
            std::vector<std::set<int>> paths;
            for (int i = 0; i < mNumOfAnts; ++i)
            {
                std::map<int, int> parentMap;
                createSolution(parentMap, P);
                getPath(parentMap, paths);
            }
            getSubset(paths);
            updatePheromones(paths);
            numOfIterations--;
        }
        return mBestPath;
    }

    template <typename Probability>
    void AntColonyMaze::createSolution(std::map<int, int>& path, Probability P)
    {
        int start = mMaze.startAsInt();
        int end = mMaze.endAsInt();
        std::stack<int> toVisit;
        std::map<int, bool> visited;
        toVisit.push(start);
        int curr;
        while (!toVisit.empty())
        {
            curr = toVisit.top();
            toVisit.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) 
                break;
            pickRandom(curr, toVisit, path, P);
        }
    }

    void AntColonyMaze::updatePheromones(const std::vector<std::set<int>>& bestPaths)
    {
        for (int i = 0; i < mSubsetLen; ++i)
            increasePheromones(bestPaths[i]);
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i)
        {
            if (mPheromones[i] > 0) decreasePheromones(i);
            mAllPheromones[i] = 0;
        }
    }

    template <typename Probability>
    void AntColonyMaze::pickRandom(int cell, std::stack<int> &toVisit, std::map<int, int> &parentMap, Probability P)
    {
        std::set<int> neighborCells;
        int num = mMaze.insertNeighbors(cell, neighborCells);
        double sum = 0;
        for (int neighbor : neighborCells)
        {
            if (mPheromones[neighbor] > 0)
            {
                if (parentMap[neighbor] == 0)
                    parentMap[neighbor] = cell;
            }
            sum += P(neighbor);
        }

        std::list<int> tempList;
        while (sum > 0 && num > 0)
        {
            double r = mRandomEngine.getDoubleInRange(0, sum);
            double total = 0;
            int pickedCell;
            for (int neighbor : neighborCells)
            {
                if (P(neighbor) + total >= r)
                {
                    sum -= P(neighbor);
                    num--;
                    pickedCell = neighbor;
                    tempList.push_front(pickedCell);
                    break;
                }
                total += P(neighbor);
            }
            neighborCells.erase(pickedCell);
        }
        for (int neighbor : tempList) toVisit.push(neighbor);
    }

    void AntColonyMaze::getPath(std::map<int, int> &newPath, std::vector<std::set<int>> &paths)
    {
        int start = mMaze.startAsInt(), end = mMaze.endAsInt();
        Maze::MazePath<int> solution;
        std::set<int> path;
        while (end != start)
        {
            assert(end != 0);
            solution.length++;
            path.insert(end);
            solution.parentMap[end] = newPath[end];
            end = newPath[end];
        }
        solution.parentMap[start] = start;
        path.insert(start);
        for (int c:path) mAllPheromones[c] += (double)1 / solution.length;
        paths.push_back(path);
        if (solution.length < mBestPath.length || mBestPath.parentMap.empty())
        {
            mBestPath = solution;
        }
    }

    void AntColonyMaze::increasePheromones(const std::set<int>& path)
    {
        for (auto cell : path) this->mPheromones[cell] += this->mAllPheromones[cell];
    }

    void AntColonyMaze::decreasePheromones(int Ant)
    {
        mPheromones[Ant] *= (1 - mDecreaseFactor);
    }

    void AntColonyMaze::getSubset(std::vector<std::set<int>> &paths) const
    {
        std::sort(paths.begin(), paths.end(), [](auto& a, auto& b){ return a.size() < b.size(); });
    }
}
