#pragma once

#include <boost/filesystem.hpp>
#include <string>

void writeToDisk(const int & value, const boost::filesystem::path & path);

void writeToDisk(const std::string & value, const boost::filesystem::path & path);