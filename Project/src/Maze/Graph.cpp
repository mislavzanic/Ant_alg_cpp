//
// Created by mislav on 2/12/21.
//

#include <cassert>
#include "Maze.h"

#include "Graph.h"

namespace mh {

    Graph::Graph(const Maze &m)
            : mStart(m.startAsInt()), mEnd(m.endAsInt())
    {
        std::queue<std::tuple<int, int, int>> Q;
        Q.push({mStart, 0, mStart});
        std::map<std::pair<int, int>, bool> visitedNeighbors;
        std::map<int, std::vector<std::pair<int, int>>> visited;
        std::map<std::pair<int, int>, bool> pairMap;
        while (!Q.empty())
        {
            auto next = Q.front();
            Q.pop();
            int cell = std::get<0>(next);
            int length = std::get<1>(next);
            int neighbor = std::get<2>(next);
            if (!visited[cell].empty())
            {
                if (m.neighbors(cell) > 2) continue;
                if (!visitedNeighbors[{cell, neighbor}])
                {
                    for (auto& vertices : visited[cell])
                    {
                        if (!pairMap[{neighbor, vertices.first}])
                        {
                            mGraph[neighbor].push_back({vertices.first, length + vertices.second});
                            mGraph[vertices.first].push_back({neighbor, length + vertices.second});
                            pairMap[{neighbor, vertices.first}] = true;
                            pairMap[{vertices.first, neighbor}] = true;
                        }
                    }

                    visitedNeighbors[{cell, neighbor}] = true;
                    visited[cell].push_back({neighbor, length});
                }
                continue;
            }
            visited[cell].push_back({neighbor, length});
            visitedNeighbors[{cell, neighbor}] = true;
            if (m[cell] && (m.neighbors(cell) > 2 || m.neighbors(cell) == 1))
            {
                mGraph[cell].push_back({neighbor, length});
                mGraph[neighbor].push_back({cell, length});
                pairMap[{neighbor, cell}] = true;
                pairMap[{cell, neighbor}] = true;
                mVertices.insert(cell);
                neighbor = cell;
                length = 0;
            }

            std::set<int> temp;
            m.insertNeighbors(cell, temp);
            for (int nextCell : temp)
            {
                if (visited[nextCell].empty())
                    Q.push({nextCell, length + 1, neighbor});
            }
        }
    }

    int Graph::getEdgeLength(int v1, int v2)
    {
        auto& neighbors = getNeighbors(v1);
        for (auto neighbor : neighbors)
        {
            if (neighbor.first == v2) return neighbor.second;
        }
        std::cout << v1 << " " << v2 << std::endl;
        assert(false);
    }
}