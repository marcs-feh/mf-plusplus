#include "alloc.hh"

// Aligns ptr to a certain alignment by incrementing it.
uintptr align_forward_ptr(uintptr ptr, uintptr align){
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
usize align_forward_size(usize ptr, usize align){
	assert(is_power2(align) && "Alignment is not a power of 2");
	usize p = ptr;
	// same as p % align if a align is a power of 2
	usize mod = p & (align - 1);

	if(mod != 0){
		p += (align - mod);
	}

	return p;
}
