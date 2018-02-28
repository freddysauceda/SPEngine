#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

#include "BaseAllocator.h"

class StackAllocator : public BaseAllocator
{
protected:
    void* m_pStartPtr = nullptr;
    size_t m_Offset;
public:
    StackAllocator( const size_t a_TotalSize );
    virtual ~StackAllocator();

    virtual void*   Allocate( const size_t& a_Size, const size_t& a_Alignment = 0 ) override;
    virtual void    Free( void* ptr );
    virtual void    Init() override;
    virtual void    Reset();
private:
    //StackAllocator( StackAllocator &StackAllocator );

    struct Header
    {
        u8 m_padding;
    };
};


#endif