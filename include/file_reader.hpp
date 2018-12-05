#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>

namespace fr {

const std::string INVALID_PATH = "Invalid path specified.";
const std::string FS_ERROR = "Filestream error (OPEN/READ)";

namespace {

    inline void allow_exceptions(std::ifstream& file)
    {
        std::ios_base::iostate exception_mask = file.exceptions() | std::ios::failbit;
        file.exceptions(exception_mask);
        return;
    }

    inline std::filesystem::path validate_path(const std::string& path)
    {
        std::filesystem::path fp{ path };
        if (std::filesystem::exists(fp))
            return fp;
        else
            throw std::invalid_argument(INVALID_PATH);
    }

} // namespace

template <class T>
bool load(const std::string& path, T&& func)
{
    std::ifstream file;
    allow_exceptions(file);
    try {
        file.open(validate_path(path));
        func(file);
        file.close();
        return true;
    } catch (std::ios_base::failure& e) {
        std::cerr << FS_ERROR << std::endl
                  << e.what() << std::endl;
        return false;
    } catch (std::invalid_argument& e) {
        std::cerr << INVALID_PATH << std::endl;
        return false;
    }
}

} // namespace fr