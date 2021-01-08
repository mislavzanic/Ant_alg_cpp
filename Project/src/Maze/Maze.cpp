#include "Maze.h"
#include "stb_image.h"

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
        int channels;
        stbi_uc *data = stbi_load(filepath.c_str(), &mWidth, &mHeight, &channels, 0);
        if (data == nullptr)
        {
            std::cout << "data is null" << std::endl;
            return;
        }
        size_t dataSize = mWidth * mHeight * channels;
        mMaze = new bool[mHeight * mWidth];
        int i = 0, j = 0;
        std::cout << channels << std::endl;
        for (auto* p = data; p != data + dataSize; p += channels)
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
}
