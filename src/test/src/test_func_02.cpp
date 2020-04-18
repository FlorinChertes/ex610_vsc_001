#include <test_func_02.h>
#include <clip.h>
#include <iostream>
#include <memory>


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_01()
{
	std::cout << "test_func_02_01" << std::endl;

	Contribution_typed<std::string> contribution_s("Adam");
	std::cout << contribution_s._content << std::endl;

	Contribution_typed<int> contribution_i(43);
	std::cout << contribution_i._content << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_02()
{
	std::cout << "test_func_02_02" << std::endl;

	std::shared_ptr<Contribution_typed<std::string>> p_s = 
		std::make_shared<Contribution_typed<std::string>>("Eva");
	std::cout << p_s->_content << std::endl;

	std::shared_ptr<Contribution_typed<int>> p_i = 
		std::make_shared<Contribution_typed<int>>(45);
	std::cout << p_i->_content << std::endl;
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

	auto p_s = std::make_shared<Contribution_typed<std::string>>("Eva");
	std::cout << p_s->_content << std::endl;

	// static_pointer_cast to go up class hierarchy
	std::shared_ptr<Contribution_basis> p_b = 
		std::static_pointer_cast<Contribution_basis>(p_s);
	std::cout << "pointer on base, call to: " << p_b->name() << std::endl;	

	// dynamic_pointer_cast to go down/across class hierarchy
    std::shared_ptr<Contribution_typed<std::string>>p_s_second = 
		std::dynamic_pointer_cast<Contribution_typed<std::string>>(p_b);
    if(p_s_second != nullptr) { 
		std::cout << "pointer on typed, call to: " << p_s_second->name() << std::endl;
		std::cout << "pointer on typed, call to get: " << p_s_second->_content << std::endl;		
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_05()
{
	std::cout << "--- test_func_02_05 ---" << std::endl;

	auto p_i = std::make_shared<Contribution_typed<int>>(54);
	std::cout << p_i->_content << std::endl;

	// static_pointer_cast to go up class hierarchy
	std::shared_ptr<Contribution_basis> p_b = 
		std::static_pointer_cast<Contribution_basis>(p_i);
	std::cout << "pointer on base, call to: " << p_b->name() << std::endl;	

	// dynamic_pointer_cast to go down/across class hierarchy
    std::shared_ptr<Contribution_typed<int>>p_i_second = 
		std::dynamic_pointer_cast<Contribution_typed<int>>(p_b);
    if(p_i_second != nullptr) { 
		std::cout << "pointer on typed, call to: " << p_i_second->name() << std::endl;
		std::cout << "pointer on typed, call to get: " << p_i_second->_content << std::endl;		
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_06()
{
	std::cout << "--- test_func_02_06 contribution map ---" << std::endl;

	try	{

		Contribution_map contribution_map;
		contribution_map.setContribution("a_1", 42, "A_1");
		
		int value = contribution_map.getContribution<int>("a_1", "A_1");
		std::cout << "value from container: " << value << std::endl;

    } 
	catch(const std::exception& e) {
        std::cout << "Caught error meaning: " << e.what() << '\n';
    }	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_07()
{
	std::cout << "--- test_func_02_07 contribution map ---" << std::endl;

	try	{

		Contribution_map contribution_map;
		contribution_map.setContribution("a_1", 42, "A_1");
		contribution_map.setContribution("a_2", std::string("Eva"), "A_1");

		int value_i = contribution_map.getContribution<int>("a_1", "A_1");
		std::cout << "value int from container: " << value_i << std::endl;

		std::string value_s = contribution_map.getContribution<std::string>("a_2", "A_1");
		std::cout << "value string from container: " << value_s << std::endl;

    } 
	catch(const std::exception& e) {
        std::cout << "Caught error meaning: " << e.what() << '\n';
    }	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_09()
{
	std::cout << "--- test_func_02_09 write to disk contribution map ---" << std::endl;

	try	{

		Contribution_map contribution_map;
		contribution_map.setContribution("a_1", 42, "A_1");
		contribution_map.setContribution("a_2", std::string("Eva"), "A_1");

		int value_i = contribution_map.getContribution<int>("a_1", "A_1");
		std::cout << "value int from container: " << value_i << std::endl;
		std::string value_s = contribution_map.getContribution<std::string>("a_2", "A_1");
		std::cout << "value string from container: " << value_s << std::endl;

		const boost::filesystem::path	storage_path("/home/florin/tmp/storage_dir");
		const std::string				storage_name("A_1");

		for (const auto & elem : contribution_map.getContributions(storage_name)) {
			const auto & key = elem.first;
			elem.second->writeTo(storage_path / key);
		}
    } 
	catch(const std::exception& e) {
        std::cout << "Caught error meaning: " << e.what() << '\n';
    }	
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_10()
{
	std::cout << "--- test_func_02_10 write to disk contribution map ---" << std::endl;

	try	{
		Contribution_map contribution_map;
		contribution_map.setContribution("a_1", 41, "A_1");
		contribution_map.setContribution("a_2", std::string("Adam"), "A_1");

		int value_i = contribution_map.getContribution<int>("a_1", "A_1");
		std::cout << "value int from container: " << value_i << std::endl;
		std::string value_s = contribution_map.getContribution<std::string>("a_2", "A_1");
		std::cout << "value string from container: " << value_s << std::endl;

#if defined (_MSC_VER)
		const boost::filesystem::path	storage_path("E:/users/temp/tmp/storage_dir");
#else
		const boost::filesystem::path	storage_path("/home/florin/tmp/storage_dir");
#endif
		const std::string				storage_name("A_1");
		writeContributions(contribution_map, storage_name, storage_path);
    }
	catch(const std::exception& e) {
        std::cout << "Caught error meaning: " << e.what() << '\n';
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_func_02_11()
{
	std::cout << "--- test_func_02_11 read from disk into contribution map ---" << std::endl;

	try	{
		Contribution_map contribution_map;

#if defined (_MSC_VER)
		const boost::filesystem::path	storage_path("E:/users/temp/tmp/storage_dir");
#else
		const boost::filesystem::path	storage_path("/home/florin/tmp/storage_dir");
#endif
		const std::string				storage_name("A_1");
		readContributions(contribution_map, storage_name, storage_path);

		int value_i = contribution_map.getContribution<int>("a_1", "A_1");
		std::cout << "value int from container: " << value_i << std::endl;
		std::string value_s = contribution_map.getContribution<std::string>("a_2", "A_1");
		std::cout << "value string from container: " << value_s << std::endl;
    }
	catch(const std::exception& e) {
        std::cout << "Caught error meaning: " << e.what() << '\n';
    }
}
