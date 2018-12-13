#include "../include/branch_and_bound.hpp"

namespace alg {

BranchAndBound::BranchAndBound(mg::Graph& graph)
    : graph_(graph)
    , best_bound_(limits::max())
{
}

plain_matrix BranchAndBound::get_plain_matrix()
{
    plain_matrix matrix;
    matrix.resize(graph_.get_vsize(), std::vector<uint32_t>(graph_.get_vsize(), limits::max()));
    auto edge_range = graph_.e_begin();
    for (auto it = edge_range.first; it != edge_range.second; ++it) {
        matrix[graph_.get_source(*it)][graph_.get_target(*it)] = graph_.get_weight(it);
    }
    return matrix;
}

Path BranchAndBound::dfs_run()
{
    matrix_ = get_plain_matrix();
    std::unique_ptr<Container> container = std::make_unique<Stack>(std::stack<City>());
    container->push(City{ 0, matrix_, 0 });
    Path best_path;
    best_path.algo_name_ = "B&B - DFS";
    return run(container, best_path);
}

Path BranchAndBound::best_fs_run()
{
    matrix_ = get_plain_matrix();
    std::unique_ptr<Container> container = std::make_unique<Priority_Queue>(city_p_queue());
    container->push(City{ 0, matrix_, 0 });
    Path best_path;
    best_path.algo_name_ = "B&B - Best-FS";
    return run(container, best_path);
}

Path BranchAndBound::run(std::unique_ptr<Container>& container, Path& best_path)
{
    City current_city;
    while (!container->empty()) {
        current_city = container->top();
        container->pop();
        handle_city(current_city, container, best_path);
    }
    finalize_path(best_path);
    graph_.set_tsp_path(best_path);
    return best_path;
}

void BranchAndBound::handle_city(City& city, std::unique_ptr<Container>& container, Path& best_path)
{
    if (city.get_path_size() == matrix_.size())
        update_best_bound(city, best_path);
    else if (city.get_bound() < best_bound_)
        push_child_cities(city, container);
}

void BranchAndBound::update_best_bound(City& city, Path& best_path)
{
    if (city.get_bound() < best_bound_) {
        std::string algo_name{ best_path.algo_name_ };
        best_bound_ = city.get_bound();
        best_path = city.get_path();
        best_path.algo_name_ = algo_name;
    }
}

void BranchAndBound::push_child_cities(City& parent_city, std::unique_ptr<Container>& container)
{
    uint32_t parent_index{ parent_city.get_index() }, travel_cost;
    std::vector<uint32_t> neighbours{ parent_city.get_neighbours() };

    for (auto& neighbour : neighbours) {
        travel_cost = parent_city.get_travel_cost(parent_index, neighbour);
        container->push(
            City(parent_city, neighbour, travel_cost));
    }
}

void BranchAndBound::finalize_path(Path& path)
{
    path.path_.push_back(0);
    calc_travel_cost(path);
}

void BranchAndBound::calc_travel_cost(Path& path)
{
    uint32_t travel_c{ 0 };
    for (size_t i{ 0 }; i < path.path_.size() - 1; ++i)
        travel_c += matrix_[path.path_[i]][path.path_[i + 1]];

    path.cost_ = travel_c;
}
} // namespace alg