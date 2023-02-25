#include <golMyFunctions.h>
#include <golExceptionMacro.h>
#include "CLI11.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    CLI::App app("Game of Life Simulation");
    // specify the version
    std::string gol_version{"0.1.0"};
    app.set_version_flag("--version", gol_version);
    // specify the way to create a Grid: use file or use random
    auto use_file = app.add_flag("-f,--file", "Create Grid from a file");
    auto use_random = app.add_flag("-r,--random", "Create Grid randomly");
    use_file->excludes(use_random);
    use_random->excludes(use_file);

    CLI11_PARSE(app, argc, argv);
    return 0;
}