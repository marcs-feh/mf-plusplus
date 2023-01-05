#include "types.hh"
#include "alloc.hh"

#include <cstdlib>
#include <stdlib.h>

// TODO: resize and free

// Linear Allocator

struct Linear_Alloc {
	byte* buf;
	usize cap;
	usize off;
	usize align;

	void* alloc(usize nbytes){
		if(nbytes == 0){ return nullptr; }

		uintptr base = reinterpret_cast<uintptr>(buf + off);
		uintptr ptr  = align_forward_ptr(base, align);
		uintptr lim  = reinterpret_cast<uintptr>(buf + cap);

		// Not enough space
		if((ptr + nbytes) > lim){
			//assert(0 && "Failed allocation");
			return nullptr;
		}

		off = (ptr - base) + nbytes;

		return reinterpret_cast<void*>(ptr);
	}

	void* zalloc(usize nbytes){
		void* ptr = this->alloc(nbytes);
		byte* zero = static_cast<byte*>(ptr);
		for(usize i = 0; i < nbytes; i += 1){
			zero[i] = 0;
		}
		return ptr;
	}

	void free_all(){
		off = 0;
	}
};

void init_linear_alloc(Linear_Alloc& al, void* buf, usize buf_len, usize align = alignof(max_align_t)){
	al.buf   = static_cast<byte*>(buf);
	al.cap   = buf_len;
	al.off   = 0;
	al.align = align;
}

void init_linear_alloc(Linear_Alloc& al, usize buf_len, usize align = alignof(max_align_t)){
	al.buf   = static_cast<byte*>(malloc(buf_len));
	al.cap   = buf_len;
	al.off   = 0;
	al.align = align;
}

Linear_Alloc make_linear_alloc(void* buf, usize buf_len, usize align = alignof(max_align_t)){
	Linear_Alloc al;
	init_linear_alloc(al, buf, buf_len, align);
	return al;
}

Linear_Alloc make_linear_alloc(usize buf_len, usize align = alignof(max_align_t)){
	Linear_Alloc al;
	return al;
}

void destroy_linear_alloc(Linear_Alloc& al, bool free_buf = false){
	if(free_buf){ free(al.buf); }
	al.buf   = nullptr;
	al.align = 0;
	al.off   = 0;
	al.cap   = 0;
}

template<class T>
T* make(usize n, Linear_Alloc& al){
	T* ptr = static_cast<T*>(al.alloc(sizeof(T) * n));
	return ptr;
}

