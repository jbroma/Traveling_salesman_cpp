#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

namespace alg {

using limits = std::numeric_limits<uint32_t>;
using plain_matrix = std::vector<std::vector<uint32_t>>;

class Reduction_Matrix {

public:
    Reduction_Matrix() = default;
    Reduction_Matrix(std::vector<std::vector<uint32_t>> matrix);

    const std::vector<uint32_t>& operator[](uint32_t index) const;
    void fill_passed_nodes(uint32_t row, uint32_t column);
    void reduce_matrix();

    uint32_t get_reduction_cost() const;
    std::vector<uint32_t> get_neighbours(uint32_t node) const;

private:
    plain_matrix matrix_;
    uint32_t reduction_cost_;

    void fill_row(uint32_t row);
    void fill_column(uint32_t column);

    uint32_t reduce_row(std::vector<std::vector<uint32_t>>::iterator row);
    uint32_t horizontal_reduction();
    uint32_t vertical_reduction();

    uint32_t get_column_min(const uint32_t column) const;
};

} // namespace alg