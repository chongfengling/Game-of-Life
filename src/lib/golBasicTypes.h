/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golBasicTypes_h
#define golBasicTypes_h

/**
 * \defgroup internal internal
 * \brief Internal stuff, not for end-users.
 */

/**
 * \defgroup types types
 * \brief Package-wide data types.
 */

/**
 * \defgroup utilities utilities
 * \brief Groups of c-style functions.
 */

/**
 * \defgroup applications applications
 * \brief Small, end-user applications, most likely command line.
 */

/**
 * \file golBasicTypes.h
 * \brief Defines types and typedefs used in this library.
 * \ingroup types
 */

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <sstream>

//! Single namespace for all code in this package
namespace gol
{

    class Grid
    {
    public:
        // constructor
        Grid(int row, int col);
        // random constructor
        Grid(int row, int col, int num_alive);
        // constructor by reading data from a file
        Grid(std::string filepath);

        void print();
        // get individual cell content
        bool get(int row, int col);
        // get number of row and col
        int get_num_row();
        int get_num_col();
        // set individual cell content
        void set(int row, int col, bool status);
        //
        std::vector<std::vector<bool>> get_cells();
        // fetch alive neighbours
        int alive_nbr_count(int row_index, int col_index);

    private:
        int row;
        int col;
        std::vector<std::vector<bool>> cells;
    };

} // end namespace

#endif
