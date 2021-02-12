#include "MatrixMaze.h"
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

    void MatrixMaze::loadImageFromFile(const std::string &filepath)
    {
        auto* mData = stbi_load(filepath.c_str(), &mWidth, &mHeight, &mChannels, 0);
        assert(mData != nullptr);
        bool* temp = new bool[mWidth * mHeight];
        size_t dataSize = mWidth * mHeight * mChannels;
        int i = 0, j = 0;
        for (auto* p = mData; p != mData + dataSize; p += mChannels)
        {
            if ((bool)(*p))
            {
                temp[i * mWidth + j] = true;
                if (i == 0)
                {
                    mStart = j + i * mWidth;
                }
                else if (i == mHeight - 1)
                {
                    mEnd = j + i * mWidth;
                }

                mVertices.insert(i * mWidth + j);
            }
            else temp[i * mWidth + j] = false;

            j++;
            if (j == mWidth)
            {
                j = 0;
                i++;
            }
        }

        for (int cell : mVertices)
        {
            if (cell % mWidth) mMaze[cell][cell - 1] = 1;
            if ((cell + 1) % mWidth) mMaze[cell][cell + 1] = 1;
            if (cell - mWidth > 0) mMaze[cell][cell - mWidth] = 1;
            if (cell + mWidth < mWidth * mHeight) mMaze[cell][cell + mWidth] = 1;
        }

        delete[] temp;
    }
}
