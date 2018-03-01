#include "stdafx.h"
#include "BaseAllocator.h"

BaseAllocator::BaseAllocator( const size_t& a_TotalSize )
{
    m_TotalSize = a_TotalSize;
    m_Used = 0;
}

BaseAllocator::~BaseAllocator()
{
    m_TotalSize = 0;
}