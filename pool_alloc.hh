#include "alloc.hh"
#include "types.hh"

struct Pool_Free_Node {
	Pool_Free_Node* next;
};

struct Pool_Alloc {
	byte* buf;
	Pool_Free_Node* head;
	usize buf_cap;
	usize pool_cap;
	usize align;

	void* alloc(){}

	void* zalloc(){
	}

	void free(void* ptr){}

	void free_all(){
		usize chunk_count = buf_cap / pool_cap;
		for(usize i = 0; i < chunk_count; i += 1){
			void* p = &buf[i * pool_cap];
			Pool_Free_Node* node = static_cast<Pool_Free_Node*>(p);
			node->next = head;
			head = node;
		}
	}
};

static void init_pool_alloc(Pool_Alloc& al, void* buf, usize buf_len, usize chunk_size, usize align = DEF_ALIGN){
	uintptr base = reinterpret_cast<uintptr>(buf);
	uintptr aligned = align_forward_ptr(base, static_cast<uintptr>(align));
	buf_len -= static_cast<usize>(base - aligned);
	chunk_size = align_forward_size(chunk_size, align);

	assert((chunk_size >= sizeof(Pool_Free_Node)) && "Chunk size too small");
	assert((chunk_size >= buf_len) && "Buffer size too small");

	al.buf      = static_cast<byte*>(buf);
	al.buf_cap  = buf_len;
	al.pool_cap = chunk_size;
	al.head     = nullptr;
	al.align    = align;

	al.free_all();
}

static void init_pool_alloc(Pool_Alloc& al, usize chunk_size, usize chunk_count, usize align = DEF_ALIGN){
}

static void destroy_pool_alloc(Pool_Alloc& al, bool use_free = false){}

