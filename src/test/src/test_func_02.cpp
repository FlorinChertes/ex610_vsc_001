#include <test_func_02.h>
#include <clip.h>
#include <iostream>
#include <memory>


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_01()
{
	std::cout << "test_func_02_01" << std::endl;

	Contribution_typed<std::string> contribution_s;
	contribution_s.set("Adam");
	std::cout << contribution_s.get() << std::endl;


	Contribution_typed<int> contribution_i;
	contribution_i.set(43);
	std::cout << contribution_i.get() << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_02()
{
	std::cout << "test_func_02_02" << std::endl;

	std::shared_ptr<Contribution_typed<std::string>> p_s = 
		std::make_shared<Contribution_typed<std::string>>();
	p_s->set("Eva");
	std::cout << p_s->get() << std::endl;

	std::shared_ptr<Contribution_typed<int>> p_i = 
		std::make_shared<Contribution_typed<int>>();
	p_i->set(45);
	std::cout << p_i->get() << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_03()
{
	std::cout << "--- test_func_02_03 ---" << std::endl;

	std::shared_ptr<Contribution_derived> p_d = std::make_shared<Contribution_derived>();
	std::cout << "pointer on deriverd, call to: " << p_d->name() << std::endl;	

	// static_pointer_cast to go up class hierarchy
	std::shared_ptr<Contribution_basis> p_b = 
		std::static_pointer_cast<Contribution_basis>(p_d);
	std::cout << "pointer on base, call to: " << p_b->name() << std::endl;	

	// dynamic_pointer_cast to go down/across class hierarchy
    std::shared_ptr<Contribution_derived>p_d_second = 
		std::dynamic_pointer_cast<Contribution_derived>(p_b);
    if(p_d_second != nullptr) { 
		std::cout << "pointer on derived, call to: " << p_d_second->name() << std::endl;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_04()
{
	std::cout << "--- test_func_02_04 ---" << std::endl;

	auto p_s = std::make_shared<Contribution_typed<std::string>>();
	p_s->set("Eva");
	std::cout << p_s->get() << std::endl;

	// static_pointer_cast to go up class hierarchy
	std::shared_ptr<Contribution_basis> p_b = 
		std::static_pointer_cast<Contribution_basis>(p_s);
	std::cout << "pointer on base, call to: " << p_b->name() << std::endl;	

	// dynamic_pointer_cast to go down/across class hierarchy
    std::shared_ptr<Contribution_typed<std::string>>p_s_second = 
		std::dynamic_pointer_cast<Contribution_typed<std::string>>(p_b);
    if(p_s_second != nullptr) { 
		std::cout << "pointer on typed, call to: " << p_s_second->name() << std::endl;
		std::cout << "pointer on typed, call to get: " << p_s_second->get() << std::endl;		
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_05()
{
	std::cout << "--- test_func_02_05 ---" << std::endl;

	auto p_i = std::make_shared<Contribution_typed<int>>();
	p_i->set(45);
	std::cout << p_i->get() << std::endl;

	// static_pointer_cast to go up class hierarchy
	std::shared_ptr<Contribution_basis> p_b = 
		std::static_pointer_cast<Contribution_basis>(p_i);
	std::cout << "pointer on base, call to: " << p_b->name() << std::endl;	

	// dynamic_pointer_cast to go down/across class hierarchy
    std::shared_ptr<Contribution_typed<int>>p_i_second = 
		std::dynamic_pointer_cast<Contribution_typed<int>>(p_b);
    if(p_i_second != nullptr) { 
		std::cout << "pointer on typed, call to: " << p_i_second->name() << std::endl;
		std::cout << "pointer on typed, call to get: " << p_i_second->get() << std::endl;		
    }
}

