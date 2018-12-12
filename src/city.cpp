#include "../include/city.hpp"

namespace alg {

City::City(const uint32_t index, const std::vector<std::vector<uint32_t>>& matrix, const uint32_t travel_cost = 0)
    : index_ { index }
    , lower_bound_ { travel_cost }
    , reduction_matrix_ { matrix }
    , previous_path_ { Path() }
{
    reduction_matrix_.reduce_matrix();
    lower_bound_ = reduction_matrix_.get_reduction_cost();
    add_to_path(index, 0);
}

City::City(const City& city, const uint32_t index, const uint32_t travel_cost)
    : index_ { index }
    , lower_bound_ { city.lower_bound_ + travel_cost }
    , reduction_matrix_ { city.reduction_matrix_ }
    , previous_path_ { city.previous_path_ }
{
    fill_n_reduce();
    add_to_path(index, travel_cost);
}

uint32_t City::get_bound() const
{
    return lower_bound_;
}

size_t City::get_path_size() const
{
    return previous_path_.path_.size();
}

uint32_t City::get_index() const
{
    return index_;
}

Path City::get_path() const
{
    return previous_path_;
}

uint32_t City::get_travel_cost(uint32_t source, uint32_t dest) const
{
    return reduction_matrix_[source][dest];
}

std::vector<uint32_t> City::get_neighbours() const
{
    return reduction_matrix_.get_neighbours(index_);
}

// Funkcja ograniczajaca.
// Wypelnia wiersz z indeksem poprzednika
// i kolumne z aktualnym indeksem wartoscia uint32_t_MAX.
// Nastepnie uruchamia redukcje macierzy.
void City::fill_n_reduce()
{
    reduction_matrix_.fill_passed_nodes(
        previous_path_.get_prev_city(), index_);

    reduction_matrix_.reduce_matrix();
    lower_bound_ += reduction_matrix_.get_reduction_cost();
}

void City::add_to_path(const uint32_t index, const uint32_t cost)
{
    previous_path_.add_to_path(index, cost);
}

} // namespace alg