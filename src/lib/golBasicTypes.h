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

        void print();
        // get individual cell content
        bool get(int row, int col);
        // set individual cell content
        void set(int row, int col, bool status);

    private:
        int row;
        int col;
        std::vector<std::vector<bool>> cells;
    };

} // end namespace

#endif
