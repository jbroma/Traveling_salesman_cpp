#include "../include/program_options.hpp"

int main(int argc, char** argv)
{
    return ProgramOptions(argc, argv).run();
}

// TODO Tests