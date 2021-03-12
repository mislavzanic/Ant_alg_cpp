//
// Created by mislav on 2/12/21.
//

#include <queue>
#include <stack>
#include <iostream>

#include "Graph.h"
#include "util/ImageProcessing.h"

namespace mh {

    Graph::Graph(const std::string& filepath)
    {
        mMatrix = readFromFile(filepath, &mWidth, &mHeight, &mChannels, &mStart, &mEnd);
        convertToGraph();
    }

    Graph::~Graph()
    {
        delete[] mMatrix;
    }

    std::map<int, int> Graph::getParentMap(Path &path)
    {
        std::map<int, int> parentMap;
        for (std::pair<int, int> vertices : path.parentMap)
        {
            auto subMap = getCorrectPath(vertices, path.edgeLengthMap[vertices.first]);
            for (auto v : subMap)
            {
                parentMap[v.first] = v.second;
            }
        }

        return parentMap;
    }

    std::map<int, int> Graph::getCorrectPath(std::pair<int, int> &vertices, int edgeLength)
    {
        std::map<int, int> parentMap;
        std::map<int, int> path;
        int start = vertices.first;
        int end = vertices.second;
        std::stack<std::pair<int, int>> S;
        std::map<int, bool> visited;
        S.push({start, 0});
        while (!S.empty())
        {
            int curr = S.top().first;
            int currLength = S.top().second;
            S.pop();
            if (curr == end && currLength == edgeLength) break;
            if (visited[curr] || curr == end || currLength > edgeLength) continue;
            visited[curr] = true;
            if (curr % mWidth && mMatrix[curr - 1] && !visited[curr - 1])
            {
                S.push({curr - 1, currLength + 1});
                path[curr - 1] = curr;
            }
            if ((curr + 1) % mWidth && mMatrix[curr + 1] && !visited[curr + 1])
            {
                S.push({curr + 1, currLength + 1});
                path[curr + 1] = curr;
            }
            if (curr - mWidth > 0 && mMatrix[curr - mWidth] && !visited[curr - mWidth])
            {
                S.push({curr - mWidth, currLength + 1});
                path[curr - mWidth] = curr;
            }
            if (curr + mWidth < mHeight * mWidth && mMatrix[curr + mWidth] && !visited[curr + mWidth])
            {
                S.push({curr + mWidth, currLength + 1});
                path[curr + mWidth] = curr;
            }
        }

        while (end != start)
        {
            parentMap[end] = path[end];
            end = path[end];
        }
        parentMap[start] = start;

        return parentMap;
    }

    int Graph::numOfNeighbors(int cell)
    {
        int numOfNeighbors = 0;
        if (cell % mWidth && mMatrix[cell - 1]) numOfNeighbors++;
        if ((cell + 1) % mWidth && mMatrix[cell + 1]) numOfNeighbors++;
        if (cell - mWidth > 0 && mMatrix[cell - mWidth]) numOfNeighbors++;
        if (cell + mWidth < mHeight * mWidth && mMatrix[cell + mWidth]) numOfNeighbors++;
        return numOfNeighbors;
    }

    void Graph::convertToGraph()
    {
        std::queue<std::tuple<int, int, int>> Q;
        Q.push({mStart, 0, mStart});
        std::map<std::pair<int, int>, bool> visitedNeighbors;
        std::map<int, std::map<int, int>> visited;
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
                if (numOfNeighbors(cell) > 2) continue;
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

                    visited[cell][neighbor] = length;
                }
                continue;
            }
            visited[cell][neighbor] = length;
            visitedNeighbors[{cell, neighbor}] = true;
            if (mMatrix[cell] && (numOfNeighbors(cell) > 2 || numOfNeighbors(cell) == 1))
            {
                mMaze[cell][neighbor] = length;
                mMaze[neighbor][cell] = length;
                pairMap[{neighbor, cell}] = true;
                pairMap[{cell, neighbor}] = true;
                mVertices.insert(cell);
                neighbor = cell;
                length = 0;
            }

            pickNext(cell, length, neighbor, Q, visited);
        }
    }

    void Graph::pickNext(int cell, int length, int neighbor, std::queue<std::tuple<int, int, int>>& Q, std::map<int, std::map<int, int>>& visited)
    {
        if (cell % mWidth && mMatrix[cell - 1])
        {
            if (visited[cell - 1].empty())
                Q.push({cell - 1, length + 1, neighbor});
        }
        if ((cell + 1) % mWidth && mMatrix[cell + 1])
        {
            if (visited[cell + 1].empty())
                Q.push({cell + 1, length + 1, neighbor});
        }
        if (cell - mWidth > 0 && mMatrix[cell - mWidth])
        {
            if (visited[cell - mWidth].empty())
                Q.push({cell - mWidth, length + 1, neighbor});
        }
        if (cell + mWidth < mHeight * mWidth && mMatrix[cell + mWidth])
        {
            if (visited[cell + mWidth].empty())
                Q.push({cell + mWidth, length + 1, neighbor});
        }
    }
}