#include <person.h>

Person::Person(const std::string& first_name,
           const std::string& second_name)
           : m_first_name(first_name)
           , m_second_name(second_name)
{
}

Person::~Person()
{
}

Person& Person::operator =(const Person& rhs)
{
    Person tmp(rhs);
    swap(tmp);
    return *this;
}

Person::Person(const Person& other)
    : m_first_name(other.m_first_name)
    , m_second_name(other.m_second_name)
{
}

Person& Person::operator =(Person&& rhs)
{
    Person tmp(std::move(rhs));
    swap(tmp);
    return *this;
}

Person::Person(Person&& other)
    : m_first_name(std::move(other.m_first_name))
    , m_second_name(std::move(other.m_second_name))
{
}


void Person::swap(Person& other)
{
    m_first_name.swap(other.m_first_name);
    m_second_name.swap(other.m_second_name);    
}

const std::string& Person::get_name()
{
    return m_first_name;
}

const std::string& Person::get_family()
{
    return m_second_name;
}
