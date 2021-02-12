//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_MAZEINTERFACE_H
#define MHRAD_MAZEINTERFACE_H

namespace mh {

    class MazeInterface
    {
    public:
        virtual std::vector<std::pair<int, int>>& getNeighbors(int cell) = 0;
        virtual const std::set<int>& getAllVertices() const = 0;
        virtual getStart() const = 0;
        virtual getEnd() const = 0;
        virtual int getMazeWidth() const = 0;
        virtual int getMazeHeight() const = 0;
    };

}



#endif //MHRAD_MAZEINTERFACE_H
