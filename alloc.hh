#ifndef INCLUDE_ALLOC_HH_
#define INCLUDE_ALLOC_HH_

#include "types.hh"
#include <assert.h>

constexpr usize DEF_ALIGN = alignof(max_align_t);

constexpr inline usize KiB(usize n) { return n * 1024; }
constexpr inline usize MiB(usize n) { return n * 1024 * 1024; }
constexpr inline usize GiB(usize n) { return n * 1024 * 1024 * 1024; }

constexpr inline bool is_power2(uintptr n){
	return (n & (n - 1)) == 0;
}

// Aligns ptr to a certain alignment by incrementing it.
uintptr align_forward_ptr(uintptr ptr, uintptr align);

// Aligns size to a certain alignment by incrementing it.
usize align_forward_size(usize ptr, usize align);

#endif /* header guard */
