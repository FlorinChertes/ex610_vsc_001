#pragma once

#include <memory>
#include <sstream>
#include <unordered_map>


template<typename Base, 
	typename KeyType, 
	typename PointerType, 
	typename ... ConstructorArgs>
class GenericFactory
{

public:

    typedef Base* (*CreatorFn)(ConstructorArgs ...);

    template<typename Derived>
    static Base * construct(ConstructorArgs ... args)
    {
        return new Derived(args...);
    }

    using Map = std::unordered_map<KeyType, CreatorFn>;

    GenericFactory() { init(); }

    template<typename Derived>
    void add(const KeyType & key)
    {
        auto inserted = _creators.emplace(key, &construct<Derived>);
        if( ! inserted.second ) {
            throw std::logic_error(key + " already used in factory");
        }
    }


    PointerType create(const KeyType & key, ConstructorArgs ... args)
    {
        auto it = _creators.find(key);
        if(it == _creators.end())
            throw std::out_of_range("No factory function found for key "+key);

        auto creator = *it->second;
        return PointerType (creator(args...));
    }


private:

    /// Init function must be specialized
    void init();

    std::string _basename;
    Map _creators;


};

