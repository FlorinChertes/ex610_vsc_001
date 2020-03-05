#include <test_func_01.h>
#include <person.h>

#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_person_ctor()
{
	Person p("Robert", "Plant");
	std::cout << "name: " << p.get_name() <<
				" family: " << p.get_family() << 
				std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_person_default_ctor()
{
	Person p;
	std::cout << "name: " << p.get_name() <<
				" family: " << p.get_family() << 
				std::endl;	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_person_copy_ctor()
{
	Person p("Robert", "Plant");
	std::cout << "name: " << p.get_name() <<
				" family: " << p.get_family() << 
				std::endl;

	Person p_1(p);
	std::cout << "name: " << p_1.get_name() <<
				" family: " << p_1.get_family() << 
				std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_person_assign_copy()
{
	Person p("Robert", "Plant");
	std::cout << "name: " << p.get_name() <<
				" family: " << p.get_family() << 
				std::endl;


	Person p_1;
	p_1 = p;
	std::cout << "name: " << p_1.get_name() <<
			 " family: " << p_1.get_family() << 
				std::endl;	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_person_elision_copy()
{

	Person p = (Person("John","Lord"));
	std::cout << "name: " << p.get_name() <<
			 " family: " << p.get_family() << 
				std::endl;	
}

//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Person create_person()
{
	return Person("Ritchie", "Blacklmore");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_person_lvalue()
{
	Person p_5;
	p_5 = create_person();
	std::cout << "name: " << p_5.get_name() <<
			 " family: " << p_5.get_family() << 
				std::endl;	
}

