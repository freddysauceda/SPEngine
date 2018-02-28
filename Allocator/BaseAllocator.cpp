#include "stdafx.h"
#include "BaseAllocator.h"

BaseAllocator::BaseAllocator( const size_t& dwTotalSize )
{
    m_TotalSize = dwTotalSize;
    m_Used = 0;
}

BaseAllocator::~BaseAllocator()
{
    m_TotalSize = 0;
}