//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_GRAPH_H
#define MHRAD_GRAPH_H

#include "MazeInterface.h"
#include <map>
#include <string>
#include <queue>
#include <set>
#include <stb_image.h>

namespace mh {

    class Graph : public MazeInterface
    {
    public:

        Graph(const std::string& filepath);
        ~Graph();

        virtual std::map<int, int>& getNeighbors(int cell) override { return mMaze[cell]; }
        virtual const std::set<int>& getAllVertices() const override { return mVertices; }
        virtual int getEdgeLength(int vertex1, int vertex2) override { return mMaze[vertex1][vertex2]; }

        virtual int getStart() const override { return mStart; }
        virtual int getEnd() const override { return mEnd; }
        virtual int getMazeWidth() const override { return mWidth; }
        virtual int getMazeHeight() const override { return mHeight; }

        virtual std::map<int, int> getParentMap(Path& path) override;

        virtual bool* getMazeMatrix() const override { return mMatrix; }

    private:

        std::map<int, int> getCorrectPath(std::pair<int, int>& vertices, int edgeLength);
        void convertToGraph();
        int numOfNeighbors(int cell);
        void pickNext(int cell, int length, int neighbor, std::queue<std::tuple<int, int, int>>& Q, std::map<int, std::map<int, int>>& visited);

    private:
        std::map<int, std::map<int, int>> mMaze;
        std::set<int> mVertices;
        int mStart, mEnd;
        int mWidth, mHeight, mChannels;
        bool* mMatrix;
    };
}


#endif //MHRAD_GRAPH_H
