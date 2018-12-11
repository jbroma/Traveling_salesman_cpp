#pragma once
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graphviz.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>

#include "file_reader.hpp"
#include "path.hpp"

namespace boost {
enum edge_tsp_path_t { edge_tspPath };
BOOST_INSTALL_PROPERTY(edge, tsp_path);
} // namespace boost

namespace mg {

const std::string NAMES { "ABCDEFGHIJKLMNOPQRSTUWXYZ" };
const uint32_t START_VERTEX { 0 };

using tsp_path = boost::property<boost::edge_tsp_path_t, bool>;
using edge_properties = boost::property<boost::edge_weight_t, uint32_t, tsp_path>;
using adj_matrix = boost::adjacency_matrix<boost::directedS, boost::no_property,
    edge_properties>;
using weight_map_t = boost::property_map<adj_matrix, boost::edge_weight_t>::type;
using tsp_path_map_t = boost::property_map<adj_matrix, boost::edge_tsp_path_t>::type;

class Graph {

    std::unique_ptr<adj_matrix> graph_;
    weight_map_t weight_map_;
    tsp_path_map_t tsp_path_map_;

public:
    Graph(const uint32_t vertices);
    Graph(const std::string& path);
    ~Graph() = default;

    bool add_edge(const uint32_t source, const uint32_t target,
        const uint32_t weight);
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
    void set_tsp_path(Path& path);
    std::string get_graphviz();
};

// Helper classes for graphviz
class VertexPropertyWriter {

public:
    void operator()(std::ostream& out, const adj_matrix::vertex_descriptor& v) const;
};

class EdgePropertyWriter {

    weight_map_t& wm_;
    tsp_path_map_t& tp_;

public:
    EdgePropertyWriter(weight_map_t wm, tsp_path_map_t tp);
    void operator()(std::ostream& out, const adj_matrix::edge_descriptor& e) const;
};

class GraphPropertyWriter {

public:
    void operator()(std::ostream& out) const;
};

} // namespace mg