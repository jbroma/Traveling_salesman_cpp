#pragma once
#include <string>
#include <memory>
#include "graph.hpp"

namespace alg 
{

class BruteForce
{
    private:
    std::unique_ptr<mg::Graph>& graph_;

    public:
    BruteForce(std::unique_ptr<mg::Graph>& graph);
    ~BruteForce() = default;

    std::string GetResult() const;
    void Run();
    void Permutate(std::vector<uint32_t> &perms, uint32_t begin, uint32_t end, Path &p);
    void UpdatePath(std::vector<uint32_t> &perms, Path &p);
    uint32_t GetCost(const std::vector<uint32_t> &perms)
};


} // namespace alg

