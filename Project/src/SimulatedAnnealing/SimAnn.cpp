//
// Created by mislav on 12/26/20.
//

#include <algorithm>
#include "SimAnn.h"

namespace mh {

    SimAnn::SimAnn(const std::string &filepath, double minTemp, double maxTemp, double step)
        : mMaze(filepath), mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
        std::map<int, int> path;
        initialSolution(path);
        int curr = mMaze.end();
        while (curr != mMaze.start())
        {
            mPath.push_back(curr);
            curr = path[curr];
        }
        mPath.push_back(mMaze.start());
        mSolution = mPath.size();
    }

    void SimAnn::solve()
    {
        while (mCurrentTemp > mFinalTemp)
        {
            std::vector<int> neighbourPath;
            int lenNeigPath = getNeighbourPath(neighbourPath);
            double neighbourCost = 0;
            double costDiff = mSolution - neighbourCost;

            if (costDiff > 0)
            {
            }
        }
    }

    void SimAnn::initialSolution(std::map<int, int> &path)
    {
        int start = mMaze.start();
        int end = mMaze.end();
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

    int SimAnn::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& path)
    {
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
        {
            {1, cell < mMaze.width() ? -1 : cell - mMaze.width()},
            {2, cell + mMaze.width() > mMaze.width() * mMaze.height() ? -1 : cell + mMaze.width()},
            {3, cell % mMaze.width() ? cell - 1 : -1},
            {4, (cell + 1) % mMaze.width() ? cell + 1 : -1}
        };
        std::shuffle(order.begin(), order.end(), mRandEngine.getEngine());
        for (int num : order)
        {
            if (cellIndex[num] != -1 && mMaze[cellIndex[num]])
            {
                toVisit.push(cellIndex[num]);
                path[cellIndex[num]] = cell;
            }
        }
    }

    int SimAnn::getNeighbourPath(std::vector<int> &path)
    {
        // hodaj po izabranom putu
        // kad naidjes na krizanje provjeri sve puteve koje dobijes iz krizanja -- smislit nacin za odabrat nasumicno krizanje
        // ako je put bolji vrati ga, ako je losiji vrati ga uz odredjenu vjerojatnost
    }
}


