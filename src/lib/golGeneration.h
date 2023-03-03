#ifndef golGeneration_h
#define golGeneration_h

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include "golBasicTypes.h"

namespace gol
{
    class Simulator
    {
    public:
        Simulator(Grid input_grid);
        void takeStep();
        void printGrid();
        std::vector<std::vector<bool>> get_last_grid();
        std::vector<std::vector<bool>> get_current_grid();
        std::vector<std::vector<bool>> get_next_grid();

    private:
        // three grid to store three status
        Grid last_grid;
        Grid current_grid;
        Grid next_grid;
    };
}

#endif