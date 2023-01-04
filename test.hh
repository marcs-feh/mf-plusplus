#include "types.hh"
#include <stdio.h>

// TODO: integrate with string type

#define COL_RED   "\e[0;31m"
#define COL_MAG   "\e[0;35m"
#define COL_GREEN "\e[0;32m"
#define COL_CYAN  "\e[0;36m"
#define COL_BLK   "\e[1;30m"
#define COL_RESET "\e[0m"

static inline void Test_Log(const char* msg){
	fprintf(stderr, "\t%s%s%s\n", COL_MAG, msg, COL_RESET);
}

#define Test_Init(name) \
	bool test_ok_ = true;\
	int test_failed_ = 0;\
	int test_count_ = 0;\
	const char* test_name_ = #name;\
	fprintf(stderr, "[ %s%s%s ]\n", COL_CYAN, #name, COL_RESET);

#define Test_Exp(expect, expr) {\
	test_count_ += 1;\
	if((expect) == (expr)){\
		fprintf(stderr, "\t%sOK%s    ", COL_GREEN, COL_RESET);\
	} else {\
		fprintf(stderr, "\t%sFAIL%s  ", COL_RED, COL_RESET);\
		test_ok_ = false;\
		test_failed_ += 1;\
	}\
	fprintf(stderr, "%s %s::%s %s\n", #expr, COL_BLK, COL_RESET, #expect);\
}

#define Test_End() \
	if(test_ok_){\
		fprintf(stderr, "[ %sPASSED%s ] ok: %d/%d\n", COL_GREEN, COL_RESET, test_count_ - test_failed_, test_count_);\
	} else {\
		fprintf(stderr, "[ %sFAILED%s ] ok: %d/%d\n", COL_RED, COL_RESET, test_count_ - test_failed_, test_count_);\
	}


