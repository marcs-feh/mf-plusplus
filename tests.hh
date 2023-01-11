#include "test.hh"
#include "maybe.hh"
#include "linear_alloc.hh"
#include "pool_alloc.hh"

static i32 test_maybe(){
	Test_Init("Maybe types");
	Maybe<i32> a, b;
	Test_Log("Initialization");
	Test_Exp(nil, a);
	Test_Log("Assignment");
	a = 7;
	Test_Exp(true, a == 7);
	a = nil;
	Test_Exp(true, a == nil);
	Test_Log("Identity");
	Test_Exp(true, nil == nil);
	Test_Exp(false, nil != nil);
	Test_Log("Equality(maybe/nil)");
	Test_Exp(true, a == nil);
	Test_Exp(true, nil == a);
	Test_Exp(false, a != nil);
	Test_Exp(false, nil != a);
	Test_Log("Equality(maybe/non-maybe)");
	i32 num = 6;
	a = num;
	Test_Exp(true, num == a);
	Test_Exp(true, a == num);
	Test_Exp(false, num != a);
	Test_Exp(false, a != num);
	Test_Log("Equality(maybe/maybe)");
	a = nil;
	Test_Exp(true, a == b);
	Test_Exp(true, b == a);
	Test_Exp(false, a != b);
	Test_Exp(false, b != a);
	b = 5;
	Test_Exp(false, a == b);
	Test_Exp(false, b == a);
	Test_Exp(true, a != b);
	Test_Exp(true, b != a);
	Test_Log("Boolean conversion");
	Maybe<f32> n;
	Test_Exp(false, !!n);
	n = 8.4;
	Test_Exp(true, !!n);
	Test_End();
}

static i32 test_linear_alloc(){
	Test_Init("Linear allocator");
	usize buflen = KiB(1);
	Linear_Alloc al = make_linear_alloc(malloc(buflen), buflen);
	Test_Log("Init");
	Test_Exp(buflen, al.cap);
	Test_Exp(0, al.off);
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
	Test_Exp(nullptr, al.buf);

	Test_End();
}

