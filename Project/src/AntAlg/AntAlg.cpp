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
        : mMaze(filepath), mNumOfAnts(numOfAnts), mSubsetLen(subsetLen), mDecreaseFactor(p),
        mAnts(new int[mNumOfAnts]), mPheromones(new double[mMaze.Width() * mMaze.Height()])
    {
    }

    void AntAlg::solve(int numOfIterations) {
        int j = numOfIterations;

        {
            std::vector<std::set<int>> paths;
            std::map<int, int> startPath;

            createSolution(0, startPath);
            getPath(startPath, paths);
            updatePheromone(paths);
        }

        while (j)
        {
            std::vector<std::set<int>> paths;
            for (int i = 0; i < mNumOfAnts; ++i)
            {
                std::map<int, int> newPath;
                createSolution(i, newPath);
                getPath(newPath, paths);
            }
            getSubset(paths);
            updatePheromone(paths);
            j--;
        }
    }

    void AntAlg::createSolution(int Ant, std::map<int, int>& path)
    {
        int start = mMaze.Start();
        int end = mMaze.End();

        std::stack<int> toVisit;
        std::set<int> visited;
        toVisit.push(mMaze.Start());
        while (!toVisit.empty())
        {
            auto curr = toVisit.top();
            if (curr == end) break;
            toVisit.pop();
            if (visited.find(curr) != visited.end()) continue;
            visited.insert(curr);
            pickRandom(curr, toVisit, path);
        }
    }

    void AntAlg::updatePheromone(const std::vector<std::set<int>>& bestPaths)
    {
         for (auto& s:bestPaths)
         {
             for (int c:s) increasePheromones(c);
         }

         for (int i = 0; i < mMaze.Width() * mMaze.Height(); ++i)
         {
             if (mPheromones[i] > 0) decreasePheromones(i);
         }
    }

    int AntAlg::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& path)
    {

    }

    void AntAlg::getPath(std::map<int, int> &newPath, std::vector<std::set<int>> &paths)
    {
        int start = mMaze.Start(), end = mMaze.End();
        std::set<int> path;
        while (end != start)
        {
            path.insert(end);
            end = newPath[end];
        }
        path.insert(start);
        paths.push_back(path);
    }

    void AntAlg::increasePheromones(int Ant)
    {

    }

    void AntAlg::decreasePheromones(int Ant)
    {
        mPheromones[Ant] *= (1 - mDecreaseFactor);
    }

    void AntAlg::getSubset(std::vector<std::set<int>> &paths) const
    {
        std::sort(paths.begin(), paths.end(), [](auto& a, auto& b){ return a.size() < b.size(); });
        paths.erase(paths.begin() + mSubsetLen, paths.end());
    }

}
