#ifndef INCLUDE_ALLOC_HH_
#define INCLUDE_ALLOC_HH_

#include "types.hh"
#include <assert.h>

static constexpr usize DEF_ALIGN = alignof(max_align_t);

static inline usize KiB(usize n) { return n * 1024; }
static inline usize MiB(usize n) { return n * 1024 * 1024; }
static inline usize GiB(usize n) { return n * 1024 * 1024 * 1024; }

static inline bool is_power2(uintptr n){
	return (n & (n - 1)) == 0;
}

// Aligns ptr to a certain alignment by incrementing it.
static uintptr align_forward_ptr(uintptr ptr, uintptr align){
	assert(is_power2(align) && "Alignment is not a power of 2");
	uintptr p = ptr;
	// same as p % align if a align is a power of 2
	uintptr mod = p & (align - 1);

	if(mod != 0){
		p += (align - mod);
	}

	return p;
}

// Aligns size to a certain alignment by incrementing it.
static usize align_forward_size(usize ptr, usize align){
	assert(is_power2(align) && "Alignment is not a power of 2");
	usize p = ptr;
	// same as p % align if a align is a power of 2
	usize mod = p & (align - 1);

	if(mod != 0){
		p += (align - mod);
	}

	return p;
}


#endif /* header guard */
