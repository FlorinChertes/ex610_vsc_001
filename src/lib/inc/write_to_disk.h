#pragma once

#include <boost/filesystem.hpp>
#include <string>

/// Generic write to disk
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
void write_to_disk(const T&, const boost::filesystem::path & path)
{
    throw std::runtime_error("No implementation for write_to_disk("+path.string()+")");
}

template<>
void write_to_disk<bool>(const bool & vale,const boost::filesystem::path & path);

template<>
void write_to_disk<float>(const float & value, const boost::filesystem::path & path);

template<>
void write_to_disk<int>(const int & value, const boost::filesystem::path & path);

template<>
void  write_to_disk<std::string>(const std::string & value, const boost::filesystem::path & path);
