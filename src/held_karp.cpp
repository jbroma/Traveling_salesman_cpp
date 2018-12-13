#include "../include/held_karp.hpp"

namespace alg {

HeldKarp::HeldKarp(mg::Graph& graph)
    : graph_{ graph }
    , full_mask_{ (uint32_t(1) << graph_.get_vsize()) - uint32_t(1) }
{
}

Path HeldKarp::run()
{
    operations_.resize(graph_.get_vsize(), std::vector<uint32_t>((uint32_t(1) << graph_.get_vsize()) - uint32_t(1), limits::max()));
    travel_vec_.resize(graph_.get_vsize(), std::vector<uint32_t>((uint32_t(1) << graph_.get_vsize()) - uint32_t(1), limits::max()));
    uint32_t cost{ h_k(bit_mask(1), 0) };
    auto path{ get_path(cost) };
    graph_.set_tsp_path(path);
    return path;
}

uint32_t HeldKarp::h_k(bit_mask mask, uint32_t city)
{
    if (mask == full_mask_)
        return graph_.get_weight(city, 0);

    if (operations_[city][mask.to_ulong()] != limits::max())
        return operations_[city][mask.to_ulong()];

    uint32_t current = limits::max();
    for (uint32_t i{ 0 }; i < graph_.get_vsize(); ++i) {
        bit_mask i_mask{ uint32_t(1) << i };
        if ((mask & i_mask).none()) {
            current = h_k(mask | i_mask, i) + graph_.get_weight(city, i);
            if (current < operations_[city][mask.to_ulong()]) {
                operations_[city][mask.to_ulong()] = current;
                travel_vec_[city][mask.to_ulong()] = i;
            }
        }
    }
    return operations_[city][mask.to_ulong()];
}

Path HeldKarp::get_path(uint32_t cost)
{
    std::vector<uint32_t> path = { 0 };
    bit_mask i_mask{ 1 };
    uint32_t index{ 0 };

    while (i_mask != full_mask_) {
        index = travel_vec_[index][i_mask.to_ulong()];
        path.push_back(index);
        i_mask |= bit_mask(uint32_t(1) << index);
    }
    path.push_back(0);
    return Path(path, cost, "Held-Karp");
}

} // namespace alg
