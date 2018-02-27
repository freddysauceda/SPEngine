#include "stdafx.h"
#include "BaseAllocator.h"

BaseAllocator::BaseAllocator( const size_t& dwTotalSize )
{
    m_dwTotalSize = dwTotalSize;
    m_dwUsed = 0;
}

BaseAllocator::~BaseAllocator()
{
    m_dwTotalSize = 0;
}