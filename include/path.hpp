#pragma once

#include <iostream>
#include <string>
#include <vector>

class Path {

    void pretty_string(std::string& path, uint32_t line_len);
    std::string pretty_title(const std::string& title, const uint32_t line_len) const;
    std::string get_path_str();
    std::string get_cost_str();

public:
    std::vector<uint32_t> path_;
    uint32_t cost_;
    std::string algo_name_;

    Path();
    Path(std::vector<uint32_t> path, const uint32_t cost, const std::string& algo_name);
    ~Path() = default;

    void add_to_path(const uint32_t node, const uint32_t cost);
    uint32_t get_prev_city();
    std::string to_string();
};