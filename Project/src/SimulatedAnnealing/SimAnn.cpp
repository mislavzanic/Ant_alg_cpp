//
// Created by mislav on 12/26/20.
//

#include <algorithm>
#include <cmath>
#include "SimAnn.h"

namespace mh {

    SimAnn::SimAnn(const std::string &filepath, double minTemp, double maxTemp, double step)
        : mMaze(filepath), mCurrentState({0, 0}), mSolution({0, 0}), mGoal({mMaze.width(), mMaze.height()}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }

    // TODO: napraviti solveWithWisitedSet()
    std::map<int, int> SimAnn::solve()
    {
        std::pair<int, int> prev = mCurrentState;
        bool foundCell = false;
        while (mCurrentTemp > mFinalTemp)
        {
            std::pair<int, int> neighbor = pickRandom(mCurrentState);
            if (neighbor == prev) continue;
            else if (neighbor == mGoal)
            {
                foundCell = true;
                break;
            }
            else if (neighbor == std::make_pair(-1, -1)) break;
            mPath[prev.first + prev.second * mMaze.width()] = neighbor.first + neighbor.second * mMaze.width();
            prev = neighbor;
            int neighborValue = abs(mGoal.first - neighbor.first) + abs(mGoal.second - neighbor.second);
            int solutionValue = abs(mGoal.first - mSolution.first) + abs(mGoal.second - mSolution.second);
            int costDiff = solutionValue - neighborValue;

            if (costDiff > 0) mSolution = neighbor;
            else
            {
                double prob = std::exp(costDiff / mCurrentTemp);
                double rand = mRandEngine.getDoubleInRange(0, 1);
                if (rand < prob) mSolution = neighbor;
            }

            mCurrentTemp -= mStep;
        }

        if (!foundCell) return {};
        return mPath;
    }


    std::pair<int, int> SimAnn::pickRandom(std::pair<int, int> cell)
    {
        std::array<int, 4> order{1,2,3,4};
        std::pair<int, int> nil = {-1, -1};
        std::map<int, std::pair<int, int>> cellIndex
        {
            {1, cell.first > 0 ? std::make_pair(cell.first - 1, cell.second) : nil},
            {2, cell.first < mMaze.width() - 1 ? std::make_pair(cell.first + 1, cell.second) : nil},
            {3, cell.second > 0 ? std::make_pair(cell.first, cell.second - 1) : nil},
            {4, cell.second < mMaze.height() - 1 ? std::make_pair(cell.first, cell.second + 1) : nil}
        };
        std::shuffle(order.begin(), order.end(), mRandEngine.getEngine());
        for (auto& kv : cellIndex)
        {
            if (kv.second != nil) return kv.second;
        }
        return nil;
    }
}


