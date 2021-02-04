#include "AntAlg.h"
#include <stack>
#include <array>
#include <algorithm>
#include <cassert>
#include <set>
#include <map>
#include <iostream>

namespace mh {

    AntColony::AntColony(const std::string &filepath, int numOfAnts, int subsetLen, double p, double startPheromones)
        : mMaze(filepath), mNumOfAnts(numOfAnts), mSubsetLen(subsetLen),
          mDecreaseFactor(p), mPheromones(new double[mMaze.width() * mMaze.height()]),
          mAllPheromones(new double[mMaze.width() * mMaze.height()])
    {
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i)
        {
            mAllPheromones[i] = 0;
            mPheromones[i] = startPheromones;
        }
    }

    AntColony::AntColony(const Maze &maze, int numOfAnts, int subsetLen, double p, double startPheromones)
        : mMaze(maze), mNumOfAnts(numOfAnts), mSubsetLen(subsetLen),
          mDecreaseFactor(p), mPheromones(new double[mMaze.width() * mMaze.height()]),
          mAllPheromones(new double[mMaze.width() * mMaze.height()])
    {
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i)
        {
            mPheromones[i] = startPheromones;
            mAllPheromones[i] = 0;
        }
    }

    Maze::MazePath<int> AntColony::shortestPath(int numOfIterations)
    {
        return solve(numOfIterations, [this](int cell)
        {
            return mPheromones[cell] *
                   std::pow(1,3);
        });
    }

    Maze::MazePath<int> AntColony::longestPath(int numOfIterations) {
        return solve(numOfIterations, [this](int cell)
        {
            return mPheromones[cell] *
                   std::pow(mMaze.width() + mMaze.height()
                            - std::abs((cell % mMaze.width()) - mMaze.end().first)
                            + std::abs((cell / mMaze.width()) - mMaze.end().second),
                            3);
        });
    }

    template <typename Probability>
    Maze::MazePath<int> AntColony::solve(int numOfIterations, Probability P)
    {
        int j = numOfIterations;
        while (j)
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
            j--;
        }
        return mBestPath;
    }

    template <typename Probability>
    void AntColony::createSolution(std::map<int, int>& path, Probability P)
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

    void AntColony::updatePheromones(const std::vector<std::set<int>>& bestPaths)
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
    void AntColony::pickRandom(int cell, std::stack<int> &toVisit, std::map<int, int> &parentMap, Probability P)
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
            double r = mMaze.getEngine().getDoubleInRange(0, sum);
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

    void AntColony::getPath(std::map<int, int> &newPath, std::vector<std::set<int>> &paths)
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

    void AntColony::increasePheromones(const std::set<int>& path)
    {
        for (auto cell : path) this->mPheromones[cell] += this->mAllPheromones[cell];
    }

    void AntColony::decreasePheromones(int Ant)
    {
        mPheromones[Ant] *= (1 - mDecreaseFactor);
    }

    void AntColony::getSubset(std::vector<std::set<int>> &paths) const
    {
        std::sort(paths.begin(), paths.end(), [](auto& a, auto& b){ return a.size() < b.size(); });
    }
}
