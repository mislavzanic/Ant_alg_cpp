#include "Maze.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <cstdlib>
#include <iostream>

namespace mh {

    Maze::Maze(const std::string& filepath)
    {
        loadImageFromFile(filepath);
    }

    Maze::Maze(const Maze &maze)
        : mHeight(maze.mHeight), mWidth(maze.mWidth), mStart(maze.mStart), mEnd(maze.mEnd),
          mMaze(new bool[mHeight * mWidth])
    {
        for (int i = 0; i < mWidth * mHeight; ++i) mMaze[i] = maze[i];
    }

    Maze::Maze(Maze &&maze) noexcept
        : mHeight(maze.mHeight), mWidth(maze.mWidth), mStart(maze.mStart), mEnd(maze.mEnd),
          mMaze(maze.mMaze)
    {
        maze.mMaze = nullptr;
    }

    Maze::~Maze()
    {
        delete[] mMaze;
    }

    void Maze::loadImageFromFile(const std::string &filepath)
    {
        mData = stbi_load(filepath.c_str(), &mWidth, &mHeight, &mChannels, 0);
        if (mData == nullptr)
        {
            std::cout << "mData is null" << std::endl;
            return;
        }
        size_t dataSize = mWidth * mHeight * mChannels;
        mMaze = new bool[mHeight * mWidth];
        int i = 0, j = 0;
        for (auto* p = mData; p != mData + dataSize; p += mChannels)
        {
            mMaze[i * mWidth + j] = (bool)(*p);
            if (i == 0 && mMaze[i * mWidth + j] != 0)
            {
                mStart = std::make_pair(j, i);
            }
            else if (i == mHeight - 1 && mMaze[i * mWidth + j])
            {
                mEnd = std::make_pair(j, i);
            }

            j++;
            if (j == mWidth)
            {
                j = 0;
                i++;
            }
        }
    }

    void Maze::modifyImage(std::map<int, int> &path)
    {
        size_t imgSize = mWidth * mHeight * mChannels;
        stbi_uc* newImg = new stbi_uc[imgSize];
        int i = 0;
        for (stbi_uc *p = mData, *np = newImg; p != mData + imgSize; p += mChannels, np += mChannels)
        {
            if (path[i] != 0) *np = 0;
            else *np = *p;
            *(np + 1) = *(p + 1);
            *(np + 2) = *(p + 2);
            if (mChannels == 4) *(np + 3) = *(p + 3);
            i++;
        }

        stbi_write_bmp("new_img.bmp", mWidth, mHeight, mChannels, newImg);
        delete[] newImg;
    }
}
