//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_MAZEINTERFACE_H
#define MHRAD_MAZEINTERFACE_H

#include <utility>
#include <set>
#include <map>

namespace mh {

    class MazeInterface
    {
    public:
        virtual std::map<int, int>& getNeighbors(int cell) = 0;
        virtual const std::set<int>& getAllVertices() const = 0;
        virtual int getEdgeLength(int vertex1, int vertex2) = 0;
        virtual int getStart() const = 0;
        virtual int getEnd() const = 0;
        virtual int getMazeWidth() const = 0;
        virtual int getMazeHeight() const = 0;
    };


    struct Path
    {
        Path() : length(0) {}

        std::set<int> vertices;
        int length;
        std::map<int, int> parentMap;
        std::map<int, int> edgeLengthMap;
    };

}

#endif //MHRAD_MAZEINTERFACE_H
