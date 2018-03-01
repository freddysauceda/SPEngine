#include "stdafx.h"
#include "StackAllocator.h"

StackAllocator::StackAllocator( const size_t a_TotalSize )
    : BaseAllocator( a_TotalSize ) {};

//StackAllocator::StackAllocator( StackAllocator &StackAllocator )
//{
//    m_Offset = StackAllocator.m_Offset;
//    m_pStartPtr = StackAllocator.m_pStartPtr;
//}

StackAllocator::~StackAllocator()
{
    Free( m_pStartPtr );
    m_pStartPtr = nullptr;
}

void StackAllocator::Init()
{
    if ( m_pStartPtr != nullptr ) {
        Free( m_pStartPtr );
    }
    m_pStartPtr = malloc( m_TotalSize );
    m_Offset = 0;
}

void * StackAllocator::Allocate( const size_t & a_Size, const size_t & a_Alignment )
{
    const size_t currentAddress = ( size_t ) m_pStartPtr + m_Offset;

    size_t padding = PaddingMath::GetPaddingWithHeader( currentAddress, a_Alignment, sizeof( Header ) );

    if ( m_Offset + padding + a_Size > m_TotalSize ) {
        return nullptr;
    }
    m_Offset += padding;

    const size_t nextAddress = currentAddress + padding;
    const size_t headerAddress = nextAddress - sizeof( Header );
    Header allocationHeader { (u8) padding };
    Header* pHeaderPtr = ( Header* ) headerAddress;
    pHeaderPtr = &allocationHeader;

    m_Offset += a_Size;

#ifdef _DEBUG
    std::cout << "A" << "\t@C " << ( void* ) currentAddress << "\t@R " << ( void* ) nextAddress << "\tO " << m_offset << "\tP " << padding << std::endl;
#endif
    m_Used = m_Offset;
    m_Peak = max( m_Peak, m_Used );

    // void* is a 64-bit address so this is safe
    return ( void* ) nextAddress;
}

void StackAllocator::Free( void* a_Ptr )
{
    // Move offset back to clear address
    const size_t currentAddress = ( size_t ) a_Ptr;
    const size_t headerAddress = currentAddress - sizeof( Header );
    const Header * allocationHeader{ ( Header * ) headerAddress };

    m_Offset = currentAddress - allocationHeader->m_padding - ( size_t ) m_pStartPtr;
    m_Used = m_Offset;

#ifdef _DEBUG
    std::cout << "F" << "\t@C " << ( void* ) currentAddress << "\t@F " << ( void* ) ( ( char* ) m_pStartPtr + m_Offset ) << "\tO " << m_Offset << std::endl;
#endif
}

void StackAllocator::Reset()
{
    m_Offset = 0;
    m_Used = 0;
    m_Peak = 0;
}
