#include <filesystem>
#include <string>
#include <regex>

std::string getRoot()
{
    std::string execPath = std::filesystem::current_path();
    execPath = std::regex_replace(execPath, std::regex("/build"), "");
    return execPath;
}