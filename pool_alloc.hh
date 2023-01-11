#include "alloc.hh"
#include "types.hh"
#include <stdlib.h>

struct Pool_Free_Node {
	Pool_Free_Node* next;
};

struct Pool_Alloc {
	byte* buf;
	Pool_Free_Node* head;
	usize buf_cap;
	usize pool_cap;
	usize align;

	void* alloc();
	void* zalloc();
	void free(void* ptr);
	void free_all();
};

void init_pool_alloc(Pool_Alloc& al, void* buf, usize buf_len, usize chunk_size, usize align = DEF_ALIGN);

void init_pool_alloc(Pool_Alloc& al, usize chunk_size, usize chunk_count, usize align = DEF_ALIGN);

Pool_Alloc make_pool_alloc(void* buf, usize buf_len, usize chunk_size, usize align = DEF_ALIGN);

Pool_Alloc make_pool_alloc(usize chunk_size, usize chunk_count, usize align = DEF_ALIGN);

void destroy_pool_alloc(Pool_Alloc& al, bool use_free = false);

// Helper function that checks if one chunk of the pool allocator can fit n
// units of type T, returns a chunk if it fits and is available.
template<class T>
T* make(usize n, Pool_Alloc& al){
	if((sizeof(T) * n) > sizeof(al.pool_cap)){ return nullptr; }
	T* ptr = static_cast<T*>(al.zalloc());
	return ptr;
}

