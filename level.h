#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <sstream> // Needed because stupid bugs, ctrl+f "bug" in level.cpp.
#include <string>  // Should be included in sstream anyway.
#include <algorithm> // For std::replace to replace spaces and commas in string.
#include <vector>
#include <memory>  // For std::shared_ptr
#include "cube.h"

class Level
{
    public:
        Level();
        ~Level();
        void Load(std::vector<std::shared_ptr<Cube>>&, std::string fileName = "level.txt");
    private:

};

#endif
