//
// Created by mislav on 12/12/20.
//

#include "AntAlg.h"
#include <stack>
#include <array>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>

namespace mh {

    AntAlg::AntAlg(const std::string &filepath, int numOfAnts, int subsetLen, double p)
        : mMaze(filepath), mFirstTraverse(true), mNumOfAnts(numOfAnts), mBestPathLen(-1), mSubsetLen(subsetLen),
          mDecreaseFactor(p), mRandEngine(), mPheromones(new double[mMaze.width() * mMaze.height()]),
          mAllPheromones(new double[mMaze.width() * mMaze.height()])
    {
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i) mPheromones[i] = mAllPheromones[i] = 0;
    }

    AntAlg::AntAlg(const Maze &maze, int numOfAnts, int subsetLen, double p)
        : mMaze(maze), mFirstTraverse(true), mNumOfAnts(numOfAnts), mBestPathLen(-1), mSubsetLen(subsetLen),
          mDecreaseFactor(p), mRandEngine(), mPheromones(new double[mMaze.width() * mMaze.height()]),
          mAllPheromones(new double[mMaze.width() * mMaze.height()])
    {
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i) mPheromones[i] = mAllPheromones[i] = 0;
    }

    std::map<int, int> AntAlg::solve(int numOfIterations)
    {
        int j = numOfIterations;
        initialSolution();
        while (j)
        {
            std::vector<std::set<int>> paths;
            for (int i = 0; i < mNumOfAnts; ++i)
            {
                std::map<int, int> newPath;
                createSolution(newPath);
                getPath(newPath, paths);
            }
            getSubset(paths);
            updatePheromone(paths);
            j--;
        }

        return mBestPath;
    }

    void AntAlg::createSolution(std::map<int, int>& path)
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
            path[curr] = prev;
            if (curr == end)
                break;
            pickRandom(curr, toVisit);
            prev = curr;
        }
    }

    void AntAlg::initialSolution()
    {
        std::vector<std::set<int>> paths;
        std::map<int, int> startPath;

        createSolution(startPath);
        getPath(startPath, paths);
        increasePheromones(paths[0]);
        mFirstTraverse = false;
    }

    void AntAlg::updatePheromone(const std::vector<std::set<int>>& bestPaths)
    {
        for (int i = 0; i < mSubsetLen; ++i)
            increasePheromones(bestPaths[i]);
        if (mFirstTraverse) return;
        for (int i = 0; i < mMaze.width() * mMaze.height(); ++i)
        {
            if (mPheromones[i] > 0) decreasePheromones(i);
            mAllPheromones[i] = 0;
        }
    }

    void AntAlg::pickRandom(int cell, std::stack<int>& toVisit)
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
        if (mFirstTraverse)
        {
            std::shuffle(order.begin(), order.end(), mRandEngine.getEngine());
        }
        for (int num : order)
        {
            if (cellIndex[num] != -1 && mMaze[cellIndex[num]])
            {
                if (mFirstTraverse)
                    toVisit.push(cellIndex[num]);
                else
                {
                    if (mPheromones[cellIndex[num]] > 0)
                        cellsToPick++;
                    sum += mPheromones[cellIndex[num]];
                }
            }
        }
        std::stack<int> tempS;
        std::set<int> duplicates;
        while (sum > 0 && cellsToPick > duplicates.size())
        {
            double r = mRandEngine.getDoubleInRange(0, sum);
            double total = 0;
            for (int num : order)
            {
                if (mPheromones[cellIndex[num]] != 0 && mPheromones[cellIndex[num]] + total >= r && duplicates.find(cellIndex[num]) == duplicates.end())
                {
                    duplicates.insert(cellIndex[num]);
                    tempS.push(cellIndex[num]);
                    sum -= mPheromones[cellIndex[num]];
                    break;
                }
                total += mPheromones[cellIndex[num]];
            }
        }
        while (!tempS.empty())
        {
            int temp = tempS.top();
            tempS.pop();
            toVisit.push(temp);
        }
    }

    void AntAlg::getPath(std::map<int, int> &newPath, std::vector<std::set<int>> &paths)
    {
        int start = mMaze.startAsInt(), end = mMaze.endAsInt(), len = 0;
        std::set<int> path;
        while (end != start)
        {
            len++;
            path.insert(end);
            end = newPath[end];
        }
        path.insert(start);
        for (int c:path) mAllPheromones[c] += (double)1/len;
        paths.push_back(path);
        if (len < mBestPathLen || mBestPathLen == -1)
        {
            mBestPathLen = len;
            mBestPath = newPath;
        }
    }

    void AntAlg::increasePheromones(const std::set<int>& path)
    {
        for (auto cell : path) this->mPheromones[cell] += this->mAllPheromones[cell];
    }

    void AntAlg::decreasePheromones(int Ant)
    {
        mPheromones[Ant] *= (1 - mDecreaseFactor);
    }

    void AntAlg::getSubset(std::vector<std::set<int>> &paths) const
    {
        std::sort(paths.begin(), paths.end(), [](auto& a, auto& b){ return a.size() < b.size(); });
    }
}
