#ifndef INPUT_H
#define INPUT_H

#include <map>

class input
{
    public:
        input();
        ~input();
        void updateInput();
        std::map<int, bool> getKeys();
        std::pair<int, int> getMouse();
    private:
        std::map<int, bool> keys;  // List of keycodes with true/false for pressed/not pressed.
        std::pair<int, int> mouse; // X and Y movement of mouse cursor
};

#endif // INPUT_H
