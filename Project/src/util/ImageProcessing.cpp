//
// Created by mislav on 2/14/21.
//

#include "ImageProcessing.h"

namespace mh {

    bool *readFromFile(const std::string &filepath, int *width, int *height, int *channels, int *start, int *end) {
        stbi_uc *data = stbi_load(filepath.c_str(), width, height, channels, 0);
        assert(data != nullptr);
        bool *temp = new bool[(*width) * (*height)];
        size_t dataSize = (*width) * (*height) * (*channels);
        int i = 0, j = 0;
        for (auto *p = data; p != data + dataSize; p += (*channels)) {
            if ((bool) (*p)) {
                temp[i * (*width) + j] = true;
                if (i == 0) {
                    (*start) = j + i * (*width);
                } else if (i == (*height) - 1) {
                    (*end) = j + i * (*width);
                }
            } else temp[i * (*width) + j] = false;

            j++;
            if (j == (*width)) {
                j = 0;
                i++;
            }
        }
        return temp;
    }

    void writeImage(const std::string& imagepath, const std::string &filepath, std::tuple<int, int, int> color, std::map<int, int> &&parentMap) {
        int width, height, channels;
        stbi_uc *data = stbi_load(imagepath.c_str(), &width, &height, &channels, 0);
        size_t imgSize = width * height * channels;
        auto *newImg = new stbi_uc[imgSize];
        int i = 0;
        for (stbi_uc *p = data, *np = newImg; p != data + imgSize; p += channels, np += channels) {
            if (parentMap[i] != 0) {
                *np = std::get<0>(color);
                *(np + 1) = std::get<1>(color);
                *(np + 2) = std::get<2>(color);
            } else {
                *np = *p;
                *(np + 1) = *(p + 1);
                *(np + 2) = *(p + 2);
            }
            if (channels == 4) *(np + 3) = *(p + 3);
            i++;
        }

        stbi_write_bmp(filepath.c_str(), width, height, channels, newImg);
        delete[] newImg;
    }
}