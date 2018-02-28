#ifndef BASE_ALLOCATOR_H
#define BASE_ALLOCATOR_H

class BaseAllocator
{
public:
	BaseAllocator( const size_t& sdwTotalSize );
    ~BaseAllocator();

	////Rule of 5, move, move assignment
	//BaseAllocator();		                                              //Default
	//~BaseAllocator();		                                              //Destructor
	//BaseAllocator( const BaseAllocator& toCopy );                       //copy
	//virtual BaseAllocator& operator=( const BaseAllocator& other );     //copy assignment
	//virtual BaseAllocator& operator=( BaseAllocator&& other ) noexcept; //move

    virtual void* Allocate( const size_t& size, const size_t& alignment = 0 ) = 0;
    virtual void Init() = 0;
    virtual void Free( void* pPtr ) = 0;

protected:
    size_t m_TotalSize;
    size_t m_Used;
    size_t m_Peak;
};


#endif //BASE_ALLOCATOR_H