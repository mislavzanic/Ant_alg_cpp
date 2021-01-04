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

    void SimAnn::solve()
    {
        while (mCurrentTemp > mFinalTemp)
        {
            std::pair<int, int> neighbor = pickRandom(mCurrentState.first + mCurrentState.second * mMaze.width());
            int neighborValue = abs(mGoal.first - neighbor.first) + abs(mGoal.second - neighbor.second);
            int solutionValue = abs(mGoal.first - mSolution.first) + abs(mGoal.second - mSolution.second);
            int costDiff = solutionValue - neighborValue;

            if (costDiff > 0)
            {
                mSolution = neighbor;
            }
            else
            {
                double prob = std::exp(costDiff / mCurrentTemp);
                double rand = mRandEngine.getDoubleInRange(0, 1);
                if (rand < prob)
                {
                    mSolution = neighbor;
                }
            }

            mCurrentTemp -= mStep;
        }
    }


    std::pair<int, int> SimAnn::pickRandom(int cell)
    {
        // TODO:popraviti fuckiju td radi sa parovima...
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
        {
            {1, cell < mMaze.width() ? -1 : cell - mMaze.width()},
            {2, cell + mMaze.width() > mMaze.width() * mMaze.height() ? -1 : cell + mMaze.width()},
            {3, cell % mMaze.width() ? cell - 1 : -1},
            {4, (cell + 1) % mMaze.width() ? cell + 1 : -1}
        };
        std::shuffle(order.begin(), order.end(), mRandEngine.getEngine());
    }
}


