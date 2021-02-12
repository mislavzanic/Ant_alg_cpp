//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_MAZEINTERFACE_H
#define MHRAD_MAZEINTERFACE_H

#include <vector>
#include <utility>
#include <set>

namespace mh {

    class MazeInterface
    {
    public:
        virtual std::vector<std::pair<int, int>>& getNeighbors(int cell) const = 0;
        virtual const std::set<int>& getAllVertices() const = 0;
        virtual int getStart() const = 0;
        virtual int getEnd() const = 0;
        virtual int getMazeWidth() const = 0;
        virtual int getMazeHeight() const = 0;
    };

}

#endif //MHRAD_MAZEINTERFACE_H
