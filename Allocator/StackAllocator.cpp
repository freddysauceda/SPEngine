#include "stdafx.h"
#include "StackAllocator.h"

StackAllocator::StackAllocator( const size_t a_qwTotalSize )
    : BaseAllocator( a_qwTotalSize ) {};

//StackAllocator::StackAllocator( StackAllocator &StackAllocator )
//{
//    m_dwOffset = StackAllocator.m_dwOffset;
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
    m_pStartPtr = malloc( m_dwTotalSize );
    m_dwOffset = 0;
}

void * StackAllocator::Allocate( const size_t & a_qwSize, const size_t & a_qwAlignment )
{
    const size_t qwCurrentAddress = ( size_t ) m_pStartPtr + m_dwOffset;

    size_t qwPadding = PaddingMath::GetPaddingWithHeader( qwCurrentAddress, a_qwAlignment, sizeof( Header ) );

    if ( m_dwOffset + qwPadding + a_qwSize > m_dwTotalSize ) {
        return nullptr;
    }
    m_dwOffset += qwPadding;

    const size_t qwNextAddress = qwCurrentAddress + qwPadding;
    const size_t qwHeaderAddress = qwNextAddress - sizeof( Header );
    Header AllocationHeader { static_cast<u8>( qwPadding ) };
    Header * HeaderPtr = ( Header* ) qwHeaderAddress;
    HeaderPtr = &AllocationHeader;

    m_dwOffset += a_qwSize;

#ifdef _DEBUG
    std::cout << "A" << "\t@C " << ( void* ) currentAddress << "\t@R " << ( void* ) nextAddress << "\tO " << m_offset << "\tP " << padding << std::endl;
#endif
    m_dwUsed = m_dwOffset;
    m_dwPeak = max( m_dwPeak, m_dwUsed );

    // void* is a 64-bit address so this is safe
    return ( void* ) qwNextAddress;
}

void StackAllocator::Free( void * ptr )
{
    // Move offset back to clear address
    const size_t currentAddress = ( size_t ) ptr;
    const size_t headerAddress = currentAddress - sizeof( Header );
    const Header * allocationHeader{ ( Header * ) headerAddress };

    m_dwOffset = currentAddress - allocationHeader->uPadding - ( size_t ) m_pStartPtr;
    m_dwUsed = m_dwOffset;

#ifdef _DEBUG
    std::cout << "F" << "\t@C " << ( void* ) currentAddress << "\t@F " << ( void* ) ( ( char* ) m_start_ptr + m_offset ) << "\tO " << m_offset << std::endl;
#endif
}

void StackAllocator::Reset()
{
    m_dwOffset = 0;
    m_dwUsed = 0;
    m_dwPeak = 0;
}
