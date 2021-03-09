//
// Created by mislav on 2/10/21.
//

#include <list>
#include "SimAnnGraph.h"

namespace mh {

    SimAnnGraph::SimAnnGraph(const std::string& filepath, int maxIter)
        : mMaze(std::make_shared<Graph>(filepath)), mRandomEngine(), mMaxIter(maxIter)
    {
    }


    Path SimAnnGraph::solve()
    {
        createInitialSolution();
        simAnn();
        return mSolution;
    }

    void SimAnnGraph::pickRandom(int cell, std::stack<int> &toVisit, std::map<int, int> &parentMap)
    {
        auto& neighbors = mMaze->getNeighbors(cell);
        std::set<int> neighborCells;
        double sum = 0;
        for (auto neighbor : neighbors)
        {
            if (parentMap[neighbor.first] == 0)
                parentMap[neighbor.first] = cell;
            neighborCells.insert(neighbor.first);
            sum += heuristics(neighbor.first);
        }

        int num = neighborCells.size();
        std::list<int> tempList;
        while (sum > 0 && num > 0)
        {
            double r = mRandomEngine.getDoubleInRange(0, sum);
            double total = 0;
            int pickedCell;
            for (int neighbor : neighborCells)
            {
                if (heuristics(neighbor) + total >= r)
                {
                    sum -= heuristics(neighbor);
                    num--;
                    pickedCell = neighbor;
                    tempList.push_front(pickedCell);
                    break;
                }
                total += heuristics(neighbor);
            }
            neighborCells.erase(pickedCell);
        }

        for (int neighbor : tempList) toVisit.push(neighbor);
    }

    void SimAnnGraph::createInitialSolution()
    {
        int start = mMaze->getStart();
        int end = mMaze->getEnd();
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

        mSolution = mMaze->buildPath(start, curr, parentMap);
    }

    void SimAnnGraph::simAnn()
    {
        Path currentState = mSolution;
        for (int k = 0; k < mMaxIter; ++k)
        {
            auto neighbor = getNeighbor(currentState);
            int costDiff = pathHeuristics(neighbor) - pathHeuristics(currentState);
            if (costDiff > 0)
            {
                currentState = neighbor;
                if (pathHeuristics(currentState) > pathHeuristics(mSolution))
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

    Path SimAnnGraph::getNeighbor(Path &state)
    {
        Path returnPath;
        int random = mRandomEngine.getIntInRange(0, state.vertices.size() - 1);
        auto node = *std::next(state.vertices.begin(), random);
        if (findPath(node, returnPath, state)) return returnPath;
        for (int vertices: state.vertices)
            if (findPath(vertices, returnPath, state)) return returnPath;
        return returnPath;
    }

    bool SimAnnGraph::findPath(int vertex, Path &newPath, Path &currentPath)
    {
        int end = mMaze->getEnd();
        int start = mMaze->getStart();
        std::map<int, bool> visited;
        std::map<int, int> parentMap;
        std::stack<int> toVisit;

        toVisit.push(vertex);

        while (vertex != start)
        {
            parentMap[vertex] = currentPath.parentMap[vertex];
            vertex = currentPath.parentMap[vertex];
            visited[vertex] = true;
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

        newPath = mMaze->buildPath(start, curr, parentMap);

        return true;
    }
}

