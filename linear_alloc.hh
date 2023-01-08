#ifndef INCLUDE_LINEAR_ALLOC_HH_
#define INCLUDE_LINEAR_ALLOC_HH_

#include "types.hh"
#include "alloc.hh"

#include <stdlib.h>

// TODO: resize and free

// Linear Allocator
struct Linear_Alloc {
	byte* buf;
	usize cap;
	usize off;

	void* alloc(usize nbytes, usize align = DEF_ALIGN){
		if(nbytes == 0 || nbytes > cap){ return nullptr; }

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

	void* zalloc(usize nbytes, usize align = DEF_ALIGN){
		void* ptr = this->alloc(nbytes, align);
		if(ptr != nullptr){
			byte* zp = static_cast<byte*>(ptr);
			for(usize i = 0; i < nbytes; i += 1){
				zp[i] = 0;
			}
		}
		return ptr;
	}

	void free_all(){
		off = 0;
	}
};

// Initializes a linear allocator
static void init_linear_alloc(Linear_Alloc& al, void* buf, usize buf_len){
	al.buf   = static_cast<byte*>(buf);
	al.cap   = buf_len;
	al.off   = 0;
}

// Wrapper to allocate buf automatically with malloc()
static void init_linear_alloc(Linear_Alloc& al, usize buf_len){
	init_linear_alloc(al, malloc(buf_len), buf_len);
}

// Create an initialized linear allocator
static Linear_Alloc make_linear_alloc(void* buf, usize buf_len){
	Linear_Alloc al;
	init_linear_alloc(al, buf, buf_len);
	return al;
}

// Create an initialized linear allocator, use malloc() for buffer
static Linear_Alloc make_linear_alloc(usize buf_len){
	Linear_Alloc al;
	init_linear_alloc(al, buf_len);
	return al;
}

// De-initialize linear allocator
// TODO: intead of bool free buf, pass an optional Allocator that runs its free() function on al.buf
static void destroy_linear_alloc(Linear_Alloc& al, bool free_buf = false){
	if(free_buf){ free(al.buf); }
	al.buf   = nullptr;
	al.off   = 0;
	al.cap   = 0;
}

// Helper function to allocate n units of a type T
template<class T>
T* make(usize n, Linear_Alloc& al){
	T* ptr = static_cast<T*>(al.zalloc(sizeof(T) * n, alignof(T)));
	return ptr;
}

#endif /* header guard */
