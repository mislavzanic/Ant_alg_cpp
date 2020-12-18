//
// Created by mislav on 12/12/20.
//

#include "AntAlg.h"
#include <stack>
#include <array>
#include <algorithm>
#include <set>
#include <map>

namespace mh {

    AntAlg::AntAlg(const std::string &filepath, int numOfAnts, int subsetLen, double p)
        : mMaze(filepath), mNumOfAnts(numOfAnts), mSubsetLen(subsetLen), mDecreaseFactor(p), mRandEngine(),
         mPheromones(new double[mMaze.Width() * mMaze.Height()]), mAllPheromones(new double[mMaze.Width() * mMaze.Height()])
    {
        for (int i = 0; i < mMaze.Width() * mMaze.Height(); ++i) mPheromones[i] = mAllPheromones[i] = 0;
    }

    void AntAlg::solve(int numOfIterations) {
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
    }

    void AntAlg::createSolution(std::map<int, int>& path)
    {
        int start = mMaze.Start();
        int end = mMaze.End();
        std::stack<int> toVisit;
        std::map<int, bool> visited;
        toVisit.push(start);
        while (!toVisit.empty())
        {
            auto curr = toVisit.top();
            if (curr == end) break;
            toVisit.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            pickRandom(curr, toVisit, path);
        }
    }

    void AntAlg::initialSolution()
    {
        std::vector<std::set<int>> paths;
        std::map<int, int> startPath;

        createSolution(startPath);
        getPath(startPath, paths);
        updatePheromone(paths);
    }

    void AntAlg::updatePheromone(const std::vector<std::set<int>>& bestPaths)
    {
         for (auto& s:bestPaths)
         {
             for (int c:s) increasePheromones(c, bestPaths);
         }

         for (int i = 0; i < mMaze.Width() * mMaze.Height(); ++i)
         {
             if (mPheromones[i] > 0) decreasePheromones(i);
             mAllPheromones[i] = 0;
         }
    }

    int AntAlg::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& path)
    {
        int w = mMaze.Width(), h = mMaze.Height(), num = 0;
        std::map<int, double> probabilities;
        double p = 0;
        if (cell % w && mMaze[cell - 1])
        {
            path[cell - 1] = cell;
            probabilities[cell - 1] = mPheromones[cell - 1];
            if (mPheromones[cell - 1] != 0) p += mPheromones[cell - 1];
            else num += 1;
        }
        else probabilities[cell - 1] = 0;
        if ((cell + 1) % w && mMaze[cell + 1])
        {
            path[cell + 1] = cell;
            probabilities[cell + 1] = mPheromones[cell + 1];
            if (mPheromones[cell + 1] != 0) p += mPheromones[cell + 1];
            else num += 1;
        }
        if (cell - w > -1 && mMaze[cell - w])
        {
            path[cell - w] = cell;
            probabilities[cell - w] = mPheromones[cell - w];
            if (mPheromones[cell - w] != 0) p += mPheromones[cell - w];
            else num += 1;
        }
        if (cell + w < w*h && mMaze[cell + w])
        {
            path[cell + w] = cell;
            probabilities[cell + w] = mPheromones[cell + w];
            if (mPheromones[cell + w] != 0) p += mPheromones[cell + w];
            else num += 1;
        }
        if (num == 4)
        {
            double pickRate = 0.25;
        }
        else
        {
            if (p > 1)
            {

            }
            else
            {

            }
        }
    }

    void AntAlg::getPath(std::map<int, int> &newPath, std::vector<std::set<int>> &paths)
    {
        int start = mMaze.Start(), end = mMaze.End(), len = 0;
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
    }

    void AntAlg::increasePheromones(int Ant, const std::vector<std::set<int>>& bestPaths)
    {
        std::for_each(bestPaths.begin(), bestPaths.begin() + mSubsetLen, [this](auto &s)
        {
            for (auto cell : s) this->mPheromones[s] += this->mAllPheromones[s];
        });
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
