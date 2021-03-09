#ifndef MHRAD_PATHFINDINGALG_H
#define MHRAD_PATHFINDINGALG_H

#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Maze/MatrixMaze.h"
#include "Maze/Graph.h"
#include "Maze/MazeInterface.h"
#include "Random.h"

namespace mh {

    template <typename T>
    void pickRandom(int cell, T& toVisit, MazeInterface& m, Random<std::mt19937>& engine, std::map<int, int>& path)
    {
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
        {
            {1, cell < m.getMazeWidth() ? -1 : cell - m.getMazeWidth()},
            {2, cell + m.getMazeWidth() > m.getMazeWidth() * m.getMazeHeight() ? -1 : cell + m.getMazeWidth()},
            {3, cell % m.getMazeWidth() ? cell - 1 : -1},
            {4, (cell + 1) % m.getMazeWidth() ? cell + 1 : -1}
        };
        std::shuffle(order.begin(), order.end(), engine.getEngine());
        for(int num : order)
        {
            if (cellIndex[num] != -1 && m.getMazeMatrix()[cellIndex[num]])
            {
                toVisit.push(cellIndex[num]);
                if (path[cellIndex[num]] == 0) path[cellIndex[num]] = cell;
            }
        }
    }

    Path BFS(MazeInterface &m)
    {
        Random<std::mt19937> engine;
        int start = m.getStart(), end = m.getEnd();
        std::queue<int> Q;
        std::map<int, int> path;
        Q.push(m.getStart());
        std::map<int, bool> visited;
        while (!Q.empty())
        {
            int curr = Q.front();
            Q.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) break;
            pickRandom(curr, Q, m, engine, path);
        }
        return m.buildPath(start, end, path);
    }

    Path DFS(mh::MazeInterface &m)
    {
        Random<std::mt19937> engine;
        int start = m.getStart(), end = m.getEnd();
        std::stack<int> Q;
        std::map<int, int> path;
        Q.push(m.getStart());
        std::map<int, bool> visited;
        while (!Q.empty())
        {
            int curr = Q.top();
            Q.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) break;
            pickRandom(curr, Q, m, engine, path);
        }
        return m.buildPath(start, end, path);
    }
}


#endif //MHRAD_PATHFINDINGALG_H
