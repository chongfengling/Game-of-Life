/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golBasicTypes.h"

namespace gol
{
    Grid::Grid(int num_row, int num_col) : row(num_row), col(num_col), cells(row, std::vector<bool>(col, false))
    {
    }

    Grid::Grid(int num_row, int num_col, int num_alive) : Grid(num_row, num_col)
    {
        if (num_row * num_col < num_alive)
        {
            throw std::invalid_argument("The number of alive cells exceed the total number of the grid.");
        }
        // set up random integer generator
        std::mt19937 rng_mt;
        std::uniform_int_distribution<> uniform_int_row(0, num_row - 1);
        std::uniform_int_distribution<> uniform_int_col(0, num_col - 1);
        // count for the number of alive at each stage
        int counts = 0;
        while (counts < num_alive)
        {
            int row = uniform_int_row(rng_mt);

            int col = uniform_int_col(rng_mt);
            if (!(cells[row][col]))
            {
                cells[row][col] = true;
                counts++;
            }
        }
    }

    void Grid::print()
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                // blankspace matters?
                std::cout << (cells[i][j] ? "o " : "- ");
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    bool Grid::get(int row, int col)
    {
        return cells[row][col];
    }

    void Grid::set(int row, int col, bool status)
    {
        cells[row][col] = status;
    }

} // end namespace