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
    BruteForce() = delete;
    BruteForce(std::unique_ptr<mg::Graph>& graph);
    BruteForce(const BruteForce&) = delete;
    BruteForce(BruteForce&&) = delete;
    BruteForce& operator=(const BruteForce&) = delete;
    BruteForce& operator=(BruteForce&&) = delete;
    ~BruteForce() = default;


    std::string GetResult() const;
    void Run();

};


} // namespace alg

