#pragma once

#include <functional>
#include <limits>
#include <memory>
#include <queue>
#include <stack>
#include <utility>

#include "bnb_containers.hpp"
#include "city.hpp"
#include "graph.hpp"
#include "path.hpp"

namespace alg {

using u_lim = std::numeric_limits<uint32_t>;
using plain_matrix = std::vector<std::vector<uint32_t>>;
using city_pq = std::priority_queue<City, std::vector<City>, City::compare>;

class BranchAndBound {

public:
    BranchAndBound() = delete;
    BranchAndBound(mg::Graph& graph);

    Path dfs_run();
    Path best_fs_run();

private:
    mg::Graph& graph_;
    plain_matrix matrix_;
    uint32_t best_bound_;

    plain_matrix get_plain_matrix();
    Path run(std::unique_ptr<Container>& container, Path& best_path);
    void handle_city(City& city, std::unique_ptr<Container>& container, Path& best_path);
    void push_child_cities(City& parent_city, std::unique_ptr<Container>& container);
    void update_best_bound(City& city, Path& best_path);
    void finalize_path(Path& best_path);
    void calc_travel_cost(Path& path);
};

} // namespace alg
