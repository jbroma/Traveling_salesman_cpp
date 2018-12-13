#pragma once

#include <bitset>
#include <iostream>
#include <limits>
#include <vector>

#include "graph.hpp"
#include "path.hpp"

namespace alg {

using bit_mask = std::bitset<32>;
using limits = std::numeric_limits<uint32_t>;

class HeldKarp {

public:
    HeldKarp() = delete;
    HeldKarp(mg::Graph& graph);
    Path run();

private:
    mg::Graph& graph_;
    std::vector<std::vector<uint32_t>> operations_;
    std::vector<std::vector<uint32_t>> travel_vec_;
    bit_mask full_mask_;

    uint32_t h_k(bit_mask mask, uint32_t city);
    Path get_path(uint32_t cost);
};

} // namespace alg