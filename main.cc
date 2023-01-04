#include <cstdlib>
#include <iostream>
#include "maybe.hh"
#include "test.hh"
#include "linear_alloc.hh"
#define print(x) std::cout << x << '\n'

void test_linear_alloc(){
	Test_Init("Linear allocator");
	usize buflen = KiB(1);
	usize align = alignof(max_align_t);
	Linear_Alloc al = Linear_Alloc(malloc(buflen), buflen, align);
	Test_Log("Init");
	Test_Exp(buflen, al.cap);
	Test_Exp(0, al.off);
	Test_Exp(align, al.align);

	Test_Log("Fill");
	Test_Exp(false, al.buf == nullptr);
	i32* vec = make<i32>(256, al);
	Test_Exp(true, nullptr != vec);
	Test_Exp(buflen, al.off);

	Test_Log("Fail alloc");
	Test_Exp(false, al.buf == nullptr);
	i32* vec2 = make<i32>(1, al);
	Test_Exp(nullptr, vec2);
	Test_Exp(buflen, al.off);

	Test_Log("Free all");
	al.free_all();
	Test_Exp(0, al.off);

	Test_Log("Alloc after free");
	vec2 = make<i32>(69, al);
	Test_Exp(true, nullptr != vec2);

	Test_End();
}
int main(int argc, const char** argv){
	test_linear_alloc();
	return 0;
}
