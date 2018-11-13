#pragma once
#include <fstream>
#include <string>
#include <functional>
#include <filesystem>

namespace fr
{

const std::string INVALID_PATH = "Invalid path specified.";
const std::string FS_ERROR = "Filestream error (OPEN/READ)";

namespace
{

void AllowExceptions(std::ifstream &file)
{
    std::ios_base::iostate exceptionMask = file.exceptions() | std::ios::failbit;
    file.exceptions(exceptionMask);
    return;
}

std::filesystem::path ValidatePath(std::string& path)
{
    std::filesystem::path fp{path};
    if(std::filesystem::exists(fp))
        return fp; 
    else throw std::invalid_argument(INVALID_PATH);
    return {};
}

} // unnamed namespace

template <class T>
bool Load(std::string &&path, T func)
{
    std::ifstream file;
    AllowExceptions(file);
    try
    {
        file.open(ValidatePath(path));
        func(file);
        file.close();
        return true;
    }
    catch (std::ios_base::failure &e)
    {
        std::cerr << FS_ERROR << std::endl
                  << e.what() << std::endl;
        return false;
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << INVALID_PATH << std::endl;
        return false;
    }
}

} // namespace fr