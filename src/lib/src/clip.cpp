#include <clip.h>

#include <iostream>
#include <exception>

using WriteLock = std::lock_guard<std::mutex>;
using ReadLock = WriteLock; // Replace by shared_lock in c++17

std::string Contribution_basis::to_string() const
{
	const std::string s("Contribution::to_string");
	return s;
}

std::string Contribution_derived::name() const
{ 
	return "name: Contribution_derived"; 
}

void Contribution_map::setContributionPtr(const std::string &key, 
										  const Contribution_basis::Ptr value, 
										  const std::string &storageName)
{
    WriteLock lock(_mutex);
    std::cout << storageName << " " << key;
    _contributions[storageName][key] = value;
}

Contribution_basis::Ptr Contribution_map::getContributionPtr(const std::string &storageName, 
														   const std::string &key) const
{
    try {
        ReadLock lock(_mutex);
        return  _contributions.at(storageName).at(key);

    } catch(const std::out_of_range &) {
		std::string msg = std::string("Missing contribution: ") + key + std::string(" in storage: ") + storageName;
        throw std::range_error(std::string("Missing contribution: ") + key + std::string(" in storage: ") + storageName);

    }
}