#pragma once

#include <component.h>

#include <boost/filesystem.hpp>

#include <unordered_map>
#include <string>

#include <iostream>
#include <mutex>
#include <exception>
#include <memory>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class Contribution_basis
{
public:

	using Ptr = std::shared_ptr<Contribution_basis>;
	using FactoryType = GenericFactory<Contribution_basis, std::string ,Ptr>;	

	/// Get instance from factory and delegate to _readFrom
    static Ptr readFrom(const boost::filesystem::path &);

	virtual std::string to_string() const = 0;

	virtual std::string name() const { 
		return "name: Contribution_basis"; 
	}

	virtual void writeTo(const boost::filesystem::path & path) = 0;

	virtual ~Contribution_basis() {
	}

protected:

    /// Fill this sequence contribution with directory contents
    virtual void _readFrom(const boost::filesystem::path & path) = 0;
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

	void writeTo(const boost::filesystem::path & path);

protected:
    void _readFrom(const boost::filesystem::path &path) override {
	}
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T>
class Contribution_typed : public Contribution_basis
{
public:

	explicit Contribution_typed() {}	// needed for factory
	explicit Contribution_typed(const T & c): _content(c) {}

	std::string to_string() const {
		const std::string s("Contribution_typed::to_string");
		return s;
	}
	std::string name() const override { 
		return "name: Contribution_typed"; 
	} 

	void writeTo(const boost::filesystem::path & path);

	T _content; 

protected:
    void _readFrom(const boost::filesystem::path &path) override;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class Contribution_map
{
public:
    static constexpr char defaultStorageName[] = "default";

	using Storage = std::unordered_map<std::string, Contribution_basis::Ptr>;

	const Contribution_map::Storage & 
		getContributions(const std::string & storageName) const;

	template<typename T>
    void setContribution(const std::string & key, 
						 const T & value,
						 const std::string & storageName = defaultStorageName)
    {
        auto valuePtr = std::make_shared<Contribution_typed<T>>(value);
        setContributionPtr(key, valuePtr, storageName);
    }

    template<typename T>
    const T & getContribution(const std::string & key, 
							  const std::string & storageName = defaultStorageName) const
    {
        auto contributionPtr = getContributionPtr(storageName, key);
        auto typedContribution = std::dynamic_pointer_cast<Contribution_typed<T>>(contributionPtr);

        if (!typedContribution) {
            throw std::runtime_error("Type mismatch for contribution: " + key + " in storage: " + storageName);
        }

        return typedContribution->_content;
    }

	void setContributionPtr(const std::string &key, 
							const Contribution_basis::Ptr value, 
							const std::string & storageName = defaultStorageName);

private:

    Contribution_basis::Ptr getContributionPtr(const std::string &storageName, 
											   const std::string & key) const;


	std::unordered_map<std::string, Storage>	_contributions;
    mutable std::mutex							_mutex;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void readContributions(Contribution_map &,
					   const std::string & storage_name,
					   const boost::filesystem::path &);
void writeContributions(const Contribution_map &,
						const std::string & storage_name,
                        const boost::filesystem::path &);
