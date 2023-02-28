#include "golGeneration.h"

namespace gol
{
    Simulator::Simulator(Grid &input_grid) : current_grid(input_grid), next_grid(input_grid.get_num_col(), input_grid.get_num_row()), last_grid(input_grid.get_num_col(), input_grid.get_num_row()) {}

    void Simulator::takeStep()
    {
        int num_row = current_grid.get_num_row();
        int num_col = current_grid.get_num_col();
        for (int index_row = 0; index_row < num_row; ++index_row)
        {
            for (int index_col = 0; index_col < num_col; index_col++)
            {
                bool current_status = current_grid.get(index_row, index_col);
                int alive_nbr = current_grid.alive_nbr_count(index_row, index_col);
                // role i
                if ((!current_status) & alive_nbr == 3)
                {
                    next_grid.set(index_row, index_col, true);
                }
                // role ii & role iii
                if (current_status)
                {
                    if (alive_nbr == 2 || alive_nbr == 3)
                    {
                        next_grid.set(index_row, index_col, true);
                    }
                }
            }
        }
        std::swap(last_grid, current_grid);
        std::swap(current_grid, next_grid);
        next_grid.reset();
    }

    void Simulator::printGrid()
    {
        std::cout << "current grid \n";
        current_grid.print();
    }

    std::vector<std::vector<bool>> Simulator::get_last_grid()
    {
        return last_grid.get_cells();
    }

    std::vector<std::vector<bool>> Simulator::get_current_grid()
    {
        return current_grid.get_cells();
    }

    std::vector<std::vector<bool>> Simulator::get_next_grid()
    {
        return next_grid.get_cells();
    }

}