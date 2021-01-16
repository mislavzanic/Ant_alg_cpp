#ifndef MHRAD_BFS_H
#define MHRAD_BFS_H

#include <map>
#include <queue>
#include <algorithm>
#include "Maze/Maze.h"
#include "Random.h"

namespace mh {

    void pickRandom(int cell, std::queue<int>& toVisit, const Maze& m, Random<std::mt19937>& engine, std::map<int, int>& path)
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

    std::map<int, int> BFS(const mh::Maze &m)
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
            pickRandom(curr, Q, m, engine, path);
        }
        std::map<int, int> retPath;
        while (end != start)
        {
            retPath[end] = path[end];
            end = path[end];
        }
        retPath[start] = start;
        return retPath;
    }
}


#endif //MHRAD_BFS_H
