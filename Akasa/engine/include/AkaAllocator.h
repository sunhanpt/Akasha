// allocator

#ifndef __I_ILOGGER_H_INCLUDED__
#define __I_ILOGGER_H_INCLUDED__
#include <new>
#include <memory.h>

namespace aka
{
namespace core
{
#ifdef DEBUG_CLIENTBLOCK
#undef DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK new
#endif
	template<typename T>
	class akaAllocator
	{
	public:
		akaAllocator() {};
		virtual ~akaAllocator() {};

		// 分配一个数组的内存
		T* allocate(size_t cnt)
		{
			return (T*)internal_new(cnt * sizeof(T));
		}

		// 释放一个数组的内存
		void deallocate(T* ptr)
		{
			internal_delete(ptr);
		}

		// construct an element
		void construct(T* ptr, const T& e)
		{
			new ((void*)ptr) T(e);
		}

		// destruct an element
		void destruct(T * ptr)
		{
			ptr->~T();
		}

	protected:
		virtual void* internal_new(size_t cnt)
		{
			return operator new(cnt);
		}
		virtual void* internal_delete(void * ptr)
		{
			operator delete(ptr);
		}
	};

#ifdef DEBUG_CLIENTBLOCK
#undef DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif


} // end namespace core

} // end namespace aka

#endif

