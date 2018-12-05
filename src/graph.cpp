#include "../include/graph.hpp"

namespace mg {

Graph::Graph(const uint32_t vertices)
    : graph_(std::make_unique<adj_matrix>(vertices))
    , weight_map_(boost::get(boost::edge_weight, *graph_))
{
}

Graph::Graph(const std::string&& path)
    : graph_(std::make_unique<adj_matrix>(0))
    , weight_map_(boost::get(boost::edge_weight, *graph_))
{
    if (!fr::load(path, [obj = this](auto& file) { obj->load_graph(file); }))
        throw std::runtime_error("Failed to load the graph.");
    //;
}

bool Graph::add_edge(const uint32_t source, const uint32_t target, const uint32_t weight)
{
    return boost::add_edge(source, target, weight, *graph_).second;
}

uint32_t Graph::get_vsize()
{
    return boost::num_vertices(*graph_);
}

uint32_t Graph::get_esize()
{
    return boost::num_edges(*graph_);
}

uint32_t Graph::get_weight(const uint32_t source, const uint32_t target)
{
    return boost::get(weight_map_, boost::edge(source, target, *graph_).first);
}

adj_matrix::vertex_iterator Graph::v_begin()
{
    return boost::vertices(*graph_).first;
}

adj_matrix::vertex_iterator Graph::v_end()
{
    return boost::vertices(*graph_).second;
}

adj_matrix::edge_iterator Graph::e_begin()
{
    return boost::edges(*graph_).first;
}

adj_matrix::edge_iterator Graph::e_end()
{
    return boost::edges(*graph_).second;
}

adj_matrix::out_edge_iterator Graph::edge_out_begin(adj_matrix::vertex_iterator& it)
{
    return boost::out_edges(*it, *graph_).first;
}

adj_matrix::out_edge_iterator Graph::edge_out_end(adj_matrix::vertex_iterator& it)
{
    return boost::out_edges(*it, *graph_).second;
}

void Graph::load_graph(std::ifstream& file)
{
    std::istream_iterator<int> it{ file };
    graph_ = std::make_unique<adj_matrix>(*it++);
    for (uint32_t i = 0; i < get_vsize(); ++i) {
        for (uint32_t j = 0; j < get_vsize(); ++j) {
            if (i != j)
                add_edge(i, j, *it++);
            else if (!file.eof())
                ++it;
        }
    }
}

void Graph::print_vertices(std::ostream& os)
{
    auto v_pair = boost::vertices(*graph_);
    os << "Vertex set:" << std::endl;
    std::for_each(v_pair.first, v_pair.second, [&](auto vertex) {
        os << names[vertex] << " ";
    });
    os << std::endl;
}

void Graph::print_edges(std::ostream& os)
{
    auto e_pair = boost::edges(*graph_);
    os << "Edge set:" << std::endl;
    std::for_each(e_pair.first, e_pair.second, [&](auto it) {
        os << "(" << names[boost::source(it, *graph_)] << "," << names[boost::target(it, *graph_)] << ") ";
    });
    os << std::endl;
}

void Graph::print_out_edges(std::ostream& os)
{
    auto v_pair = boost::vertices(*graph_);
    auto weightmap = boost::get(boost::edge_weight, *graph_);
    os << "Outgoing edges:" << std::endl;
    std::for_each(v_pair.first, v_pair.second, [&](auto v_it) {
        auto e_pair = boost::out_edges(v_it, *graph_);
        if (e_pair.first != e_pair.second) {
            os << names[v_it] << " <---> ";
            std::for_each(e_pair.first, e_pair.second, [&](auto e_it) {
                os << names[boost::target(e_it, *graph_)]
                   << "("
                   << weightmap[e_it]
                   << ")\t";
            });
            os << std::endl;
        }
    });
}

void Graph::gen_random_complete_graph()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weight_dist{ 0, 1000 };
    auto source_v_pair = boost::vertices(*graph_);
    std::for_each(source_v_pair.first, source_v_pair.second, [&](auto source) {
        auto target_v_pair = boost::vertices(*graph_);
        std::for_each(target_v_pair.first, target_v_pair.second, [&](auto target) {
            if (source != target)
                add_edge(source, target, weight_dist(gen));
        });
    });
}

} //namespace mg