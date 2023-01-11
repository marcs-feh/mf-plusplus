#include "pool_alloc.hh"

void* Pool_Alloc::alloc(){
	// Failed alloc
	if(head == nullptr){ return nullptr; }

	void* chunk = static_cast<void*>(head);
	head = head->next;
	return chunk;
}

void* Pool_Alloc::zalloc(){
	void* p = this->alloc();
	if(p != nullptr){
		byte* zp = static_cast<byte*>(p);
		for(usize i = 0; i < pool_cap; i += 1){
			zp[i] = 0;
		}
	}
	return p;
}

void Pool_Alloc::free(void* ptr){
	uintptr p     = reinterpret_cast<uintptr>(ptr);
	uintptr base  = reinterpret_cast<uintptr>(buf);
	uintptr limit = base + buf_cap;
	assert(((p < base) || (p >= limit)) && "Pointer does not belong to this allocator");

	Pool_Free_Node* node = static_cast<Pool_Free_Node*>(ptr);
	node->next = head;
	head = node;
}

void Pool_Alloc::free_all(){
	usize chunk_count = buf_cap / pool_cap;
	for(usize i = 0; i < chunk_count; i += 1){
		void* p = &buf[i * pool_cap];
		Pool_Free_Node* node = static_cast<Pool_Free_Node*>(p);
		node->next = head;
		head = node;
	}
}

#include <stdio.h>
void init_pool_alloc(Pool_Alloc& al, void* buf, usize buf_len, usize chunk_size, usize align){
	uintptr base = reinterpret_cast<uintptr>(buf);
	uintptr aligned = align_forward_ptr(base, static_cast<uintptr>(align));
	chunk_size = align_forward_size(chunk_size, align);
	buf_len -= static_cast<usize>(base - aligned);

	assert((chunk_size >= sizeof(Pool_Free_Node)) && "Chunk size too small");
	assert((buf_len >= chunk_size ) && "Buffer size too small");

	al.buf      = static_cast<byte*>(buf);
	al.buf_cap  = buf_len;
	al.pool_cap = chunk_size;
	al.head     = nullptr;
	al.align    = align;

	al.free_all();
}

void init_pool_alloc(Pool_Alloc& al, usize chunk_size, usize chunk_count, usize align){
	usize bs = chunk_size * chunk_count;
	init_pool_alloc(al, malloc(bs), bs, chunk_size, align);
}

Pool_Alloc make_pool_alloc(usize chunk_size, usize chunk_count, usize align){
	Pool_Alloc al;
	init_pool_alloc(al, chunk_size, chunk_count, align);
	return al;
}

void destroy_pool_alloc(Pool_Alloc& al, bool use_free){}

