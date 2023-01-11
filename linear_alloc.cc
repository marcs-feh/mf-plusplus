#include "linear_alloc.hh"
// TODO: resize and free

void* Linear_Alloc::alloc(usize nbytes, usize align){
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

void* Linear_Alloc::zalloc(usize nbytes, usize align){
	void* ptr = this->alloc(nbytes, align);
	if(ptr != nullptr){
		byte* zp = static_cast<byte*>(ptr);
		for(usize i = 0; i < nbytes; i += 1){
			zp[i] = 0;
		}
	}
	return ptr;
}

void Linear_Alloc::free_all(){
	off = 0;
}

// Initializes a linear allocator
void init_linear_alloc(Linear_Alloc& al, void* buf, usize buf_len){
	al.buf   = static_cast<byte*>(buf);
	al.cap   = buf_len;
	al.off   = 0;
}

// Wrapper to allocate buf automatically with malloc()
void init_linear_alloc(Linear_Alloc& al, usize buf_len){
	init_linear_alloc(al, malloc(buf_len), buf_len);
}

// Create an initialized linear allocator
Linear_Alloc make_linear_alloc(void* buf, usize buf_len){
	Linear_Alloc al;
	init_linear_alloc(al, buf, buf_len);
	return al;
}

// Create an initialized linear allocator, use malloc() for buffer
Linear_Alloc make_linear_alloc(usize buf_len){
	Linear_Alloc al;
	init_linear_alloc(al, buf_len);
	return al;
}

// De-initialize linear allocator
// TODO: intead of bool free buf, pass an optional Allocator that runs its free() function on al.buf
void destroy_linear_alloc(Linear_Alloc& al, bool free_buf){
	if(free_buf){ free(al.buf); }
	al.buf   = nullptr;
	al.off   = 0;
	al.cap   = 0;
}

