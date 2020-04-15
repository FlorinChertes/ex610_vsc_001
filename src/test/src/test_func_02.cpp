#include <test_func_02.h>
#include <clip.h>
#include <iostream>
#include <memory>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02()
{
	std::cout << "test_func_02" << std::endl;

	Contribution contribution;
	std::cout << contribution.to_string() << std::endl;

	std::shared_ptr<Contribution> p = std::make_shared<Contribution>();
	std::cout << p->to_string() << std::endl;
}

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

	std::shared_ptr<Contribution_typed<std::string>> p_s = std::make_shared<Contribution_typed<std::string>>();
	p_s->set("Eva");
	std::cout << p_s->get() << std::endl;

	std::shared_ptr<Contribution_typed<int>> p_i = std::make_shared<Contribution_typed<int>>();
	p_i->set(45);
	std::cout << p_i->get() << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_03()
{
	std::cout << "test_func_02_03" << std::endl;

	auto p_s = std::make_shared<Contribution_typed<std::string>>();
	p_s->set("Eva");
	std::cout << p_s->get() << std::endl;

	auto p_i = std::make_shared<Contribution_typed<int>>();

	std::shared_ptr<Contribution_basis> p_bi = static_cast<Contribution_basis>(p_i);

	//p_i->set(45);
	//std::cout << p_i->get() << std::endl;
}

