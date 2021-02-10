#include <queue>
#include <iostream>
#include <algorithm>
#include <set>
#include "SimAnn.h"

namespace mh {

    SimulatedAnnealing::SimulatedAnnealing(const std::string &filepath, int maxIter)
        : mMaze(filepath), mRandomEngine(mMaze.getEngine()),
          mMaxIter(maxIter)
    {
    }

    SimulatedAnnealing::SimulatedAnnealing(const Maze& m, int maxIter)
        : mMaze(m), mRandomEngine(mMaze.getEngine()), mMaxIter(maxIter)
    {
    }

    SimulatedAnnealing::SimulatedAnnealing(Maze&& m, int maxIter)
        : mMaze(std::move(m)), mMaxIter(maxIter)
    {
    }
    
    Maze::MazePath<int> SimulatedAnnealing::shortestPath()
    {
        createInitialSolution([this](int cell)
        {
            return mMaze.width() + mMaze.height()
                   - std::abs((cell % mMaze.width()) - mMaze.end().first)
                   + std::abs((cell / mMaze.width()) - mMaze.end().second);
        });

        simAnn([this](int cell)
        {
            return mMaze.width() + mMaze.height()
                   - std::abs((cell % mMaze.width()) - mMaze.end().first)
                   + std::abs((cell / mMaze.width()) - mMaze.end().second);
        },
        [this](const Maze::MazePath<int>& state)
        {
            return mMaze.width() * mMaze.height() - state.length;
        });
        return mSolution;
    }

    Maze::MazePath<int> SimulatedAnnealing::longestPath()
    {
        createInitialSolution([this](int cell)
        {
            return 1;
        });

        simAnn([this](int cell)
        {
            return 1;
        },
        [this](const Maze::MazePath<int>& state)
        {
            return state.length;
        });
        return mSolution;
    }

    template <typename Heuristic>
    void SimulatedAnnealing::createInitialSolution(Heuristic h)
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
            pickRandom(curr, toVisit, parentMap, h);
        }

        while (curr != start)
        {
            mSolution.parentMap[curr] = parentMap[curr];
            if (mMaze.neighbors(curr) > 2) mSolution.intersections.push_back(curr);
            mSolution.length++;
            curr = parentMap[curr];
        }
        mSolution.parentMap[start] = start;
    }

    template <typename CellHeuristics, typename PathHeuristics>
    void SimulatedAnnealing::simAnn(CellHeuristics ch, PathHeuristics ph)
    {
        Maze::MazePath<int> currentState = mSolution;
        for (int k = 0; k < mMaxIter; ++k)
        {
            Maze::MazePath<int> neighbor = getNeighbor(currentState, ch);
            int costDiff = ph(neighbor) - ph(currentState);
            if (costDiff > 0)
            {
                currentState = neighbor;
                if (ph(currentState) > ph(mSolution))
                    mSolution = currentState;
            }
            else
            {
                double random = mRandomEngine.getDoubleInRange(0, 1);
                double T = temperature((double)costDiff / (double)(mMaxIter - k));
                if (random < T) currentState = neighbor;
            }
        }
    }

    template <typename Heuristics>
    void SimulatedAnnealing::pickRandom(int cell, std::stack<int> &toVisit, std::map<int, int> &parentMap, Heuristics h)
    {
        std::set<int> neighborCells;
        int num = mMaze.insertNeighbors(cell, neighborCells);
        double sum = 0;
        for (int neighbor : neighborCells)
        {
            if (parentMap[neighbor] == 0) parentMap[neighbor] = cell;
            sum += h(neighbor);
        }

        std::list<int> tempList;
        while (sum > 0 && num > 0)
        {
            double r = mRandomEngine.getDoubleInRange(0, sum);
            double total = 0;
            int pickedCell;
            for (int neighbor : neighborCells)
            {
                if (h(neighbor) + total >= r)
                {
                    sum -= h(neighbor);
                    num--;
                    pickedCell = neighbor;
                    tempList.push_front(pickedCell);
                    break;
                }
                total += h(neighbor);
            }
            neighborCells.erase(pickedCell);
        }
        for (int neighbor : tempList) toVisit.push(neighbor);
    }

    template <typename Heuristics>
    Maze::MazePath<int> SimulatedAnnealing::getNeighbor(Maze::MazePath<int>& state, Heuristics h)
    {
        Maze::MazePath<int> returnPath;
        std::shuffle(state.intersections.begin(), state.intersections.end(), mRandomEngine.getEngine());
        int i = state.intersections.size() / 2;
        if (findPath(state.intersections[i], returnPath, state, h))
            return returnPath;
        for (int intersection: state.intersections)
            if (findPath(intersection, returnPath, state, h))
                return returnPath;
        return returnPath;
    }

    template <typename Heuristics>
    bool SimulatedAnnealing::findPath(int intersection, Maze::MazePath<int>& newPath, Maze::MazePath<int>& currentPath, Heuristics h)
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
            pickRandom(curr, toVisit, parentMap, h);
        }
        if (curr != end) return false;

        while (curr != start)
        {
            newPath.parentMap[curr] = parentMap[curr];
            if (mMaze.neighbors(curr) > 2) newPath.intersections.push_back(curr);
            newPath.length++;
            curr = parentMap[curr];
        }
        newPath.parentMap[start] = start;

        return true;
    }
}