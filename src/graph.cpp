#include "../include/graph.hpp"

namespace mg {

Graph::Graph(uint32_t vertices) : graph_(vertices) {}

Graph::Graph(std::string&& path) : graph_(0)
{
    if(!fr::load(path, [obj=this] (auto& file) { obj->load_graph(file);}))
        throw std::runtime_error("Failed to load the graph.");
}

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
    std::istream_iterator<int> it{file};
    graph_ = adj_matrix(*it++);
    for(uint32_t i=0; i<get_vsize(); ++i)
    {
        for(uint32_t j=0; j<get_vsize(); ++j)
        {
            if(i != j)
                add_edge(i,j,*it++);
            else if(!file.eof())
                ++it;
        }    
    }
}

void Graph::print_vertices(std::ostream& os)
{
    auto v_pair = boost::vertices(graph_);
    os << "Vertex set:" << std::endl;
    std::for_each(v_pair.first, v_pair.second, [&](auto vertex){
        os << names[vertex] << " ";
    });
    os << std::endl;
}

void Graph::print_edges(std::ostream& os)
{
    auto e_pair = boost::edges(graph_);
    os << "Edge set:" << std::endl;
    std::for_each(e_pair.first, e_pair.second, [&] (auto it) {
        os << "(" << names[boost::source(it,graph_)] << "," << names[boost::target(it,graph_)] << ") ";
    });
    os << std::endl;
}

void Graph::print_out_edges(std::ostream& os)
{
    auto v_pair = boost::vertices(graph_);
    auto weightmap = boost::get(boost::edge_weight, graph_);
    os << "Outgoing edges:" << std::endl;
    std::for_each(v_pair.first, v_pair.second, [&] (auto v_it) {
        auto e_pair = boost::out_edges(v_it, graph_);
        if(e_pair.first != e_pair.second)
        {
            os << names[v_it] << " <---> ";
            std::for_each(e_pair.first, e_pair.second, [&] (auto e_it) {
                os  << names[boost::target(e_it, graph_)] 
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
    std::uniform_int_distribution<> weight_dist{0, 1000};
    auto source_v_pair = boost::vertices(graph_);
    std::for_each(source_v_pair.first,source_v_pair.second, [&](auto source) {
        auto target_v_pair = boost::vertices(graph_);
        std::for_each(target_v_pair.first, target_v_pair.second, [&](auto target) {
            if(source != target)
                add_edge(source,target, weight_dist(gen));
        });
    });
}


} //namespace mg