
#include <unordered_map>
#include <string>
#include <mutex>
#include <memory>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class Contribution_basis
{
public:

	using Ptr = std::shared_ptr<Contribution_basis>;

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


class Contribution_map
{
public:
    static constexpr char defaultStorageName[] = "default";

	using Storage = std::unordered_map<std::string, Contribution_basis::Ptr>;

private:

	void setContributionPtr(const std::string &key, 
							const Contribution_basis::Ptr value, 
							const std::string & storageName = defaultStorageName);
							
    Contribution_basis::Ptr getContributionPtr(const std::string &storageName, 
											   const std::string & key) const;


	std::unordered_map<std::string, Storage>	_contributions;
    mutable std::mutex							_mutex;

};