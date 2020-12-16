//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_MAZE_H
#define MHRAD_MAZE_H

#include <string>

namespace mh {

    class Maze
    {
    public:
        Maze(const std::string& filepath);
        ~Maze();

        const bool& operator[](int index) const { return mMaze[index]; }
        bool& operator[](int index) { return mMaze[index]; }

        int Start() { return mStart; }
        int End() { return mEnd; }
        int Width() { return mCols; }
        int Height() { return mRows; }

    private:
        void loadImageFromFile(const std::string& filepath);

    private:
        int mRows;
        int mCols;
        int mStart;
        int mEnd;
        bool *mMaze;
    };
}

#endif //MHRAD_MAZE_H
