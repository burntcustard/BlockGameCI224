#include "level.h"

// TODO: Add remove or unload method so that the level can be easily cleared.

Level::Level() {} // Could load level with this?...

Level::~Level() {}

void Level::Load(std::vector<std::shared_ptr<Cube>>& gameworld, std::string fileName)
{
    std::ifstream levelFile (fileName); // Open file with input stream. Note to write as well, use fstream.
    std::string line;                   // Individual line from the file.
    std::vector<int> cubeInfo;          // List to store the numbers grabbed to create cube with.
    if (levelFile.is_open())
    {
        getline (levelFile, line); // Get the first line, but do nothing with it.
        while ( getline (levelFile, line) ) // Loop through other lines.
        {
            cubeInfo.clear();
            for (int i = line.length(); i >= 0; i--) // Loop through every character in a line (right to left).
            {
                if (line[i] == ',' || (i == 0)) // If comma found or hit end of line (there's a number on the right)...
                {
                    // There is a bug in the version of MinGW the code::blocks installs, which means that
                    // std:stoi doesn't exist, even though it should in the C++11 standard, so this don't work:
                    // cubeInfo.push_back(std::stoi (line.replace(i, std::string::npos, "")));
                    // So, instead, we're going to use this:
                    int vInt = 0;
                    std::string vString = line.substr(i,std::string::npos); // Get section of line.
                    std::replace(vString.begin(), vString.end(), ',',' ');  // Remove spaces.
                    std::replace(vString.begin(), vString.end(), ' ',' ');  // Remove commas.
                    std::istringstream vStream(vString);                    // Convert to stringStream.
                    if ( !(vStream >> vInt) )                               // Convert to integer.
                        std::cerr << "Failed to load cube info from " << fileName << std::endl;
                    cubeInfo.push_back(vInt);                               // Add the int to the cube's data.
                    line.replace(i, std::string::npos, "");                 // Remove the value looked at from the line.
                }
            }
            gameworld.push_back(std::make_shared<Cube>(cubeInfo[2], cubeInfo[1], cubeInfo[0])); // Create cube at x,y,z.
        }
        levelFile.close(); // Finished loading, so stop looking in the file.
    }
    else std::cout << "Unable to open level file " << fileName << std::endl;
}
