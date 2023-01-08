#include "alloc.hh"
#include "types.hh"

struct Pool_Free_Node {
	Pool_Free_Node* next;
};

struct Pool_Alloc {
	byte* buf;
	Pool_Free_Node* next;
	usize pool_size;
	usize pool_count;
	usize align;

	void* alloc(){}

	void* zalloc(){}

	void free(void* ptr){}

	void free_all(){}
};

static void init_pool_alloc(Pool_Alloc& al, void* buf, usize buf_len,
                            usize chunk_size, usize chunk_count, usize align = DEF_ALIGN){
	assert((chunk_size >= sizeof(Pool_Free_Node)) && "Chunk size too small");
}
static void init_pool_alloc(Pool_Alloc& al, usize chunk_size, usize chunk_count, usize align = DEF_ALIGN){
	assert((chunk_size >= sizeof(Pool_Free_Node)) && "Chunk size too small");
}

static void destroy_pool_alloc(Pool_Alloc& al, bool use_free = false){}

