#include <iostream>
#include <utility>
#include <functional>
#include <fstream>
// #include <boost/graph/adjacency_matrix.hpp>
// #include <boost/graph/graph_utility.hpp>
#include "../include/file_reader.hpp"

int main() {
    struct A {
        int a,b,c;
        void func(std::ifstream&) {
            a = 5;
            b = 0;
            c = 5;
            std::cout << a << b << c << std::endl;
        }
    };
    A example;
    std::function<void(std::ifstream&)> xd = std::bind(&A::func, example, std::placeholders::_1);
    std::cout << fr::Load("/home/jroma/ATTENDANCE.txt", xd) << std::endl;
    return 0;
}

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
//     boost::print_edges(g, name);
//     std::cout << std::endl;

//     std::cout << "out-edges: " << std::endl;
//     boost::print_graph(g, name);
//     std::cout << std::endl;
// }