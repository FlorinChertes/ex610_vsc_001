#include <string>

class Person
{
public:
    Person() = default;

    Person(const std::string& m_first_name,
           const std::string& m_second_name);

    ~Person();

    Person& operator =(const Person& rhs);

    void swap(Person& other);      
    const std::string& get_name();
    const std::string& get_family();    

private:
    std::string m_first_name;
    std::string m_second_name;
};