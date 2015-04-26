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
        std::map<char, int> getMouse();
    private:
        std::map<int, bool> keys;  // List of keycodes with true/false for pressed/not pressed.
        std::map<char, int> mouse; // char is X or Y or L(eft click) or R(ight click).
};

#endif // INPUT_H
