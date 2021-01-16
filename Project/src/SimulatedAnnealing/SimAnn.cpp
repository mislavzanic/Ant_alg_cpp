#include <iostream>
#include <algorithm>
#include <cmath>
#include "SimAnn.h"

namespace mh {

    SimAnn::SimAnn(const std::string &filepath, double minTemp, double maxTemp, double step)
        : mMaze(filepath), mSolution({0, 0}), mGoal({mMaze.width(), mMaze.height()}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }

    SimAnn::SimAnn(const Maze& m, double minTemp, double maxTemp, double step)
        : mMaze(m), mSolution({mMaze.start().first, mMaze.start().second}),
        mGoal({mMaze.end().first, mMaze.end().second}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }

    SimAnn::SimAnn(Maze&& m, double minTemp, double maxTemp, double step)
        : mMaze(std::move(m)), mSolution({mMaze.start().first, mMaze.start().second}), 
        mGoal({mMaze.end().first, mMaze.end().second}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }
    
    std::map<int, int> SimAnn::solve()
    {
        std::pair<int, int> prev = mSolution;
        std::stack<int> toVisit;
        std::map<int, bool> visited;
        toVisit.push(mMaze.startAsInt());
        while (mCurrentTemp > mFinalTemp)
        {
            while (!pickRandom(mSolution, toVisit))
            {
                toVisit.pop();
                if (toVisit.empty()) return mPath;
                mSolution = mMaze.intToPair(toVisit.top());
            }

            std::pair<int, int> nextCell = mMaze.intToPair(toVisit.top());
            toVisit.pop();
            if (visited[mMaze.pairToInt(nextCell)]) continue;
            visited[mMaze.pairToInt(nextCell)] = true;
            mPath[mMaze.pairToInt(mSolution)] = mMaze.pairToInt(nextCell);
            if (nextCell == mGoal) return mPath;

            int nextCellValue = heuristics(mGoal, nextCell);
            int solutionValue = heuristics(mGoal, mSolution);
            int costDiff = solutionValue - nextCellValue;

            if (costDiff > 0) 
            {
                prev = mSolution;
                mSolution = nextCell;
            }
            else
            {
                double prob = std::exp(costDiff / mCurrentTemp);
                double rand = mMaze.getEngine().getDoubleInRange(0, 1);
                if (rand < prob)
                {
                    prev = mSolution;
                    mSolution = nextCell;
                }
            }

            mCurrentTemp *= mStep;
        }

        return mPath;
    }


    bool SimAnn::pickRandom(std::pair<int, int> cell, std::stack<int>& toVisit)
    {
        std::array<int, 4> order{1,2,3,4};
        std::pair<int, int> nil = {-1, -1};
        bool found = false;
        std::map<int, std::pair<int, int>> cellIndex
        {
            {1, cell.first > 0 ? std::make_pair(cell.first - 1, cell.second) : nil},
            {2, cell.first < mMaze.width() - 1 ? std::make_pair(cell.first + 1, cell.second) : nil},
            {3, cell.second > 0 ? std::make_pair(cell.first, cell.second - 1) : nil},
            {4, cell.second < mMaze.height() - 1 ? std::make_pair(cell.first, cell.second + 1) : nil}
        };
        std::shuffle(order.begin(), order.end(), mMaze.getEngine().getEngine());
        for (int i : order)
        {
            if (cellIndex[i] != nil && mMaze[mMaze.pairToInt(cellIndex[i])])
            {
                toVisit.push(mMaze.pairToInt(cellIndex[i]));
                found = true;
            }
        }
        return found;
    }
}


