#include "../include/reduction_matrix.hpp"

namespace alg {

Reduction_Matrix::Reduction_Matrix(std::vector<std::vector<uint32_t>> matrix)
    : matrix_(matrix)
{
}

const std::vector<uint32_t>& Reduction_Matrix::operator[](uint32_t index) const
{
    return matrix_[index];
}

void Reduction_Matrix::fill_passed_nodes(uint32_t row, uint32_t column)
{
    fill_row(row);
    fill_column(column);
    matrix_[column][0] = limits::max();
}

void Reduction_Matrix::fill_row(uint32_t row)
{
    std::fill_n(matrix_[row].begin(), matrix_.size(), limits::max());
}

void Reduction_Matrix::fill_column(uint32_t column)
{
    for (auto& rows : matrix_)
        rows[column] = limits::max();
}

void Reduction_Matrix::reduce_matrix()
{
    uint32_t reduction { 0 };
    reduction += horizontal_reduction();
    reduction += vertical_reduction();
    reduction_cost_ = reduction;
}

// Reduces the matrix by the smallest factor row wise.
uint32_t Reduction_Matrix::horizontal_reduction()
{
    uint32_t reduction { 0 };
    for (auto row { matrix_.begin() }; row != matrix_.end(); ++row)
        reduction += reduce_row(row);

    return reduction;
}

uint32_t Reduction_Matrix::reduce_row(std::vector<std::vector<uint32_t>>::iterator row)
{
    uint32_t min { *(std::min_element(row->begin(), row->end())) };
    if (min != limits::max() && min != 0) {
        std::for_each(row->begin(), row->end(), [&min](uint32_t& element) {
            if (element != limits::max())
                element -= min;
        });
        return min;
    }
    return 0;
}

// Reduces the matrix by the smallest factor column wise.
uint32_t Reduction_Matrix::vertical_reduction()
{
    uint32_t min { 0 }, reduction { 0 };
    for (uint32_t i { 0 }; i < matrix_.size(); ++i) {
        min = get_column_min(i);
        if (min != limits::max() && min != 0) {
            reduction += min;
            for (auto& rows : matrix_) {
                if (rows[i] != limits::max())
                    rows[i] -= min;
            }
        }
    }
    return reduction;
}

uint32_t Reduction_Matrix::get_column_min(const uint32_t column) const
{
    uint32_t min { limits::max() };
    for (auto& rows : matrix_) {
        if (rows[column] < min)
            min = rows[column];
    }
    return min;
}

uint32_t Reduction_Matrix::get_reduction_cost() const
{
    return reduction_cost_;
}

std::vector<uint32_t> Reduction_Matrix::get_neighbours(uint32_t node) const
{
    auto neighbours { std::vector<uint32_t>() };
    for (uint32_t i { 0 }; i < matrix_[node].size(); ++i) {
        if (matrix_[node][i] != limits::max())
            neighbours.push_back(i);
    }
    return neighbours;
}

} // namespace alg