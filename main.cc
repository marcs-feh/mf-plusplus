#include <iostream>
#include "maybe.hh"
#include "test.hh"
#define print(x) std::cout << x << '\n'

int divide(int a, int b){
	if(b == 0)
		return 0;
	return a / b;
}

void test_divide() {
	Test_Init(Divide);
	Test_Eq(3, divide(9, 3));
	Test_Eq(3, divide(9, 3));
	Test_Eq(4, divide(1, 0));
	Test_End();
}
int main(int argc, const char** argv){
	test_divide();
	return 0;
}
