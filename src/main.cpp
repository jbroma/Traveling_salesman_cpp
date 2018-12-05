// #include <iostream>
// #include <utility>
// #include <functional>
// #include <fstream>
// #include <memory>
// #include <boost/graph/adjacency_matrix.hpp>
// #include <boost/graph/graph_utility.hpp>
// #include "../include/graph.hpp"
// // #include "../include/file_reader.hpp"

// void test();
// void test2();

// int main() {
//     // struct A {
//     //     int a,b,c;
//     //     void func(std::ifstream&) {
//     //         a = 5;
//     //         b = 0;
//     //         c = 5;
//     //         std::cout << a << b << c << std::endl;
//     //     }
//     // };
//     // A example;
//     // auto xd = std::bind(&A::func, example, std::placeholders::_1);
//     // std::cout << fr::Load("../../../ATTENDANCE.txt", xd) << std::endl;
//     test2();
//     return 0;
// }

// void test() {
//     enum { A, B, C, D, E, F, N };
//     const char* name = "ABCDEF";

//     typedef boost::adjacency_matrix<boost::directedS> Graph;
//     Graph g(N);
//     boost::add_edge(B, C, g);
//     boost::add_edge(B, F, g);
//     boost::add_edge(C, A, g);
//     boost::add_edge(C, C, g);
//     boost::add_edge(D, E, g);
//     boost::add_edge(E, D, g);
//     boost::add_edge(F, A, g);

//     //Print test
//     std::cout << "vertex set: ";
//     boost::print_vertices(g, name);
//     std::cout << std::endl;

//     std::cout << "edge set: ";
//     boost::print

//     std::cout << "out-edges: " << std::endl;
//     boost::print_graph(g, name);
//     std::cout << std::endl;
// }

// void test2() {
//     std::unique_ptr<mg::Graph> gr;
//     try
//     {
//         gr = std::make_unique<mg::Graph>("test_data/test2.txt");
//     }
//     catch (std::runtime_error& e)
//     {
//         std::cerr << e.what() << std::endl;
//         std::exit(1);
//     }
//     //gr->gen_random_complete_graph();
//     gr->print_vertices(std::cout);
//     gr->print_edges(std::cout);
//     gr->print_out_edges(std::cout);
// }
#include "../include/program_options.hpp"

int main(int argc, char** argv)
{
    return ProgramOptions(argc, argv).run();
}