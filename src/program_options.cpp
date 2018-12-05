#include "../include/program_options.hpp"

namespace po = boost::program_options;

ProgramOptions::ProgramOptions(int argc, char** argv)
    : argument_count_(argc)
    , arguments_(argv)
    , app_name_(std::filesystem::path(argv[0]).filename())
    , desc_("Options")
{
    add_options_desc();
    add_positional_opt();
}

void ProgramOptions::add_options_desc()
{
    // clang-format off
    desc_.add_options()
    ("help,h", "Print help message")
    ("version,v", "Print program version")
    ("input,i", "Specify input file")
    ("output,o", "Specify output file")
    ("algorithm,a","Specify which algorithm to run")
    ("random,r", "Generates a random graph complete graph");
    // clang-format on
}

void ProgramOptions::add_positional_opt()
{
    // TODO
}

size_t ProgramOptions::run()
{
    try {
        po::store(po::parse_command_line(argument_count_, arguments_, desc_),
            var_map_);
    } catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }
    if (var_map_.count("input")) {
        try {
            auto gr = mg::Graph(12);
            gr.gen_random_complete_graph();
            auto bf = alg::BruteForce(gr);
            //std::cout << bf.run().to_string() << std::endl;
            auto t{ Timer<Path>(std::bind(&alg::BruteForce::run, bf)) };
            double time{ t.run() };
            std::cout << t.get_output().to_string();
            std::cout << "  Time [ms] >> " << time << std::endl;
            // gr.print_vertices(std::cout);
            // gr.print_edges(std::cout);
            // gr.print_out_edges(std::cout);
        } catch (std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return ERROR_UNHANDLED_EXCEPTION;
        }
    }

    if (var_map_.count(""))
        return SUCCESS;
    return SUCCESS;
}

void ProgramOptions::conflicting_options(const std::string opt_1,
    const std::string opt_2)
{
    if (var_map_.count(opt_1) && !var_map_[opt_1].defaulted() && var_map_.count(opt_2) && !var_map_[opt_2].defaulted())
        throw std::logic_error(std::string("Conflicting options '") + opt_1 + "' and '" + opt_2 + "'.");
}