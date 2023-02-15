/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include <iostream>
#include <vector>
#include "golBasicTypes.h"

TEST_CASE("My first test", "[some group identifier]")
{
    int a = 5;
    REQUIRE(a < 6);
}

TEST_CASE("My second test", "[some group identifier]")
{
    std::vector<int> a;
    REQUIRE(a.size() == 0);
}

TEST_CASE("Simple add", "[MyFirstAddFunction]")
{
    REQUIRE(gol::MyFirstAddFunction(1, 2) == 3);
}

TEST_CASE("Grid: Construct and get function", "[Grid construct]")
{
    int row = 5;
    int col = 5;
    gol::Grid grid(row, col);

    // grid.print();

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            REQUIRE(grid.get(i, j) == false);
        }
    }
}

TEST_CASE("Grid: set function", "[Grid construct]")
{
    int row = 5;
    int col = 5;
    gol::Grid grid(row, col);

    grid.set(1, 1, true);
    REQUIRE(grid.get(1, 1) == true);
}

TEST_CASE("Random initialization", "[task1_2]")
{
    int row = 5;
    int col = 6;
    int num_alive = 10;
    gol::Grid grid(row, col, num_alive);

    int total_num_alive = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if(grid.get(i,j)){
                total_num_alive++;
            }
        }
    }
    REQUIRE(total_num_alive == num_alive);
}

TEST_CASE("Different instances different patterns", "[task1_2]")
{
    int row = 10;
    int col = 10;
    int num_alive = 5;
    gol::Grid grid1(row, col, num_alive);
    grid1.print();

    gol::Grid grid2(row, col, num_alive);
    grid2.print();
    // two grids could be the same, but the probability can be ignored.
    REQUIRE(grid1.get_cells() != grid2.get_cells());
}