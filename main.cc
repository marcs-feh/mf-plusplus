#include <cstdlib>
#include <iostream>

#include "maybe.hh"
#include "test.hh"
#include "linear_alloc.hh"
#include "ring_buf_alloc.hh"

#define print(x) std::cout << x << '\n'

i32 test_linear_alloc(){
	Test_Init("Linear allocator");
	usize buflen = KiB(1);
	usize align = alignof(max_align_t);
	Linear_Alloc al = make_linear_alloc(malloc(buflen), buflen, align);
	Test_Log("Init");
	Test_Exp(buflen, al.cap);
	Test_Exp(0, al.off);
	Test_Exp(align, al.align);
	Test_Exp(true, nullptr != al.buf);

	Test_Log("alloc(0)");
	Test_Exp(nullptr, al.alloc(0));

	Test_Log("alloc(al.cap + 1)");
	Test_Exp(nullptr, al.alloc(al.cap + 1));

	Test_Log("Fill");
	Test_Exp(false, al.buf == nullptr);
	i32* vec = make<i32>(256, al);
	Test_Exp(true, nullptr != vec);
	Test_Exp(buflen, al.off);

	Test_Log("Fail alloc");
	i32* vec2 = make<i32>(1, al);
	Test_Exp(nullptr, vec2);
	Test_Exp(buflen, al.off);

	Test_Log("Free all");
	al.free_all();
	Test_Exp(0, al.off);

	Test_Log("Alloc after free");
	vec2 = make<i32>(69, al);
	Test_Exp(true, nullptr != vec2);

	Test_Log("Destroy");
	destroy_linear_alloc(al, true);
	Test_Exp(0, al.cap);
	Test_Exp(0, al.off);
	Test_Exp(0, al.align);
	Test_Exp(nullptr, al.buf);

	Test_End();
}

i32 test_ring_alloc(){
	Test_Init("Circular allocator");

	Test_End();
}

int main(int argc, const char** argv){
	i32 results = test_linear_alloc() + test_ring_alloc();
	return results;
}
