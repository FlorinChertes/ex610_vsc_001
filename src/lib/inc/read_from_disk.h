#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <exception>

/// Generic read from disk
template<typename T>
T readFromDisk(const boost::filesystem::path & path)
{
    throw std::runtime_error("No implementation for readFromDisk("+path.string()+")");
}

template<>
bool readFromDisk(const boost::filesystem::path & path);

template<>
int readFromDisk(const boost::filesystem::path & path);

template<>
float readFromDisk(const boost::filesystem::path & path);

template<>
std::string readFromDisk(const boost::filesystem::path & path);

