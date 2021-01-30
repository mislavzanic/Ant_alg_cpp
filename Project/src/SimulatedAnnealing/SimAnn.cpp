#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include "SimAnn.h"

namespace mh {

    SimulatedAnnealing::SimulatedAnnealing(const std::string &filepath, int maxIter)
        : mMaze(filepath), mGoal({mMaze.width(), mMaze.height()}), mMaxIter(maxIter)
    {
    }

    SimulatedAnnealing::SimulatedAnnealing(const Maze& m, int maxIter)
        : mMaze(m), mMaxIter(maxIter),
          mGoal({mMaze.end().first, mMaze.end().second})
    {
    }

    SimulatedAnnealing::SimulatedAnnealing(Maze&& m, int maxIter)
        : mMaze(std::move(m)), mMaxIter(maxIter),
          mGoal({mMaze.end().first, mMaze.end().second})
    {
    }
    
    Maze::MazePath<int> SimulatedAnnealing::solve()
    {
        createInitialSolution();
        simAnn();
        return mSolution;
    }

    void SimulatedAnnealing::createInitialSolution()
    {
        int start = mMaze.startAsInt();
        int end = mMaze.endAsInt();
        std::stack<int> toVisit;
        std::map<int, bool> visited;
        std::map<int, int> parentMap;
        toVisit.push(start);
        int curr;
        while (!toVisit.empty())
        {
            curr = toVisit.top();
            toVisit.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) break;
            pickRandom(curr, toVisit, parentMap);
        }

        while (curr != start)
        {
            mSolution.parentMap[curr] = parentMap[curr];
            if (mMaze.neighbors(curr) > 2) mSolution.intersections.insert(curr);
            mSolution.length++;
            curr = parentMap[curr];
        }
        mSolution.parentMap[start] = start;
    }

    void SimulatedAnnealing::simAnn()
    {
        Maze::MazePath<int> currentState = mSolution;
        for (int k = 0; k < mMaxIter; ++k)
        {
            Maze::MazePath<int> neighbor = getNeighbor(currentState);
            int costDiff = heuristics(neighbor) - heuristics(currentState);
            if (costDiff > 0)
            {
                currentState = neighbor;
                if (heuristics(currentState) > heuristics(mSolution))
                    mSolution = currentState;
            }
            else
            {
                double random = mMaze.getEngine().getDoubleInRange(0, 1);
                double T = temperature((double)costDiff / (double)(mMaxIter - k));
                if (random < T)
                    currentState = neighbor;
            }
        }
    }

    void SimulatedAnnealing::pickRandom(int cell, std::queue<int>& toVisit, std::map<int, int>& parentMap)
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

    void SimulatedAnnealing::pickRandom(int cell, std::stack<int>& toVisit, std::map<int, int>& parentMap)
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

    Maze::MazePath<int> SimulatedAnnealing::getNeighbor(Maze::MazePath<int>& state)
    {
        Maze::MazePath<int> returnPath;
        for (int intersection : state.intersections)
        {
            if (findPath(intersection, returnPath, state))
                return returnPath;
        }
        return returnPath;
    }

    // TODO: refactor this!!
    bool SimulatedAnnealing::findPath(int intersection, Maze::MazePath<int>& newPath, Maze::MazePath<int>& currentPath)
    {
        int end = mMaze.endAsInt();
        int start = mMaze.startAsInt();
        std::map<int, bool> visited;
        std::map<int, int> parentMap;
        std::stack<int> toVisit;

        toVisit.push(intersection);

        while (intersection != start)
        {
            parentMap[intersection] = currentPath.parentMap[intersection];
            intersection = currentPath.parentMap[intersection];
            visited[intersection] = true;
        }
        parentMap[start] = start;

        int curr;
        while (!toVisit.empty())
        {
            curr = toVisit.top();
            toVisit.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) break;
            pickRandom(curr, toVisit, parentMap);
        }
        if (curr != end) return false;
        
        while (curr != start)
        {
            newPath.parentMap[curr] = parentMap[curr];
            if (mMaze.neighbors(curr) > 2) newPath.intersections.insert(curr);
            newPath.length++;
            curr = parentMap[curr];
        }
        newPath.parentMap[start] = start;

        return true;
    }
}