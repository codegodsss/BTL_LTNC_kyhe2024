#include "Os.hpp"
#include <cstdlib>

#if defined(_WIN32) || defined(__WIN32__) // Windows
#define SYS_WINDOWS


namespace os
{

std::filesystem::path config_path(const std::string& appname)
{
#ifdef SYS_WINDOWS
    return std::string(std::getenv("APPDATA")) + "\\" + appname;

}

}
