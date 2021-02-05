//
// Created by mislav on 12/12/20.
//

#ifndef MHRAD_MAZE_H
#define MHRAD_MAZE_H

#include <string>
#include <map>
#include <iostream>
#include <stack>
#include <array>
#include <set>
#include <list>
#include <stb_image.h>
#include "util/Random.h"

namespace mh {

    class Maze
    {
    public:
        template <typename T> 
        struct MazePath
        {
            std::map<T, T> parentMap;
            std::vector<T> intersections;
            size_t length = 0;
        };
        
    public:
        explicit Maze(const std::string& filepath);
        Maze(const Maze &maze);
        Maze(Maze &&maze) noexcept;

        ~Maze();

        const bool& operator[](int index) const { return mMaze[index]; }
        bool& operator[](int index) { return mMaze[index]; }

        int startAsInt() const { return pairToInt(mStart); }
        int endAsInt() const { return pairToInt(mEnd); }
        std::pair<int, int> start() const { return mStart; }
        std::pair<int, int> end() const { return mEnd; }
        int width() const { return mWidth; }
        int height() const { return mHeight; }

        int neighbors(int cell) const;
        int insertNeighbors(int cell, std::set<int>& neighborSet) const;

        int pairToInt(const std::pair<int, int> coord) const { return coord.first + coord.second * mWidth; }
        std::pair<int, int> intToPair(int coord) const { return std::make_pair<int, int>(coord % mWidth, coord / mWidth); }

        const Random<std::mt19937> & getEngine() const { return mRandEngine; };

        void modifyImage(std::map<int, int>& path, const std::tuple<uint8_t, uint8_t, uint8_t>& color, const std::string& filename);

    private:
        void loadImageFromFile(const std::string& filepath);

    public:

        int crossroads()
        {
            int num = 0;
            for (int i = 0; i < mWidth * mHeight; ++i)
            {
                if (mMaze[i] && (neighbors(i) > 2 || neighbors(i) == 1))
                {
                    num++;
                }
            }

            return num;
        }

    private:
        int mHeight;
        int mWidth;
        int mChannels;
        std::pair<int, int> mStart;
        std::pair<int, int> mEnd;
        bool *mMaze;
        stbi_uc* mData;

        Random<std::mt19937> mRandEngine;
    };

    class Graph
    {
    public:
        using Vertex = std::pair<int, int>;

        struct GraphPath
        {
            GraphPath() : length(0) {}
            std::set<int> vertices;
            int length;
        };

        int getEdgeLength(int v1, int v2);

    public:
        explicit Graph(const Maze& m);
        int bfs();

        std::vector<Vertex>& getNeighbors(int cell)
        {
            if (!mGraph[cell].empty()) return mGraph[cell];
        }

        const std::set<int>& getAllVertices() { return mVertices; }
        int start() const { return mStart; }
        int end() const { return mEnd; }



    private:
        std::map<int, std::vector<Vertex>> mGraph;
        std::set<int> mVertices;
        int mStart, mEnd;
    };

}

#endif //MHRAD_MAZE_H
