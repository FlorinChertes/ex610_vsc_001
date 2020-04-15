#include <clip.h>

std::string Contribution_basis::to_string() const
{
	const std::string s("Contribution::to_string");
	return s;
}

std::string Contribution_derived::name() const
{ 
	return "name: Contribution_derived"; 
}

