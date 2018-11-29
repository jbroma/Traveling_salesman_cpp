#include "../include/bruteforce.hpp"

namespace alg
{

BruteForce::BruteForce(std::unique_ptr<mg::Graph> &graph) : graph_(graph) {}

void BruteForce::Run()
{
    Path p{ Path(std::vector<int>(), INT_MAX, "BF") };
    auto perms = std::vector<int>(graph_->get_vsize() + 1, 0);
    std::iota(perms.begin(), perms.end() - 1, 0);
    Permutate(perms, 1, graph_->get_vsize() - 1, p);
    return p;
}

void BruteForce::Permutate(std::vector<int> &perms, int begin, int end, Path &p)
{
    if (begin == end)
        UpdatePath(perms, p);
    else
    {
        for (int i{begin}; i <= end; ++i)
        {
            std::swap(perms[begin], perms[i]);
            Permutate(perms, begin + 1, end, p);
            std::swap(perms[begin], perms[i]);
        }
    }
}

void BruteForce::UpdatePath(std::vector<int> &perms, Path &p)
{
    int updated_cost{GetCost(perms)};
    if (updated_cost < p.cost_)
    {
        p.path_ = perms;
        p.cost_ = updated_cost;
    }
}

int BruteForce::GetCost(const std::vector<int> &perms)
{
    // todo
    return std::accumulate(perms.begin(), perms.end(), 0);
}

} //namespace alg