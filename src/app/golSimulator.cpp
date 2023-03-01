#include <golMyFunctions.h>
#include <golExceptionMacro.h>
#include "CLI11.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void generation(gol::Simulator &sml, int steps)
{
    std::cout << "The initial grid is" << std::endl;
    sml.printGrid();
    std::cout << "Start to generate ......\n"
              << "*****************" << std::endl;
    for (int i = 0; i < steps; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Current generations: " << i + 1 << std::endl;
        sml.takeStep();
        sml.printGrid();
        std::cout << "*****************" << std::endl;
    }
}

int main(int argc, char **argv)
{
    CLI::App app("Game of Life Simulation");
    // specify the version
    std::string gol_version{"0.1.0"};
    app.set_version_flag("--version", gol_version);
    // specify the way to create a Grid: use file or use random
    bool use_file = false;
    bool use_random = false;
    auto use_file_opt = app.add_flag("-f,--file", use_file, "Create Grid from a file");
    auto use_random_opt = app.add_flag("-r,--random", use_random, "Create Grid randomly");
    use_file_opt->excludes(use_random_opt);
    use_random_opt->excludes(use_file_opt);
    // find stationary patterns
    bool find_stationary = false;
    auto find_stationary_opt = app.add_flag("-s, --stationary", find_stationary, "Whether find the stationary pattern for a random Grid");
    find_stationary_opt->excludes(use_file_opt);
    find_stationary_opt->needs(use_random_opt);
    // specify the input file path
    std::string input_file;
    app.add_option("-i,--input", input_file, "Specify the input file path")->check(CLI::ExistingFile)->needs(use_file_opt)->excludes(use_random_opt);
    // specify the parameters for randomly creation
    int rows, cols, alive;
    app.add_option("--rows", rows, "Number of rows for random initial values")->check(CLI::PositiveNumber)->needs(use_random_opt)->excludes(use_file_opt);
    app.add_option("--cols", cols, "Number of columns for random initial values")->check(CLI::PositiveNumber)->needs(use_random_opt)->excludes(use_file_opt);
    app.add_option("--alive", alive, "Number of initial alive cells for random initial values")->check(CLI::NonNegativeNumber)->needs(use_random_opt)->excludes(use_file_opt);
    // specify the number of generating steps
    int steps;
    app.add_option("--steps", steps, "Number of generations to simulate")->check(CLI::NonNegativeNumber)->required(use_file || use_random);

    // examples
    // /workspaces/game-of-life-chongfengling/build/bin/golSimulator -f --input '/workspaces/game-of-life-chongfengling/test/data/glider.txt' --steps 10
    // /workspaces/game-of-life-chongfengling/build/bin/golSimulator -r --rows 10 --cols 10 --alive 10 --steps 2

    CLI11_PARSE(app, argc, argv);

    if (argc == 1) // no arguments input
    {
        std::cout << app.help() << std::endl;
        return 0;
    }

    // Implement application
    if ((use_file) && (input_file != "") && (steps > 0)) // when create Grid from a file
    {
        std::cout << "Create Grid from a file.\n"
                  << "Filepath: " << input_file << "\n"
                  << "Number of generations: " << steps << std::endl;
        gol::Grid grid_file(input_file);
        gol::Simulator sml_file(grid_file);
        generation(sml_file, steps);
    }
    else if ((use_random) && (rows > 0) && (cols > 0) && (alive >= 0) && (steps > 0)) // when create Grid randomly
    {
        if (!find_stationary) // iterate generations
        {
            std::cout << "Create Grid randomly.\n"
                      << "Rows = " << rows << ", Cols = " << cols << ", Alive = " << alive << "\n"
                      << "Number of generations: " << steps << std::endl;
            gol::Grid grid_random(rows, cols, alive);
            gol::Simulator sml_random(grid_random);
            generation(sml_random, steps);
        }
        else // find stationary patterns
        {
            gol::Grid grid_stationary(rows, cols, alive);
            gol::Simulator sml_stationary(grid_stationary);
            std::cout << "The initial grid is" << std::endl;
            sml_stationary.printGrid();
            std::cout << "Start to generate ......\n"
                      << "*****************" << std::endl;
            for (int i = 0; i < steps; ++i)
            {
                if (!(sml_stationary.get_last_grid() == sml_stationary.get_current_grid()))
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "Current generations: " << i + 1 << std::endl;
                    sml_stationary.takeStep();
                    sml_stationary.printGrid();
                }
                else
                {
                    std::cout << "No change in the last generation: " << i + 1 << std::endl;
                    break;
                }
            };
        }
        return 0;
    }
    else
    {
        std::cerr << "Error: arguments are unacceptable, please refer to the help information '-h'." << std::endl;
        return 1;
    }
}