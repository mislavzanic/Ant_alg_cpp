#include "Maze.h"
#include "stb_image.h"

#include <cstdlib>

namespace mh {

    Maze::Maze(const std::string& filepath)
    {
        loadImageFromFile(filepath);
    }

    Maze::~Maze()
    {
        delete[] mMaze;
    }

    void Maze::loadImageFromFile(const std::string &filepath)
    {
        int channels;
        stbi_uc *data = stbi_load(filepath.c_str(), &mWidth, &mHeight, &channels, 0);

        size_t dataSize = mWidth * mHeight * channels;
        mMaze = new bool[mHeight * mWidth];
        int i = 0, j = 0;
        for (auto* p = data; p != data + dataSize; p += channels)
        {
            mMaze[i * mWidth + j] = (bool)(*p);
            j++;
            if (j == mWidth)
            {
                j = 0;
                i++;
            }
        }
    }
}
