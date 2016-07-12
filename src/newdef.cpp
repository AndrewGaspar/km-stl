#include "..\inc\new"

void * _cdecl operator new(std::size_t count, std::nothrow_t const &)
{
    return ExAllocatePoolWithTag(PagedPool, count, 'KSTD');
}

void _cdecl operator delete(void* ptr, std::nothrow_t const &)
{
    ExFreePool(ptr);
}

void * _cdecl operator new[](std::size_t count, std::nothrow_t const &)
{
    return ExAllocatePoolWithTag(PagedPool, count, 'KSAR');
}

void _cdecl operator delete[](void* ptr, std::nothrow_t const &)
{
    ExFreePool(ptr);
}

void _cdecl operator delete(void* ptr, std::size_t)
{
    ExFreePool(ptr);
}

void _cdecl operator delete[](void* ptr, std::size_t)
{
    ExFreePool(ptr);
}

void * _cdecl operator new(std::size_t, void* ptr)
{
    return ptr;
}

void _cdecl operator delete(void*, void*)
{
    // DO NOTHING
}

void* _cdecl operator new[](std::size_t, void* ptr)
{
    return ptr;
}

void _cdecl operator delete[](void*, void*)
{
    // DO NOTHING
}