#pragma once
#include <boost/graph/adjacency_matrix.hpp>
#include <filesystem>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>

#include "file_reader.hpp"

namespace boost {
  enum edge_tsp_path_t { edge_tspPath };
  BOOST_INSTALL_PROPERTY(edge, tsp_path);
} // namespace boost

namespace mg {

using tsp_path = boost::property<boost::edge_tsp_path_t, bool>;
using edge_properties = boost::property<boost::edge_weight_t, uint32_t, tsp_path>;
using adj_matrix = boost::adjacency_matrix<boost::directedS, boost::no_property, edge_properties>;

class Graph
{
    
    const std::string names{"ABCDEFGHIJKLMNOPQRSTUWXYZ"};
    std::unique_ptr<adj_matrix> graph_;

  public:
    Graph(uint32_t vertices);
    Graph(std::string&& path);
    ~Graph() = default;

    bool add_edge(uint32_t source, uint32_t target, uint32_t weight);
    uint32_t get_vsize();
    uint32_t get_esize();
    void load_graph(std::ifstream& file);
    void print_vertices(std::ostream& os);
    void print_edges(std::ostream& os);
    void print_out_edges(std::ostream& os);
    void gen_random_complete_graph();
};



} //namespace mg
