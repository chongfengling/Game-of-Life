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
        std::mt19937 rng_mt{std::random_device{}()};
        std::uniform_int_distribution<int> uniform_int_row(0, num_row - 1);
        std::uniform_int_distribution<int> uniform_int_col(0, num_col - 1);
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

    Grid::Grid(std::string filepath)
    {
        // file stream
        std::ifstream file(filepath);
        // single line in the file
        std::string line;
        // status of single cell
        std::string status;
        // dimensions of the array in the file
        int row_file = 0;
        int col_file = 0;
        // record the position of alive cells
        std::vector<std::pair<int, int>> alive_cells;
        // read each line
        while (std::getline(file, line))
        {
            col_file = 0;
            std::stringstream ssline(line);
            // split the line by whitespace and iterate single element
            while (std::getline(ssline, status, ' '))
            {
                // if alive, record the position
                if (status == "o")
                {
                    alive_cells.push_back(std::make_pair(row_file, col_file));
                }
                col_file++;
            }
            row_file++;
        }
        // initialize the object
        row = row_file;
        col = col_file;
        cells.resize(row, std::vector<bool>(col, false));
        // set status of alive cells
        for (const auto &cell : alive_cells)
        {
            cells[cell.first][cell.second] = true;
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

    std::vector<std::vector<bool>> Grid::get_cells()
    {
        return cells;
    }

    int Grid::alive_nbr_count(int row_index, int col_index)
    {
        // validation
        // index of row /col starts from 0 or row-1/col-1
        if (row_index >= row || col_index >= col || row_index < 0 || col_index < 0)
        {
            throw std::out_of_range("The input(s) is(are) out of range.");
        }

        int alive_nbr = 0;
        for (int i = std::max(row_index - 1, 0); i <= std::min(row_index + 1, row - 1); i++)
        {
            for (int j = std::max(col_index - 1, 0); j <= std::min(col_index + 1, col - 1); j++)
            {
                if(i != row_index || j != col_index)
                {
                    if (cells[i][j])
                    {
                        alive_nbr++;
                    }
                }
            }
        }

        return alive_nbr;
    }
} // end namespace