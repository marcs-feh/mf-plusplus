#include "alloc.hh"
#include <stdlib.h>

struct LibC_Alloc {
	void* alloc(usize nbytes){
		return malloc(nbytes);
	}

	void* zalloc(usize nbytes){
		void* ptr = malloc(nbytes);
		if(ptr != nullptr){
			byte* zp  = static_cast<byte*>(ptr);
			for(usize i = 0; i < nbytes; i += 1){
				zp[i] = 0;
			}
		}
		return ptr;
	}

	void free(void* ptr){
		free(ptr);
	}
} static std_alloc;

