//
// Created by mislav on 12/26/20.
//

#include <algorithm>
#include "SimAnn.h"

namespace mh {

    SimAnn::SimAnn(const std::string &filepath, double minTemp, double maxTemp, double step)
        : mMaze(filepath), mCurrentTemp(minTemp), mFinalTemp(maxTemp), mStep(step)
    {
        std::map<int, int> path;
        initialSolution(path);
        int curr = mMaze.End();
        while (curr != mMaze.Start())
        {
            mPath.push_back(curr);
            curr = path[curr];
        }
        mPath.push_back(mMaze.Start());
        mSolution = mPath.size();
    }

    void SimAnn::solve()
    {

    }

    void SimAnn::initialSolution(std::map<int, int> &path)
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

    int SimAnn::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& path)
    {
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
                {
                        {1, cell < mMaze.Width() ? -1 : cell - mMaze.Width()},
                        {2, cell + mMaze.Width() > mMaze.Width() * mMaze.Height() ? -1 : cell + mMaze.Width()},
                        {3, cell % mMaze.Width() ? cell - 1 : -1},
                        {4, (cell + 1) % mMaze.Width() ? cell + 1 : -1}
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

    int SimAnn::traverseBack()
    {
        return 0;
    }
}


