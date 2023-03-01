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
#include "golGeneration.h"

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

TEST_CASE("Grid: Construct and get function", "[task1_1]")
{
    int row = 5;
    int col = 5;
    gol::Grid grid(row, col);

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            REQUIRE(grid.get(i, j) == false);
        }
    }
}

TEST_CASE("Grid: set function", "[task1_1]")
{
    int row = 5;
    int col = 5;
    gol::Grid grid(row, col);

    grid.set(1, 1, true);
    REQUIRE(grid.get(1, 1) == true);
}

TEST_CASE("The total number of alive cells are correct", "[task1_2]")
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
            if (grid.get(i, j))
            {
                total_num_alive++;
            }
        }
    }
    REQUIRE(total_num_alive == num_alive);
}

TEST_CASE("Different instances different patterns", "[task1_2]")
{
    int row = 50;
    int col = 50;
    int num_alive = 5;
    gol::Grid grid1(row, col, num_alive);

    gol::Grid grid2(row, col, num_alive);
    // two grids could be the same, but the probability can be ignored.
    REQUIRE(grid1.get_cells() != grid2.get_cells());
}

TEST_CASE("Check if the file path is available", "[task1_3]")
{
    std::string filepath = "/workspaces/game-of-life-chongfengling/test/data/glider.txt";
    std::string unknown_filepath = "/workspaces/game-of-life-chongfengling/test/data/Untitled.txt";
    REQUIRE_NOTHROW(gol::Grid(filepath));
    REQUIRE_THROWS(gol::Grid(unknown_filepath));
}

TEST_CASE("The loaded grid is consistent", "[task1_3]")
{
    std::string filepath = "/workspaces/game-of-life-chongfengling/test/data/glider.txt";
    gol::Grid grid(filepath);

    // check the size of grid is consistent
    int row(grid.get_num_row());
    int col(grid.get_num_col());
    REQUIRE(row == 10);
    REQUIRE(row == 10);

    // check the location of alive cells are correct
    REQUIRE(grid.get(1, 2));
    REQUIRE(grid.get(2, 0));
    REQUIRE(grid.get(2, 2));
    REQUIRE(grid.get(3, 1));
    REQUIRE(grid.get(3, 2));

    // check other cells are all dead
    int total_num_alive = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (grid.get(i, j))
            {
                total_num_alive++;
            }
        }
    }
    REQUIRE(total_num_alive == 5);
}

TEST_CASE("Check if the patterns in the file are acceptable.", "[task1_3]")
{
    std::string wrong_pattern_filepath = "/workspaces/game-of-life-chongfengling/test/data/unacceptable_patterns.txt";
    REQUIRE_THROWS(gol::Grid(wrong_pattern_filepath));
}

TEST_CASE("Check if the number of live neighbours fetched correctly.", "[task1_4]")
{
    std::string filepath = "/workspaces/game-of-life-chongfengling/test/data/still_lifes.txt";
    gol::Grid grid(filepath);

    // out of range
    REQUIRE_THROWS(grid.alive_nbr_count(-1, 1));
    REQUIRE_THROWS(grid.alive_nbr_count(100, 2));
    REQUIRE_THROWS(grid.alive_nbr_count(2, 100));
    REQUIRE_THROWS(grid.alive_nbr_count(2, -1));

    // on the edge
    // central cell is dead
    REQUIRE(grid.alive_nbr_count(0, 0) == 1);
    REQUIRE(grid.alive_nbr_count(0, 9) == 0);
    REQUIRE(grid.alive_nbr_count(9, 0) == 2);
    // central cell is alive
    REQUIRE(grid.alive_nbr_count(2, 0) == 2);
    REQUIRE(grid.alive_nbr_count(8, 0) == 2);

    // not on the edge
    // central cell is dead
    REQUIRE(grid.alive_nbr_count(1, 3) == 2);
    REQUIRE(grid.alive_nbr_count(3, 7) == 5);
    // central cell is alive
    REQUIRE(grid.alive_nbr_count(2, 3) == 2);
    REQUIRE(grid.alive_nbr_count(8, 6) == 3);
}

TEST_CASE("Check the 1st role of gol.", "[task2_1]")
{
    std::string filepath = "/workspaces/game-of-life-chongfengling/test/data/glider.txt";
    gol::Grid grid(filepath);
    gol::Simulator sml(grid);
    sml.takeStep();
    // A dead cell with exactly three live neighbours should become a live cell
    // Example 1
    REQUIRE(grid.get(2, 3) == false);
    REQUIRE(grid.alive_nbr_count(2, 3) == 3);
    REQUIRE(sml.get_current_grid()[2].at(3));
    // Example 2
    REQUIRE(grid.get(1, 1) == false);
    REQUIRE(grid.alive_nbr_count(1, 1) == 3);
    REQUIRE(sml.get_current_grid()[1].at(1));
}

TEST_CASE("Check the 2nd role of gol.", "[task2_1]")
{
    std::string filepath = "/workspaces/game-of-life-chongfengling/test/data/glider.txt";
    gol::Grid grid(filepath);
    gol::Simulator sml(grid);
    sml.takeStep();
    // A live cell with two or three live neighbours should stay alive.
    // Example 1
    REQUIRE(grid.get(3, 1));
    REQUIRE(grid.alive_nbr_count(3, 1) > 1); // return of Grid.alive_nbr_count() is int
    REQUIRE(sml.get_current_grid()[3].at(1));
    // Example 2
    REQUIRE(grid.get(3, 2));
    REQUIRE(grid.alive_nbr_count(3, 2) > 1); // return of Grid.alive_nbr_count() is int
    REQUIRE(sml.get_current_grid()[3].at(2));
    // Example 3
    REQUIRE(grid.get(2, 2));
    REQUIRE(grid.alive_nbr_count(2, 2) > 1); // return of Grid.alive_nbr_count() is int
    REQUIRE(sml.get_current_grid()[2].at(2));
}

TEST_CASE("Check the 3rd role of gol.", "[task2_1]")
{
    std::string filepath = "/workspaces/game-of-life-chongfengling/test/data/input.txt";
    gol::Grid grid(filepath);
    gol::Simulator sml(grid);
    sml.takeStep();
    // A live cell with less than two or more than three live neighbours should die.
    // Example 1
    REQUIRE(grid.get(0, 4));
    REQUIRE(grid.alive_nbr_count(0, 4) == 0);
    REQUIRE(sml.get_current_grid()[0].at(4) == false);
    // Example 2
    REQUIRE(grid.get(0, 0));
    REQUIRE(grid.alive_nbr_count(0, 0) == 0);
    REQUIRE(sml.get_current_grid()[0].at(0) == false);
    // Example 3
    REQUIRE(grid.get(3, 2));
    REQUIRE(grid.alive_nbr_count(3, 2) > 3); // =4, return of Grid.alive_nbr_count() is int
    REQUIRE(sml.get_current_grid()[3].at(2) == false);
    // Example 4
    REQUIRE(grid.get(3, 3));
    REQUIRE(grid.alive_nbr_count(3, 3) > 3); // =5, return of Grid.alive_nbr_count() is int
    REQUIRE(sml.get_current_grid()[3].at(3) == false);
}