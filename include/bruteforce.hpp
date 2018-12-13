#pragma once

#include <limits>
#include <memory>
#include <string>

#include "graph.hpp"
#include "path.hpp"

namespace alg {

using u_lim = std::numeric_limits<uint32_t>;

class BruteForce {
private:
    mg::Graph& graph_;

public:
    BruteForce(mg::Graph& graph);
    ~BruteForce() = default;

    Path run();
    void permutate(std::vector<uint32_t>& perms, uint32_t begin, uint32_t end, Path& p);
    void update_path(std::vector<uint32_t>& perms, Path& p);
    uint32_t get_cost(const std::vector<uint32_t>& perms);
};

} // namespace alg
