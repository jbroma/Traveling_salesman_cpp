#pragma once
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <memory>
#include <string>
#include <fstream>

namespace mg
{

using edge_weight = boost::property<boost::edge_weight_t, uint32_t>;
using adj_matrix = boost::adjacency_matrix<boost::directedS, boost::no_property, edge_weight>;
using vd = adj_matrix::vertex_descriptor;

class Graph
{
  private:
    std::unique_ptr<adj_matrix> graph_;

  public:
    Graph() = delete;
    Graph(uint32_t vertices);
    void AddEdge(vd source, vd target, uint32_t weight);
    void LoadFromFile(std::string path);
};

} // namespace mg