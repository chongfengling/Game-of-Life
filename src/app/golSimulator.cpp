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

    CLI11_PARSE(app, argc, argv);
    return 0;
}