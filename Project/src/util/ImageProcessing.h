//
// Created by mislav on 2/12/21.
//

#ifndef MHRAD_IMAGEPROCESSING_H
#define MHRAD_IMAGEPROCESSING_H

#include <string>
#include <cassert>
#include <map>
#include <tuple>

#include <stb_image_write.h>
#include <stb_image.h>

namespace mh {
    bool *readFromFile(const std::string &filepath, int* width, int* height, int* channels, int* start, int* end);
    void writeImage(const std::string& imagepath, const std::string& filepath, std::tuple<int, int, int> color, std::map<int, int>&& parentMap);
    void writeImage(const std::string& imagepath, const std::string& filepath, std::tuple<int, int, int> color, const std::set<int>& vertices);
}

#endif //MHRAD_IMAGEPROCESSING_H
