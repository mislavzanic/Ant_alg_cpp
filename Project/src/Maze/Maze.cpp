#include "Maze.h"
#include "stb_image.h"

#include <cstdlib>

namespace mh {

    Maze::Maze(const std::string& filepath)
    {
        loadImageFromFile(filepath);
        mRows = mCols = 100;
        mMaze = new bool[mRows * mCols];
    }

    Maze::~Maze()
    {
        delete[] mMaze;
    }

    void Maze::loadImageFromFile(const std::string &filepath)
    {
        //  TODO....
    }
}
