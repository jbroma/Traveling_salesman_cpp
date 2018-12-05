#pragma once

#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
#include <string>

#include "bruteforce.hpp"
#include "graph.hpp"
#include "timer.hpp"

class ProgramOptions {
    const size_t SUCCESS = 0;
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

    int argument_count_;
    char** arguments_;

    std::string app_name_;
    boost::program_options::options_description desc_;
    boost::program_options::positional_options_description pos_desc_;
    boost::program_options::variables_map var_map_;

    void add_options_desc();
    void add_positional_opt();
    void conflicting_options(const std::string opt_1, const std::string opt_2);

public:
    ProgramOptions(int argc, char** argv);
    size_t run();
};