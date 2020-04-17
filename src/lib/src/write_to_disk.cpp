#include <write_to_disk.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<>
void  write_to_disk<int>(const int& value, const boost::filesystem::path & path)
{
    std::ofstream(path.string()) << value << std::endl;
}

template<>
void  write_to_disk<std::string>(const std::string& value, const boost::filesystem::path & path)
{
    std::ofstream(path.string()) << value << std::endl;
}

template<>
void  write_to_disk<bool>(const bool & value, const boost::filesystem::path & path)
{
    std::ofstream(path.string()) << value << std::endl;
}

template<>
void  write_to_disk<float>(const float & value, const boost::filesystem::path & path)
{
    std::ofstream(path.string()) << value << std::endl;
}
