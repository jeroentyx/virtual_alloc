#pragma once

#include "entity.h"

//a c++20 , low-level memory allocation
// didn't see much virtualAlloc in github or tutorials
// so i decided to write my own , this serves as a building block
// for people who want to push their memory pool further
class Pool
{
public:
	template<typename T>
	static T* ReserveMemory(const T& m)
	{
		int nPages = 1; //worst case of page allocation
		int virtual_page_size = 4096;
		LPVOID pageStartPtr = VirtualAlloc(nullptr, nPages * virtual_page_size, MEM_RESERVE, PAGE_NOACCESS);
		return reinterpret_cast<T*>(pageStartPtr);
	}

	template<virtual_object T>
	static T* ReserveMemory(const T&& m)
	{
		int nPages = 1; //worst case of pages allocation
		int virtual_page_size = 4096;
		LPVOID pageStartPtr = VirtualAlloc(nullptr, nPages * virtual_page_size, MEM_RESERVE, PAGE_NOACCESS);
		return reinterpret_cast<T*>(pageStartPtr);
	}

	//Once you Reserve the Virtual Memory, you need to COMMIT the virtual memory
	// to be able to write or read on the virtual memory
	// Extra-type safe
	// learnt about virtual_memory after reading  from unity new ECS doc
	template<virtual_object T>
	static void AllocateMemory(T* m)
	{
		int pageSize = 4096;
		VirtualAlloc(m, 4096, MEM_COMMIT, PAGE_READWRITE);
	}

	template<virtual_object T>
	static void FreeMemory(const T* m)
	{
		//virtual alloc
		bool throwErr = VirtualFree(LPVOID(m), 0, MEM_RELEASE);
		assert(throwErr, "pool deallocation unsuccessful");
	}
};