#include "../include/graph.hpp"

namespace mg {

Graph::Graph() : graph_(0) {}

Graph::Graph(uint32_t vertices) : graph_(vertices) {}

bool Graph::add_edge(uint32_t source, uint32_t target, uint32_t weight) 
{
    return boost::add_edge(source,target,weight,graph_).second;
}

uint32_t Graph::get_vsize()
{
    return boost::num_vertices(graph_);
}

uint32_t Graph::get_esize()
{
    return boost::num_edges(graph_);
}

void Graph::load_graph(std::ifstream& file)
{
    uint32_t vertices;
    file >> vertices;
    for(uint32_t i=0; i<vertices; ++i)
    {
        for(uint32_t j=0; j<vertices; ++j)
        {
            if(i != j)
                add_edge(i,j,file.get()); 
        }    
    }
}

void Graph::print_vertices(std::ostream& os)
{
    auto v_pair = boost::vertices(graph_);
    os << "Vertex set:" << std::endl;
    std::copy(v_pair.first, v_pair.second, std::ostream_iterator<uint32_t>(os, " "));
    os << std::endl;
}

void Graph::print_edges(std::ostream& os)
{
    auto e_pair = boost::edges(graph_);
    os << "Edge set:" << std::endl;
    std::for_each(e_pair.first, e_pair.second, [&] (auto it) {
        os << "(" << boost::source(it,graph_) << "," << boost::target(it,graph_) << ") ";
    });
    os << std::endl;
}

void Graph::print_out_edges(std::ostream& os)
{
    auto v_pair = boost::vertices(graph_);
    os << "Outgoing edges:" << std::endl;
    std::for_each(v_pair.first, v_pair.second, [&] (auto v_it) {
        auto e_pair = boost::out_edges(v_it, graph_);
        if(e_pair.first != e_pair.second)
        {
            os << v_it << " <---> ";
            std::for_each(e_pair.first, e_pair.second, [&] (auto e_it) {
                os << boost::target(e_it, graph_) << " | ";
            });
            os << std::endl;
        }   
    });
}

void Graph::gen_random_complete_graph(uint32_t vertices, boost::minstd_rand& gen)
{
    graph_ = adj_matrix(vertices);
    boost::generate_random_graph(graph_,0,vertices*vertices,gen,true,false);
}


} //namespace mg