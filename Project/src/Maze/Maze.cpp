#include "Maze.h"
#include <stb_image.h>
#include <stb_image_write.h>

#include <cstdlib>
#include <queue>
#include <algorithm>
#include <cassert>

namespace mh {

    MatrixMaze::MatrixMaze(const std::string& filepath)
    {
        loadImageFromFile(filepath);
    }

    MatrixMaze::MatrixMaze(const MatrixMaze &matrixMaze)
    {
    }

    MatrixMaze::MatrixMaze(MatrixMaze &&matrixMaze) noexcept
    {
    }

    MatrixMaze::~MatrixMaze()
    {
        delete[] mMaze;
    }

    void MatrixMaze::loadImageFromFile(const std::string &filepath)
    {
        mData = stbi_load(filepath.c_str(), &mWidth, &mHeight, &mChannels, 0);
        assert(mData != nullptr);

        size_t dataSize = mWidth * mHeight * mChannels;
        mMaze = new bool[mHeight * mWidth];
        int i = 0, j = 0;
        for (auto* p = mData; p != mData + dataSize; p += mChannels)
        {
            mMaze[i * mWidth + j] = (bool)(*p);
            if (i == 0 && mMaze[i * mWidth + j] != 0)
            {
                mStart = j + i * mWidth;
            }
            else if (i == mHeight - 1 && mMaze[i * mWidth + j])
            {
                mEnd = j + i * mWidth;
            }

            j++;
            if (j == mWidth)
            {
                j = 0;
                i++;
            }
        }
    }

    std::vector<std::pair<int, int>> &MatrixMaze::getNeighbors(int cell) const
    {
        std::vector
    }
}
