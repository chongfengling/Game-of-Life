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
    bool use_file = false;
    bool use_random = false;
    auto use_file_opt = app.add_flag("-f,--file", use_file, "Create Grid from a file");
    auto use_random_opt = app.add_flag("-r,--random", use_random, "Create Grid randomly");
    use_file_opt->excludes(use_random_opt);
    use_random_opt->excludes(use_file_opt);
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
    app.add_option("--steps", steps, "Number of generations to simulate")->check(CLI::NonNegativeNumber)->required();

    // examples
    // /workspaces/game-of-life-chongfengling/build/bin/golSimulator -f --input '/workspaces/game-of-life-chongfengling/test/data/glider.txt' --steps 10
    // /workspaces/game-of-life-chongfengling/build/bin/golSimulator -r --rows 10 --cols 10 --alive 10 --steps 2

    CLI11_PARSE(app, argc, argv);
    // Implement application
    if (use_file) // when create Grid from a file
    {
        std::cout << "Create Grid from a file.\n"
                  << "Filepath: " << input_file << "\n"
                  << "Number of generations: " << steps << std::endl;
    }
    else if (use_random) // when create Grid randomly
    {
        std::cout << "Create Grid randomly.\n"
                  << "Rows = " << rows << ", Cols = " << cols << ", Alive = " << alive <<  "\n"
                  << "Number of generations: " << steps << std::endl;
    }
    else // when unidentified argv
    {
        return 3;
    };

    return 0;
}