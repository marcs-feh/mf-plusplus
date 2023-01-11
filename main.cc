#include <cstdlib>
#include <iostream>
#define print(x) std::cout << x << '\n'

#include "log.hh"
#include "tests.hh"

i32 test_pool_alloc(){
	Test_Init("Pool allocator");
	Test_Log("Initialization");
	Pool_Alloc al = make_pool_alloc(64, 8);
	Test_Exp(true, al.head != nullptr);
	Test_Exp(true, al.buf != nullptr);
	Test_End();
}

int main(int argc, const char** argv){
	i32 results =
		+ test_linear_alloc()
		+ test_maybe()
		+ test_pool_alloc();
	return results;
}
