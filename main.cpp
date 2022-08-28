#include "Build/Core/Pool.h"

void test1()
{
	//example
	int nPages = 1; //worst case
	int virtual_page_size = 4096;
	LPVOID pageStartPtr = VirtualAlloc(nullptr, nPages * virtual_page_size, MEM_RESERVE, PAGE_NOACCESS);

	//use this to commit
	int pageSize = 4096;
	VirtualAlloc(pageStartPtr, 4096, MEM_COMMIT, PAGE_READWRITE);

	int* intPtr = reinterpret_cast<int*>(pageStartPtr);

	if (intPtr)
	{
		*intPtr = 4;
	}

	if (pageStartPtr != nullptr)
	{
		std::cout << *intPtr << std::endl;
	}


	//this will release all allocated memory

	bool throwErr = VirtualFree(pageStartPtr, 0, MEM_RELEASE);

	assert(throwErr, "throw deallocation");
}

void test2()
{
	entity entt;
	entity* entityPointerToPool = Pool::ReserveMemory(entt);
	Pool::AllocateMemory(entityPointerToPool);

	//You are allocating 4096 bytes
	//so each int is 4 bytes
	// you have 1024 entity
	entityPointerToPool[0].m_entityID = 1;
	entityPointerToPool[1].m_entityID = 2;
	entityPointerToPool[3].m_entityID = 3;
	entityPointerToPool[1023].m_entityID = 3;

	std::cout << entityPointerToPool[0].m_entityID << std::endl;
	std::cout << entityPointerToPool[1].m_entityID << std::endl;
	std::cout << entityPointerToPool[3].m_entityID << std::endl;
	std::cout << entityPointerToPool[0].m_entityID << std::endl;

	entityPointerToPool->m_entityID = 4;
	std::cout << sizeof(entityPointerToPool->m_entityID) << std::endl;
	Pool::FreeMemory(entityPointerToPool);
}

int main()
{

	//examples
	test1();
	test2();


	return 0;
}