#include "types.hh"
#include "alloc.hh"

// TODO: resize and free
#include <iostream>
#define print(x) std::cout << x << '\n'

// Linear Allocator

struct Linear_Alloc {
	byte* buf;
	usize cap;
	usize off;
	usize align;

	void* alloc(usize nbytes){
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

	Linear_Alloc(void* buf, usize buf_len, usize align = alignof(max_align_t)){
		this->buf   = static_cast<byte*>(buf);
		this->cap   = buf_len;
		this->off   = 0;
		this->align = align;
	}
};

template<class T>
T* make(usize n, Linear_Alloc& al){
	T* ptr = static_cast<T*>(al.alloc(sizeof(T) * n));
	return ptr;
}

