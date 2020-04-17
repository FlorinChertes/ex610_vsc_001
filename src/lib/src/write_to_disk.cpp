#include <write_to_disk.h>

void writeToDisk(const int &value, const boost::filesystem::path & path)
{
    std::ofstream(path.string()) << value << std::endl;
}

void writeToDisk(const std::string &value, const boost::filesystem::path & path)
{
    std::ofstream(path.string()) << value << std::endl;
}

