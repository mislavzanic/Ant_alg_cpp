//
// Created by mislav on 2/10/21.
//

#include "SimAnnGraph.h"

namespace mh {

    SimAnnGraph::SimAnnGraph(const Maze &m, int maxIter)
        : mGraph(m), mRandomEngine(m.getEngine()),
          mMaxIter(maxIter), mMazeWidth(m.width()), mMazeHeight(m.height())
    {
    }

    SimAnnGraph::SimAnnGraph(Maze &&m, int maxIter)
        : mGraph(m), mRandomEngine(m.getEngine()),
          mMaxIter(maxIter), mMazeWidth(m.width()), mMazeHeight(m.height())
    {
    }

    Graph::GraphPath SimAnnGraph::shortestPath()
    {
        createInitialSolution();
        simAnn();
        return mSolution;
    }

    void SimAnnGraph::pickRandom(int cell, std::stack<int> &toVisit, std::map<int, int> &parentMap)
    {
        auto& neighbors = mGraph.getNeighbors(cell);
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
        int start = mGraph.start();
        int end = mGraph.end();
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
            mSolution.vertices.insert(parentMap[curr]);
            mSolution.length += mGraph.getEdgeLength(curr, parentMap[curr]);
            curr = parentMap[curr];
        }

        mSolution.parentMap[start] = start;
    }

    void SimAnnGraph::simAnn()
    {
        Graph::GraphPath currentState = mSolution;
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

    Graph::GraphPath SimAnnGraph::getNeighbor(Graph::GraphPath &state)
    {
        Graph::GraphPath returnPath;
        int random = mRandomEngine.getIntInRange(0, state.vertices.size() - 1);
        auto node = *std::next(state.vertices.begin(), random);
        if (findPath(node, returnPath, state)) return returnPath;
        for (int vertices: state.vertices)
            if (findPath(vertices, returnPath, state)) return returnPath;
        return returnPath;
    }

    bool SimAnnGraph::findPath(int vertex, Graph::GraphPath &newPath, Graph::GraphPath &currentPath)
    {
        int end = mGraph.end();
        int start = mGraph.start();
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

        while (curr != start)
        {
            newPath.parentMap[curr] = parentMap[curr];
            newPath.length += mGraph.getEdgeLength(curr, parentMap[curr]);
            newPath.vertices.insert(parentMap[curr]);
            curr = parentMap[curr];
        }
        newPath.parentMap[start] = start;

        return true;
    }
}

