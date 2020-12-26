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

        int Start() const { return mStart; }
        int End() const { return mEnd; }
        int Width() const { return mWidth; }
        int Height() const { return mHeight; }

    private:
        void loadImageFromFile(const std::string& filepath);

    private:
        int mHeight;
        int mWidth;
        int mStart;
        int mEnd;
        bool *mMaze;
    };
}

#endif //MHRAD_MAZE_H
