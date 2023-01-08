#include <cstdlib>
#include <iostream>
#define print(x) std::cout << x << '\n'

#include "tests.cc"

int main(int argc, const char** argv){
	i32 results = test_linear_alloc() + test_maybe();
	return results;
}
