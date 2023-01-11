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

	void* alloc(usize nbytes, usize align = DEF_ALIGN);
	void* zalloc(usize nbytes, usize align = DEF_ALIGN);
	void free_all();
};

// Initializes a linear allocator
void init_linear_alloc(Linear_Alloc& al, void* buf, usize buf_len);

// Wrapper to allocate buf automatically with malloc()
void init_linear_alloc(Linear_Alloc& al, usize buf_len);

// Create an initialized linear allocator
Linear_Alloc make_linear_alloc(void* buf, usize buf_len);

// Create an initialized linear allocator, use malloc() for buffer
Linear_Alloc make_linear_alloc(usize buf_len);

// De-initialize linear allocator
// TODO: intead of bool free buf, pass an optional Allocator that runs its free() function on al.buf
void destroy_linear_alloc(Linear_Alloc& al, bool free_buf = false);

// Helper function to allocate n units of a type T
template<class T>
T* make(usize n, Linear_Alloc& al){
	T* ptr = static_cast<T*>(al.zalloc(sizeof(T) * n, alignof(T)));
	return ptr;
}

#endif /* header guard */
