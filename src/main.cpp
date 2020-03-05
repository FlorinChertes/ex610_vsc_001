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
   
   return 0;
}
