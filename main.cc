#include "log.hh"
#include "tests.hh"

#include <iostream>
i32 test_pool_alloc(){
	Test_Init("Pool allocator");
	Test_Log("Initialization");
	Pool_Alloc al = make_pool_alloc(64, 8);
	Test_Exp(64, al.pool_cap);
	Test_Exp(8, al.buf_cap / al.pool_cap);
	Test_Exp(64 * 8, al.buf_cap);
	//eprint("pcap:%zu, bcap:%zu\n", al.pool_cap, al.buf_cap / al.pool_cap);
	Test_Exp(true, al.head != nullptr);
	Test_Exp(true, al.buf != nullptr);
	Test_Log("Alloc too big");
	i32* nums = make<i32>(300, al);
	Test_Exp(nullptr, nums);

	Test_End();
}

int main(){
	log_ok("These log messages");
	log_info("Are just a test");
	log_warn("Nothing went wrong");
	log_error("I think");
	log_fatal(";)");
	i32 results =
		+ test_maybe()
		+ test_linear_alloc()
		+ test_pool_alloc();
	return results;
}
