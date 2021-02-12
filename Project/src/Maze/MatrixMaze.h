//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_MATRIXMAZE_H
#define MHRAD_MATRIXMAZE_H

#include "MazeInterface.h"
#include <string>
#include <stb_image.h>
#include <map>

namespace mh {

    class MatrixMaze : public MazeInterface
    {
    public:

        MatrixMaze(const std::string& filepath);
        MatrixMaze(const MatrixMaze& matrixMaze);
        MatrixMaze(MatrixMaze&& matrixMaze) noexcept;

        virtual  std::map<int, int>& getNeighbors(int cell) override { return mMaze[cell]; }
        virtual const std::set<int>& getAllVertices() const override { return mVertices; }
        virtual int getEdgeLength(int vertex1, int vertex2) override { return mMaze[vertex1][vertex2]; }

        virtual int getStart() const override { return mStart; }
        virtual int getEnd() const override { return mEnd; }
        virtual int getMazeWidth() const override { return mWidth; }
        virtual int getMazeHeight() const override { return mHeight; }

        static void writeToFile(std::map<int, int> parentMap, std::tuple<int, int, int> color, const std::string& filepath);

    private:
        void loadImageFromFile(const std::string& filepath);

    private:
        int mHeight;
        int mWidth;
        int mChannels;
        int mStart;
        int mEnd;
        std::map<int, std::map<int, int>> mMaze;
        std::set<int> mVertices;
    };
}

#endif //MHRAD_MATRIXMAZE_H
