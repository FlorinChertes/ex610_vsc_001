#include <test_func_02.h>
#include <test_func_01.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
   test_person_ctor();
   test_person_default_ctor();
   test_person_copy_ctor();
   test_person_elision_copy();  
   test_person_lvalue();

   test_func_02_01();
   test_func_02_02();
   test_func_02_03();
   test_func_02_04();
   test_func_02_05();
   test_func_02_06();
   test_func_02_07();
   test_func_02_09();

   test_func_02_10();
   test_func_02_11();

   return 0;
}
