#include "types.hh"
#include <stdio.h>

// TODO: integrate with string type

#define Test_Init(name) \
	bool test_ok_ = true;\
	int test_failed_ = 0;\
	int test_count_ = 0;\
	const char* test_name_ = #name;\
	fprintf(stderr, "[ %s ]\n", #name);

#define Test_Eq(expect, expr) {\
	test_count_ += 1;\
	if((expect) == (expr)){\
		fprintf(stderr, "\tOK    ");\
	} else {\
		fprintf(stderr, "\tFAIL  ");\
		test_ok_ = false;\
		test_failed_ += 1;\
	}\
	fprintf(stderr, "%s => %s\n", #expr, #expect);\
}

#define Test_End() \
	if(test_ok_){\
		fprintf(stderr, "[PASSED] %s\n", test_name_);\
	} else {\
		fprintf(stderr, "[FAILED] %s\n", test_name_);\
	}

