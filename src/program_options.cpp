#include "../include/program_options.hpp"

namespace po = boost::program_options;

ProgramOptions::ProgramOptions(int argc, char** argv)
    : argument_count_(argc)
    , arguments_(argv)
    , app_name_(std::filesystem::path(argv[0]).filename())
    , desc_("Options")
    , count_(1)
    , random_vertices_(0)
{
    add_positional_opt();
    add_options_desc();
}

void ProgramOptions::add_options_desc()
{
    // clang-format off
    desc_.add_options()
    ("algorithm,a", po::value<std::string>(&algorithm_name_)->required(),"REQUIRED: Select which algorithm to run.\n")
    ("input,i", po::value<std::string>(&input_file_) ,"Specify input file. Path can be either absolute or relative.")
    //("output,o", po::value<std::string>(&output_file_), "Specify path of an output file. Path can be either absolute or relative.")
    ("random,r", po::value<int>(&random_vertices_), "Generates a random complete graph with [arg] vertices. [arg] must be an unsigned integer within the range <1, 25>.")
    ("multi,m", po::value<int>(&count_)->default_value(1), "Specify how many times to run the algorithm. \n")
    ("time,t", "Specify whether to measure execution time.")
    ("graphviz,g", "Displays visual representation of a graph in the default browser")
    //("print-graph,pg", "Prints the structure of a graph")
    ("help,h", "Prints this help message");
    // clang-format on
}

void ProgramOptions::add_positional_opt()
{
    pos_desc_.add("algorithm", 1);
}

size_t ProgramOptions::run()
{
    try {
        po::store(po::command_line_parser(argument_count_, arguments_).options(desc_).positional(pos_desc_).run(),
            var_map_);

        if (var_map_.count("help")) {
            std::cout << get_help_string();
            return SUCCESS;
        }
        po::notify(var_map_);
    } catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }

    if (var_map_.count("random") && random_vertices_ < 1) {
        std::cerr << "ERROR: Parameter \"--random\" must be an unsigned integer within the range <1, 25>." << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }

    if (var_map_.count("multi") && count_ < 0) {
        std::cerr << "ERROR: Parameter \"--multi\" must be an unsigned integer." << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }

    if (conflict_check())
        return ERROR_CONFLICTING_OPTIONS;

    if (!var_map_.count("algorithm")) {
        return ERROR_IN_COMMAND_LINE;
    }

    std::function<Path(void)> algorithm;
    std::unique_ptr<mg::Graph> graph_ptr;

    try {
        // get graph
        if (var_map_.count("input")) {
            graph_ptr = std::make_unique<mg::Graph>(input_file_);
        } else if (var_map_.count("random")) {
            graph_ptr = std::make_unique<mg::Graph>(random_vertices_);
        } else {
            graph_ptr = std::make_unique<mg::Graph>(RANDOM_DEFAULT);
            random_vertices_ = RANDOM_DEFAULT;
            std::cout << "INFO: No \"--input\" or \"--random\" specified"
                      << std::endl
                      << "INFO: Defaulting to \"--random "
                      << RANDOM_DEFAULT
                      << "\"." << std::endl;
        }

        // get algorithm
        if (algorithm_name_ == "bf")
            algorithm = std::bind(&alg::BruteForce::run, alg::BruteForce(*graph_ptr));
        else if (algorithm_name_ == "hk")
            algorithm = std::bind(&alg::HeldKarp::run, alg::HeldKarp(*graph_ptr));
        else if (algorithm_name_ == "bfs")
            algorithm = std::bind(&alg::BranchAndBound::best_fs_run, alg::BranchAndBound(*graph_ptr));
        else if (algorithm_name_ == "dfs")
            algorithm = std::bind(&alg::BranchAndBound::dfs_run, alg::BranchAndBound(*graph_ptr));
        else
            throw po::validation_error(po::invalid_option_value::kind_t::invalid_option_value, "algorithm", algorithm_name_, 0);

        // main part
        auto times = std::vector<double>();
        auto timer = Timer(algorithm);
        double time = 0.0;
        for (int i = 0; i < count_; ++i) {
            graph_ptr->clear_tsp_path();
            if (random_vertices_)
                graph_ptr->gen_random_complete_graph();
            time = timer.run();
            times.push_back(time);
        }

        // output
        if (var_map_["multi"].defaulted()) {
            std::cout << timer.get_output().to_string();
        }

        if (var_map_.count("time")) {
            if (var_map_["multi"].defaulted()) {
                std::cout << "Time [ms] >> " << time << std::endl;
            } else {
                std::cout << "Mean Time [ms] >> "
                          << std::accumulate(times.begin(), times.end(), 0.0) / times.size()
                          << std::endl;
            }
        }

        if (var_map_.count("graphviz")) {
            std::ostringstream os;
            int sys_response;
#ifdef __linux__
            os << "xdg-open https://dreampuf.github.io/GraphvizOnline/#" << url_encode(graph_ptr->get_graphviz());
            sys_response = std::system(os.str().c_str());
            if (sys_response)
                std::cerr << "Failed to open browser." << std::endl;
#elif __WIN32
            os << url_encode(graph_ptr->get_graphviz());
            sys_response = ShellExecute(NULL, "open", "http://yourwebpage.com", NULL, NULL, SW_SHOWNORMAL);
            if (sys_response < 32)
                std::cerr << "Failed to open browser." << std::endl;
#endif
        }

    } catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    return SUCCESS;
}

bool ProgramOptions::conflict_check()
{
    try {
        conflicting_options("input", "random");
        // add more conflicts here
    } catch (std::logic_error& e) {
        std::cerr << "ERRROR: " << e.what() << std::endl;
        return true;
    }
    return false;
}

void ProgramOptions::conflicting_options(const std::string opt_1,
    const std::string opt_2)
{
    if (var_map_.count(opt_1) && !var_map_[opt_1].defaulted() && var_map_.count(opt_2) && !var_map_[opt_2].defaulted())
        throw std::logic_error(std::string("Conflicting options '") + opt_1 + "' and '" + opt_2 + "'.");
}

std::string ProgramOptions::get_help_string()
{
    std::stringstream ss;
    ss << "Usage: TSP ALGORITHM [OPTIONS]"
       << std::endl
       << std::endl
       << desc_
       << std::endl
       << "Implemented algorithms:"
       << std::endl
       << std::endl
       << "  [ bf ]  Bruteforce" << std::endl
       << "  [ hk ]  Held-Karp" << std::endl
       << "  [ bfs ] Best-first search Branch&Bound" << std::endl
       << "  [ dfs ] Depth-first search Branch&Bound" << std::endl;
    return ss.str();
}

std::string url_encode(const std::string& value)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(), n = value.end(); i != n;
         ++i) {
        std::string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char)c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}
