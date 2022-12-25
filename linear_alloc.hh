#include "types.hh"
#include "alloc.hh"

struct Linear_Alloc {
	byte* buf;
	usize cap;
	usize off;
	usize align;

	void* alloc(usize nbytes){
		uintptr p   = reinterpret_cast<uintptr>(buf + off);
		uintptr lim = reinterpret_cast<uintptr>(buf + cap);
		p = align_forward_ptr(p, align);
		// Not enough space
		if((p + nbytes) >= lim){
			assert(0 && "Failed allocation");
			return nullptr;
		}

		off = lim - p + nbytes;
		return reinterpret_cast<void*>(p);
	}

	void* zalloc(usize nbytes){
		void* ptr = this->alloc(nbytes);
		byte* zero = static_cast<byte*>(ptr);
		for(usize i = 0; i < nbytes; i += 1){
			zero[i] = 0;
		}
		return ptr;
	}

	void free(){}

	Linear_Alloc(void* buf, usize buf_len, usize align = alignof(max_align_t)){
		this->buf   = static_cast<byte*>(buf);
		this->cap   = buf_len;
		this->off   = 0;
		this->align = align;
	}
};

template<class T>
T* make(usize n, Linear_Alloc& al){
}

