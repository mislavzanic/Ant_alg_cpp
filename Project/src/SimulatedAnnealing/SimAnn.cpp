#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include "SimAnn.h"

namespace mh {

    SimAnn::SimAnn(const std::string &filepath, double minTemp, double maxTemp, double step)
        : mMaze(filepath), mSolution(), mGoal({mMaze.width(), mMaze.height()}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }

    SimAnn::SimAnn(const Maze& m, double minTemp, double maxTemp, double step)
        : mMaze(m), mSolution(),
        mGoal({mMaze.end().first, mMaze.end().second}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }

    SimAnn::SimAnn(Maze&& m, double minTemp, double maxTemp, double step)
        : mMaze(std::move(m)), mSolution(), 
        mGoal({mMaze.end().first, mMaze.end().second}),
        mCurrentTemp(maxTemp), mFinalTemp(minTemp), mStep(step)
    {
    }
    
    std::map<int, int> SimAnn::solve()
    {
        createInitialSolution();
        return mSolution;
    }

    void SimAnn::createInitialSolution()
    {
        int start = mMaze.startAsInt();
        int end = mMaze.endAsInt();
        std::stack<int> toVisit;
        std::map<int, bool> visited;
        std::map<int, int> parentMap;
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
            pickRandom(curr, toVisit, parentMap);
            prev = curr;
        }

        while (curr != start)
        {
            mSolution[curr] = parentMap[curr];
            curr = parentMap[curr];
        }
        mSolution[start] = start;
    }

    void SimAnn::simulatedAnnealing()
    {
        while (mCurrentTemp > mFinalTemp)
        {
            
        }
    }

    void SimAnn::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap)
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
                if (mMaze[cellIndex[num]])
                {
                    if (parentMap[cellIndex[num]] == 0)
                        parentMap[cellIndex[num]] = cell;
                    cellsToPick++;
                }
                
                sum += heuristics(cellIndex[num]);
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
                if (heuristics(cellIndex[num]) + total >= r && duplicates.find(cellIndex[num]) == duplicates.end() && mMaze[cellIndex[num]])
                {
                    duplicates.insert(cellIndex[num]);
                    tempS.push(cellIndex[num]);
                    sum -= heuristics(cellIndex[num]);
                    break;
                }
                total += heuristics(cellIndex[num]);
            }
        }
        while (!tempS.empty())
        {
            int temp = tempS.top();
            tempS.pop();
            toVisit.push(temp);
        }
    }
}


