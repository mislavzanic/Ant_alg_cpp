#ifndef MHRAD_PATHFINDINGALG_H
#define MHRAD_PATHFINDINGALG_H

#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Maze/MatrixMaze.h"
#include "Random.h"

namespace mh {

    void pick_random(int cell, std::queue<int>& toVisit, const Maze& m, Random<std::mt19937>& engine, std::map<int, int>& path)
    {
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
        {
            {1, cell < m.width() ? -1 : cell - m.width()},
            {2, cell + m.width() > m.width() * m.height() ? -1 : cell + m.width()},
            {3, cell % m.width() ? cell - 1 : -1},
            {4, (cell + 1) % m.width() ? cell + 1 : -1}
        };
        std::shuffle(order.begin(), order.end(), engine.getEngine());
        for(int num : order)
        {
            if (cellIndex[num] != -1 && m[cellIndex[num]])
            {
                toVisit.push(cellIndex[num]);
                if (path[cellIndex[num]] == 0) path[cellIndex[num]] = cell;
            }
        }
    }

    void pick_random(int cell, std::stack<int>& toVisit, const Maze& m, Random<std::mt19937>& engine, std::map<int, int>& path)
    {
        std::array<int, 4> order{1,2,3,4};
        std::map<int, int> cellIndex
                {
                        {1, cell < m.width() ? -1 : cell - m.width()},
                        {2, cell + m.width() > m.width() * m.height() ? -1 : cell + m.width()},
                        {3, cell % m.width() ? cell - 1 : -1},
                        {4, (cell + 1) % m.width() ? cell + 1 : -1}
                };
        std::shuffle(order.begin(), order.end(), engine.getEngine());
        for(int num : order)
        {
            if (cellIndex[num] != -1 && m[cellIndex[num]])
            {
                toVisit.push(cellIndex[num]);
                if (path[cellIndex[num]] == 0) path[cellIndex[num]] = cell;
            }
        }
    }

    Maze::MazePath<int> BFS(const mh::Maze &m)
    {
        Random<std::mt19937> engine;
        int start = m.startAsInt(), end = m.endAsInt();
        std::queue<int> Q;
        std::map<int, int> path;
        Q.push(m.startAsInt());
        std::map<int, bool> visited;
        while (!Q.empty())
        {
            int curr = Q.front();
            Q.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) break;
            pick_random(curr, Q, m, engine, path);
        }
        Maze::MazePath<int> retPath;
        while (end != start)
        {
            retPath.parentMap[end] = path[end];
            retPath.length++;
            end = path[end];
        }
        retPath.parentMap[start] = start;
        return retPath;
    }

    Maze::MazePath<int> DFS(const mh::Maze &m)
    {
        Random<std::mt19937> engine;
        int start = m.startAsInt(), end = m.endAsInt();
        std::stack<int> Q;
        std::map<int, int> path;
        Q.push(m.startAsInt());
        std::map<int, bool> visited;
        while (!Q.empty())
        {
            int curr = Q.top();
            Q.pop();
            if (visited[curr]) continue;
            visited[curr] = true;
            if (curr == end) break;
            pick_random(curr, Q, m, engine, path);
        }
        Maze::MazePath<int> retPath;
        while (end != start)
        {
            retPath.parentMap[end] = path[end];
            retPath.length++;
            end = path[end];
        }
        retPath.parentMap[start] = start;
        return retPath;
    }
}


#endif //MHRAD_PATHFINDINGALG_H
