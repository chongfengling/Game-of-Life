#include "golSimulator.h"

namespace gol
{
    Simulator::Simulator(Grid &input_grid) : current_grid(input_grid), next_grid(input_grid.get_num_col(), input_grid.get_num_row()) {}
}