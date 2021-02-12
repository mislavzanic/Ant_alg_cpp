//
// Created by mislav on 2/12/21.
//

#include <cassert>
#include <queue>

#include "Graph.h"

namespace mh {

    Graph::Graph(const std::string& filepath)
    {
        bool* maze = readFromFile(filepath, &mWidth, &mHeight, &mChannels, &mStart, &mEnd);
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

            int numOfNeighbors = 0;
            if (cell % mWidth && maze[cell - 1]) numOfNeighbors++;
            if ((cell + 1) % mWidth && maze[cell + 1]) numOfNeighbors++;
            if (cell - mWidth > 0 && maze[cell - mWidth]) numOfNeighbors++;
            if (cell + mWidth < mHeight * mWidth && maze[cell + mWidth]) numOfNeighbors++;

            if (!visited[cell].empty())
            {
                if (numOfNeighbors > 2) continue;
                if (!visitedNeighbors[{cell, neighbor}])
                {
                    for (auto& vertices : visited[cell])
                    {
                        if (!pairMap[{neighbor, vertices.first}])
                        {
                            mMaze[neighbor][vertices.first] = length + vertices.second;
                            mMaze[vertices.first][neighbor] = length + vertices.second;
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
            if (maze[cell] && (numOfNeighbors > 2 || numOfNeighbors == 1))
            {
                mMaze[cell][neighbor] = length;
                mMaze[neighbor][cell] = length;
                pairMap[{neighbor, cell}] = true;
                pairMap[{cell, neighbor}] = true;
                mVertices.insert(cell);
                neighbor = cell;
                length = 0;
            }

            if (cell % mWidth && maze[cell - 1])
            {
                if (visited[cell - 1].empty())
                    Q.push({cell - 1, length + 1, neighbor});
            }
            if ((cell + 1) % mWidth && maze[cell + 1])
            {
                if (visited[cell + 1].empty())
                    Q.push({cell + 1, length + 1, neighbor});
            }
            if (cell - mWidth > 0 && maze[cell - mWidth])
            {
                if (visited[cell - mWidth].empty())
                    Q.push({cell - mWidth, length + 1, neighbor});
            }
            if (cell + mWidth < mHeight * mWidth && maze[cell + mWidth])
            {
                if (visited[cell + mWidth].empty())
                    Q.push({cell + mWidth, length + 1, neighbor});

            }
        }

        delete[] maze;
    }
}