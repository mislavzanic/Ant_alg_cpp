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

    Maze::MazePath<int> AntColony::solve(int numOfIterations)
    {
        int j = numOfIterations;
        while (j)
        {
            std::vector<std::set<int>> paths;
            for (int i = 0; i < mNumOfAnts; ++i)
            {
                std::map<int, int> parentMap;
                createSolution(parentMap);
                getPath(parentMap, paths);
            }
            getSubset(paths);
            updatePheromones(paths);
            j--;
        }

        return mBestPath;
    }

    void AntColony::createSolution(std::map<int, int>& path)
    {
        int start = mMaze.startAsInt();
        int end = mMaze.endAsInt();
        std::stack<int> toVisit;
        std::map<int, bool> visited;
        toVisit.push(start);
        int prev = toVisit.top(), curr;
        while (!toVisit.empty())
        {
            curr = toVisit.top();
            toVisit.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) 
                break;
            pickRandom(curr, toVisit, path);
            prev = curr;
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

    void AntColony::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap)
    {
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
        {
            {1, cell < mMaze.width() ? -1 : cell - mMaze.width()},
            {2, cell + mMaze.width() > mMaze.width() * mMaze.height() ? -1 : cell + mMaze.width()},
            {3, cell % mMaze.width() ? cell - 1 : -1},
            {4, (cell + 1) % mMaze.width() ? cell + 1 : -1}
        };
        double sum = 0;
        int cellsToPick = 0;
        for (int num : order)
        {
            if (cellIndex[num] != -1 && mMaze[cellIndex[num]])
            {
                if (mPheromones[cellIndex[num]] > 0)
                {
                    if (parentMap[cellIndex[num]] == 0)
                        parentMap[cellIndex[num]] = cell;
                    cellsToPick++;
                }
                
                sum += probability(cellIndex[num]);
            }
        }

        std::stack<int> tempS;
        std::set<int> duplicates;
        while (sum > 0 && cellsToPick > duplicates.size())
        {
            double r = mMaze.getEngine().getDoubleInRange(0, sum);
            double total = 0;
            for (int num : order)
            {
                if (mPheromones[cellIndex[num]] != 0 && probability(cellIndex[num]) + total >= r && duplicates.find(cellIndex[num]) == duplicates.end() && mMaze[cellIndex[num]])
                {
                    duplicates.insert(cellIndex[num]);
                    tempS.push(cellIndex[num]);
                    sum -= probability(cellIndex[num]);
                    break;
                }
                total += probability(cellIndex[num]);
            }
        }
        while (!tempS.empty())
        {
            int temp = tempS.top();
            tempS.pop();
            toVisit.push(temp);
        }
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
