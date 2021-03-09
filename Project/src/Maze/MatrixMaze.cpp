#include "MatrixMaze.h"

#include <queue>
#include "util/ImageProcessing.h"

namespace mh {

    MatrixMaze::MatrixMaze(const std::string& filepath)
    {
        mMazeMatrix = readFromFile(filepath, &mWidth, &mHeight, &mChannels, &mStart, &mEnd);

        for (int i = 0; i < mWidth * mHeight; ++i)
        {
            if (mMazeMatrix[i])
            {
                int cell = i;
                mVertices.insert(cell);
                if (cell % mWidth) mMaze[cell][cell - 1] = 1;
                if ((cell + 1) % mWidth) mMaze[cell][cell + 1] = 1;
                if (cell - mWidth > 0) mMaze[cell][cell - mWidth] = 1;
                if (cell + mWidth < mWidth * mHeight) mMaze[cell][cell + mWidth] = 1;
            }
        }
    }

    MatrixMaze::~MatrixMaze()
    {
        delete[] mMazeMatrix;
    }
}
