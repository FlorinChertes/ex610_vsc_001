#include <string>

class Contribution
{
public:
	std::string to_string() const;
};


class Contribution_basis
{
public:
	virtual std::string to_string() const = 0;
};

template <typename T>
class Contribution_typed : Contribution_basis
{
public:
	std::string to_string() const 	{
		const std::string s("Contribution_typed::to_string");
		return s;
	}

	void set(const T& c) {
		content = c;
	}

	const T& get() {
		return content;
	}

	T content; 
};

