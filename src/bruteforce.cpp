#include "../include/bruteforce.hpp"

namespace alg 
{

BruteForce::BruteForce(std::unique_ptr<mg::Graph>& graph) : graph_(graph) {}

void BruteForce::run()
    {
        //Path p{ Path(std::vector<int>(), INT_MAX, "BF") };
        auto perms = std::vector<int>( graph_->get_vsize() + 1, 0 );
        std::iota(perms.begin(),perms.end() - 1,0);
        permutate(perms, 1, mat_.size() - 1, p);
        return p;
    }

    void brute_force::permutate(std::vector<int>& perms, int begin, int end, Path& p)
    {
		if (begin == end)
			update_if_better(perms, p);
        else
        { 
            for (int i{ begin }; i <= end; ++i) 
            { 
                std::swap(perms[begin], perms[i]); 
                permutate(perms, begin + 1, end, p); 
                std::swap(perms[begin], perms[i]);
            } 
        }
    }

    void brute_force::update_if_better(std::vector<int>& perms, Path& p)
    {
        int updated_cost{ get_cost(perms) };
        if(updated_cost < p.cost_)
        {
            p.path_ = perms;
            p.cost_ = updated_cost;
        }
    }

    int brute_force::get_cost(const std::vector<int>& perms)
    {
        // todo
        return std::accumulate(perms.begin(),perms.end(),0);
    }

} //namespace alg