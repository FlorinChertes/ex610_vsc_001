#include "read_from_disk.h"

#include <boost/lexical_cast.hpp>

namespace fs = boost::filesystem;


template<>
bool readFromDisk(const boost::filesystem::path & path)
{
    bool value;
    std::ifstream ifs(path.string());
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    ifs >> value;
    return value;
}

template<>
int readFromDisk(const boost::filesystem::path & path)
{
    int value;
    std::ifstream ifs(path.string());
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    ifs >> value;
    return value;
}

template<>
float readFromDisk(const boost::filesystem::path & path)
{
    float value;
    std::ifstream ifs(path.string());
    ifs.precision( std::numeric_limits<float>::digits10 + 1);
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    ifs >> value;
    return value;
}

template<>
std::string readFromDisk(const boost::filesystem::path & path)
{
    std::string value;
    std::ifstream in(path.c_str());
    std::getline(in, value);
    return value;
}

