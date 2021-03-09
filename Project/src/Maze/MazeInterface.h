//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_MAZEINTERFACE_H
#define MHRAD_MAZEINTERFACE_H

#include <utility>
#include <set>
#include <map>

namespace mh {

    struct Path
    {
        Path() : length(0) {}

        std::set<int> vertices;
        int length;
        std::map<int, int> parentMap;
        std::map<int, int> edgeLengthMap;
    };

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
        virtual bool* getMazeMatrix() const = 0;

        Path buildPath(int start, int end, std::map<int, int>& parentMap)
        {
            Path newPath;
            while (end != start)
            {
                int nextVertex = parentMap[end];
                newPath.parentMap[end] = nextVertex;
                newPath.vertices.insert(nextVertex);
                int edgeLength = getEdgeLength(end, nextVertex);
                newPath.length += edgeLength;
                newPath.edgeLengthMap[end] = edgeLength;
                end = nextVertex;
            }
            newPath.parentMap[start] = start;
            return newPath;
        }

        virtual std::map<int, int> getParentMap(Path& path) = 0;
    };
}

#endif //MHRAD_MAZEINTERFACE_H
