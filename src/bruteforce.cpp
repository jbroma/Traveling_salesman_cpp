#include "../include/bruteforce.hpp"
#include <iterator>

namespace alg {

BruteForce::BruteForce(mg::Graph& graph)
    : graph_(graph)
{
}

Path BruteForce::run()
{
    Path p{ Path(std::vector<uint32_t>(), INT_MAX, "BF") };
    auto sequence = std::vector<uint32_t>(graph_.get_vsize() + 1, 0);
    std::iota(sequence.begin(), sequence.end() - 1, 0);
    permutate(sequence, 1, graph_.get_vsize() - 1, p);
    graph_.set_tsp_path(p);
    return p;
}

void BruteForce::permutate(std::vector<uint32_t>& sequence, uint32_t begin, uint32_t end, Path& p)
{
    if (begin == end)
        update_path(sequence, p);
    else {
        for (uint32_t i{ begin }; i <= end; ++i) {
            std::swap(sequence[begin], sequence[i]);
            permutate(sequence, begin + 1, end, p);
            std::swap(sequence[begin], sequence[i]);
        }
    }
}

void BruteForce::update_path(std::vector<uint32_t>& sequence, Path& p)
{
    uint32_t updated_cost{ get_cost(sequence) };
    if (updated_cost < p.cost_) {
        p.path_ = sequence;
        p.cost_ = updated_cost;
    }
}

uint32_t BruteForce::get_cost(const std::vector<uint32_t>& perms)
{
    auto prev = perms.begin();
    return std::accumulate(perms.begin() + 1, perms.end(), 0, [&](auto sum, auto current) -> auto {
        return sum + graph_.get_weight(*(prev++), current);
    });
}

} //namespace alg