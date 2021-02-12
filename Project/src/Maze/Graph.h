//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_GRAPH_H
#define MHRAD_GRAPH_H


#include <string>
#include <map>
#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <set>
#include <list>
#include <stb_image.h>
#include "util/Random.h"

namespace mh {

    class Maze;

    class Graph
    {
    public:
        struct GraphPath
        {
            GraphPath() : length(0) {}

            std::map<int, int> parentMap;
            std::set<int> vertices;
            std::map<std::pair<int, int>, int> lengthMap;
            int length;
        };

        int getEdgeLength(int v1, int v2);

    public:
        explicit Graph(const Maze& m);

        std::vector<std::pair<int, int>>& getNeighbors(int cell)
        {
            if (!mGraph[cell].empty()) return mGraph[cell];
        }

        const std::set<int>& getAllVertices() const { return mVertices; }
        int start() const { return mStart; }
        int end() const { return mEnd; }

    public:
        std::map<int, std::vector<std::pair<int, int>>> mGraph;
        std::set<int> mVertices;
        int mStart, mEnd;
    };
}


#endif //MHRAD_GRAPH_H
