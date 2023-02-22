#ifndef golSimulator_h
#define golSimulator_h

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
        Simulator(Grid& input_grid);
        void takeStep();
        void printGrid();

    private:
        Grid& current_grid;
        Grid next_grid;
    };
}

#endif