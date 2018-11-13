#pragma once
#include <fstream>
#include <string>
#include <functional>
#include <filesystem>

namespace fr 
{
const std::string INVALID_PATH  = "Invalid path specified.";
const std::string FS_ERROR      = "Filestream error (OPEN/READ)";

template<typename T, typename U>
class FileReader
{
    private:
    static void AllowExceptions(std::ifstream& file);
    static std::filesystem::path ValidatePath(std::string& path);

    public:
    FileReader() = delete;
    FileReader(const FileReader&) = delete;
    FileReader(FileReader&&) = delete;
    FileReader& operator=(const FileReader&) = delete;
    FileReader& operator=(FileReader&&) = delete;
    ~FileReader() = delete;

    static bool Load(std::string&& path, std::function<T(U)>);

};

template<typename T, typename U>
bool FileReader<T,U>::Load(std::string&& path, std::function<T(U)> func)
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
    catch (std::ios_base::failure& e)
    {
        std::cerr << FS_ERROR << std::endl << e.what() << std::endl;
        return false;
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

template<typename T, typename U>
void FileReader<T,U>::AllowExceptions(std::ifstream& file)
{
    std::ios_base::iostate exceptionMask = file.exceptions() | std::ios::failbit;
    file.exceptions(exceptionMask);
    return;
}

template<typename T, typename U>
typename std::filesystem::path FileReader<T,U>::ValidatePath(std::string& path)
{
    std::filesystem::path path_{path};
    if(std::filesystem::exists(path_))
        return path_; 
    else throw std::invalid_argument(INVALID_PATH);
    return {};
}


}