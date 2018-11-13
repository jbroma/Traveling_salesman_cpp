#include "graph.hpp"

namespace mg {

void Graph::AddEdge(vd source, vd target, uint32_t weight) 
{
    boost::add_edge(source,target,weight,graph_);
}



}