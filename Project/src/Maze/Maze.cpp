#include "Maze.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <cstdlib>
#include <queue>
#include <iostream>
#include <algorithm>
#include <util/StopWatch.h>

namespace mh {

    Maze::Maze(const std::string& filepath)
    {
        loadImageFromFile(filepath);
    }

    Maze::Maze(const Maze &maze)
        : mHeight(maze.mHeight), mWidth(maze.mWidth), mStart(maze.mStart), mEnd(maze.mEnd),
          mMaze(new bool[mHeight * mWidth]), mRandEngine(maze.mRandEngine)
    {
        for (int i = 0; i < mWidth * mHeight; ++i) mMaze[i] = maze[i];
    }

    Maze::Maze(Maze &&maze) noexcept
        : mHeight(maze.mHeight), mWidth(maze.mWidth), mStart(maze.mStart), mEnd(maze.mEnd),
          mMaze(maze.mMaze), mRandEngine(std::move(maze.mRandEngine))
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

    void Maze::modifyImage(std::map<int, int> &path, const std::tuple<uint8_t, uint8_t, uint8_t>& color, const std::string& filename)
    {
        size_t imgSize = mWidth * mHeight * mChannels;
        stbi_uc* newImg = new stbi_uc[imgSize];
        int i = 0;
        for (stbi_uc *p = mData, *np = newImg; p != mData + imgSize; p += mChannels, np += mChannels)
        {
            if (path[i] != 0)
            {
                *np = std::get<0>(color);
                *(np + 1) = std::get<1>(color);
                *(np + 2) = std::get<2>(color);
            }
            else
            {
                *np = *p;
                *(np + 1) = *(p + 1);
                *(np + 2) = *(p + 2);
            }
            if (mChannels == 4) *(np + 3) = *(p + 3);
            i++;
        }

        stbi_write_bmp(filename.c_str(), mWidth, mHeight, mChannels, newImg);
        delete[] newImg;
    }

    int Maze::neighbors(int cell) const
    {
        int num = 0;
        std::pair<int, int> cellAsPair = intToPair(cell);
        if (cellAsPair.first > 0 && mMaze[cell - 1]) num += 1;
        if (cellAsPair.first < mWidth - 1 && mMaze[cell + 1]) num += 1;
        if (cellAsPair.second > 0 && mMaze[cell - mWidth]) num += 1;
        if (cellAsPair.second < mHeight - 1 && mMaze[cell + mWidth]) num += 1;

        return num;
    }

    int Maze::insertNeighbors(int cell, std::set<int> &neighborSet) const
    {
        int num = 0;
        std::pair<int, int> cellAsPair = intToPair(cell);
        if (cellAsPair.first > 0 && mMaze[cell - 1])
        {
            neighborSet.insert(cell - 1);
            num++;
        }
        if (cellAsPair.first < mWidth - 1 && mMaze[cell + 1])
        {
            neighborSet.insert(cell + 1);
            num++;
        }
        if (cellAsPair.second > 0 && mMaze[cell - mWidth])
        {
            neighborSet.insert(cell - mWidth);
            num++;
        }
        if (cellAsPair.second < mHeight - 1 && mMaze[cell + mWidth])
        {
            neighborSet.insert(cell + mWidth);
            num++;
        }

        return num;
    }

    Graph::Graph(const Maze &m)
        : mStart(m.startAsInt()), mEnd(m.endAsInt())
    {
        std::queue<std::tuple<int, int, int>> Q;
        Q.push({mStart, 0, mStart});
        std::map<int, bool> visited;
        while (!Q.empty())
        {
            auto next = Q.front();
            Q.pop();
            int cell = std::get<0>(next);
            int length = std::get<1>(next);
            int neighbor = std::get<2>(next);
            if (visited[cell]) continue;
            visited[cell] = true;
            if (m[cell] && (m.neighbors(cell) > 2 || m.neighbors(cell) == 1))
            {
                mGraph[cell].push_back({neighbor, length});
                mGraph[neighbor].push_back({cell, length});
                mVertices.insert(cell);
                neighbor = cell;
                length = 0;
            }

            std::set<int> temp;
            m.insertNeighbors(cell, temp);
            for (int nextCell : temp)
            {
                Q.push({nextCell, length + 1, neighbor});
            }
        }
    }

    int Graph::bfs()
    {
        auto cmp = [](std::pair<int, int> a, std::pair<int, int> b){return a.second > b.second;};
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> Q(cmp);
        std::map<int, bool> bio;
        std::map<int, int> parentMap;
        Q.push({mStart, 0});

        while (!Q.empty())
        {
            int cell = Q.top().first;
            int len = Q.top().second;
            Q.pop();
            if (bio[cell]) continue;
            bio[cell] = true;
            if (cell == mEnd) break;
            auto& v = getNeighbors(cell);
            for (auto& vv : v)
            {
                Q.push({vv.first, vv.second});
                if (parentMap[vv.first] == 0) parentMap[vv.first] = cell;
            }
        }
        int end = mEnd;
        int len = 0;
        while (end != mStart)
        {
            for (auto& vv : mGraph[end])
            {
                if (vv.first == parentMap[end])
                {
                    len += vv.second;
                    end = parentMap[end];
                    break;
                }
            }
        }
        return len;
    }

    int Graph::getEdgeLength(int v1, int v2)
    {
        auto& neighbors = getNeighbors(v1);
        for (auto neighbor : neighbors)
        {
            if (neighbor.first == v2) return neighbor.second;
        }
        std::cout << v1 << " " << v2 << std::endl;
        assert(false);
    }
}
