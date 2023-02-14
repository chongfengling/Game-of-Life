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
} // end namespace
