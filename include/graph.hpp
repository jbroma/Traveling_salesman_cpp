#pragma once
#include <boost/graph/adjacency_matrix.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>

#include "file_reader.hpp"

namespace boost {
enum edge_tsp_path_t { edge_tspPath };
BOOST_INSTALL_PROPERTY(edge, tsp_path);
} // namespace boost

namespace mg {

using tsp_path = boost::property<boost::edge_tsp_path_t, bool>;
using edge_properties = boost::property<boost::edge_weight_t, uint32_t, tsp_path>;
using adj_matrix = boost::adjacency_matrix<boost::directedS, boost::no_property,
    edge_properties>;
using weight_map_t = boost::property_map<adj_matrix, boost::edge_weight_t>::type;

class Graph {

    const std::string names{ "ABCDEFGHIJKLMNOPQRSTUWXYZ" };

    std::unique_ptr<adj_matrix> graph_;
    weight_map_t weight_map_;

public:
    Graph(const uint32_t vertices);
    Graph(const std::string& path);
    ~Graph() = default;

    bool add_edge(const uint32_t source, const uint32_t target, const uint32_t weight);
    uint32_t get_vsize();
    uint32_t get_esize();

    uint32_t get_weight(const uint32_t source, const uint32_t target);

    adj_matrix::vertex_iterator v_begin();
    adj_matrix::vertex_iterator v_end();
    adj_matrix::edge_iterator e_begin();
    adj_matrix::edge_iterator e_end();
    adj_matrix::out_edge_iterator edge_out_begin(adj_matrix::vertex_iterator& it);
    adj_matrix::out_edge_iterator edge_out_end(adj_matrix::vertex_iterator& it);

    void load_graph(std::ifstream& file);
    void print_vertices(std::ostream& os);
    void print_edges(std::ostream& os);
    void print_out_edges(std::ostream& os);
    void gen_random_complete_graph();
};

} // namespace mg
