#include "../include/path.hpp"

Path::Path()
    : path_{ std::vector<uint32_t>() }
    , cost_{ 0 }
{
}

Path::Path(std::vector<uint32_t> path, const uint32_t cost, const std::string& algo_name)
    : path_{ path }
    , cost_{ cost }
    , algo_name_{ algo_name }
{
}

void Path::add_to_path(const uint32_t node, const uint32_t cost)
{
    path_.push_back(node);
    cost_ += cost;
}

uint32_t Path::get_prev_city()
{
    return path_[path_.size() - 1];
}

std::string Path::to_string()
{
    std::string path{ get_path_str() };
    std::string cost{ get_cost_str() };
    std::string output{ "| Path >> " + path + " |\n" };

    size_t line_len{ output.size() };

    output += "| Cost >> " + cost;
    pretty_string(output, line_len);
    return output;
}

std::string Path::pretty_title(const std::string& title, const unsigned line_len) const
{
    unsigned dash_count{ line_len - (unsigned)title.size() - 2 };
    auto dashes{ std::string((uint32_t)dash_count / 2, '-') };
    auto title_string{ std::string(dashes + " " + title + " " + dashes) };

    if (dash_count % 2 == 1)
        return title_string;
    else
        return title_string.substr(0, title_string.size() - 1);
}

void Path::pretty_string(std::string& path, uint32_t line_len)
{
    size_t cost_str_len{ path.size() - line_len };
    size_t spaces{ line_len - cost_str_len - 2 };
    std::string title{ pretty_title(algo_name_, line_len) };

    path.append(std::string(spaces, ' '));
    path.append("|\n");
    std::string dashes{ std::string(line_len - 1, '-') + "\n" };
    path.insert(0, title + "\n");
    path.append(dashes);
}

std::string Path::get_path_str()
{
    auto output{ std::string() };
    for (size_t i{ 0 }; i < path_.size(); ++i) {
        output += std::to_string(path_[i]);
        if (i < path_.size() - 1)
            output += "->";
    }
    return output;
}

std::string Path::get_cost_str()
{
    return std::to_string(cost_);
}