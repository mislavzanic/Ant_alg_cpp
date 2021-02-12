//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_MAZE_H
#define MHRAD_MAZE_H

#include "MazeInterface.h"
#include <string>
#include <stb_image.h>

namespace mh {

    class MatrixMaze : public MazeInterface
    {
    public:

        MatrixMaze(const std::string& filepath);
        MatrixMaze(const MatrixMaze& matrixMaze);
        MatrixMaze(MatrixMaze&& matrixMaze) noexcept;
        ~MatrixMaze();

        virtual std::vector<std::pair<int, int>>& getNeighbors(int cell) const override;
        virtual const std::set<int>& getAllVertices() const override;

        virtual int getStart() const override { return mStart; }
        virtual int getEnd() const override { return mEnd; }
        virtual int getMazeWidth() const override { return mWidth; }
        virtual int getMazeHeight() const override { return mHeight; }

        void modifyImage(std::map<int, int>& path, const std::tuple<uint8_t, uint8_t, uint8_t>& color, const std::string& filename);

    private:
        void loadImageFromFile(const std::string& filepath);

    private:
        int mHeight;
        int mWidth;
        int mChannels;
        int mStart;
        int mEnd;
        bool *mMaze;
        stbi_uc* mData;
    };
}

#endif //MHRAD_MAZE_H
