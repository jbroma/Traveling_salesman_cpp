#pragma once

#include <algorithm>
#include <vector>

#include "path.hpp"
#include "reduction_matrix.hpp"

namespace alg {

using u_lim = std::numeric_limits<uint32_t>;
using plain_matrix = std::vector<std::vector<uint32_t>>;

class City {

public:
    City() = default;
    City(const uint32_t index, std::vector<std::vector<uint32_t>>& matrix, const uint32_t travel_cost);
    City(City& city, const uint32_t index, const uint32_t travel_cost);
    City(const City& city) = default;
    City(City&& city) = default;
    City& operator=(const City& rhs) = default;
    City& operator=(City&& rhs) = default;
    ~City() = default;

    uint32_t get_bound() const;
    size_t get_path_size() const;
    uint32_t get_index() const;
    Path get_path() const;
    uint32_t get_travel_cost(uint32_t source, uint32_t dest) const;
    std::vector<uint32_t> get_neighbours() const;

    struct compare {
        bool operator()(const City& lhs, const City& rhs)
        {
            return (lhs.lower_bound_ > rhs.lower_bound_);
        }
    };

private:
    uint32_t index_;
    uint32_t lower_bound_;
    Reduction_Matrix reduction_matrix_;
    Path previous_path_;

    void fill_n_reduce();
    void add_to_path(const uint32_t index, const uint32_t travel_cost);
};

} //namespace alg