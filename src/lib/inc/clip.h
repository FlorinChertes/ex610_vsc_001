#include <string>


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class Contribution_basis
{
public:
	virtual std::string to_string() const = 0;

	virtual std::string name() const { 
		return "name: Contribution_basis"; 
	}
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class Contribution_derived : public Contribution_basis
{
public:
	std::string to_string() const {
		return "Contribution_derived::to_string";
	}

	std::string name() const override;

};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T>
class Contribution_typed : public Contribution_basis
{
public:
	std::string to_string() const 	{
		const std::string s("Contribution_typed::to_string");
		return s;
	}

	std::string name() const override { 
		return "name: Contribution_typed"; 
	} 

	void set(const T& c) {
		content = c;
	}

	const T& get() {
		return content;
	}

	T content; 
};

