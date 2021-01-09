//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_MAZE_H
#define MHRAD_MAZE_H

#include <string>
#include <map>
#include <stb_image.h>

namespace mh {

    class Maze
    {
    public:
        Maze(const std::string& filepath);
        Maze(const Maze &maze);
        Maze(Maze &&maze) noexcept;

        ~Maze();

        const bool& operator[](int index) const { return mMaze[index]; }
        bool& operator[](int index) { return mMaze[index]; }

        int startAsInt() const { return mStart.first + mStart.second * mWidth; }
        int endAsInt() const { return mEnd.first + mEnd.second * mWidth; }
        std::pair<int, int> start() const { return mStart; }
        std::pair<int, int> end() const { return mEnd; }
        int width() const { return mWidth; }
        int height() const { return mHeight; }

        void modifyImage(std::map<int, int>& path);

    private:
        void loadImageFromFile(const std::string& filepath);

    private:
        int mHeight;
        int mWidth;
        int mChannels;
        std::pair<int, int> mStart;
        std::pair<int, int> mEnd;
        bool *mMaze;
        stbi_uc* mData;
    };
}

#endif //MHRAD_MAZE_H
