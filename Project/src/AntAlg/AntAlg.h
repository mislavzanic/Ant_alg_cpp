//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_ANTALG_H
#define MHRAD_ANTALG_H

#include "Maze/Maze.h"

#include <vector>
#include <stack>
#include <utility>
#include <set>
#include <map>


namespace mh {

    class AntAlg {
    public:
        //using Ant = std::pair<int, int>;

        AntAlg(const std::string& filepath, int numOfAnts, int subsetLen, double p);
        void solve(int numOfIterations);

    private:
        struct compare
        {
            bool operator() (const std::set<int>& lhs, const std::set<int>& rhs) const
            {
                return lhs.size() < rhs.size();
            }
        };

    private:
        void createSolution(int Ant, std::map<int, int>& path);

        void getPath(std::map<int, int>& newPath, std::vector<std::set<int>>& paths);
        int pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& path);
        void getSubset(std::vector<std::set<int>>& paths) const;

        void updatePheromone(const std::vector<std::set<int>>& bestPaths);
        void increasePheromones(int Ant);
        void decreasePheromones(int Ant);

    private:
        Maze mMaze;

        int* mAnts;
        int mSubsetLen;
        int mNumOfAnts;

        double *mPheromones;
        double mDecreaseFactor;
    };

}


#endif //MHRAD_ANTALG_H