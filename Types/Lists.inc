#pragma once

//Begin Node<T> implementation
template<class T>
inline Node<T>::Node( const T& data )
{
    m_data = data;
}

template<class T>
inline Node<T>::~Node()
{
}

template<class T>
inline const T Node<T>::GetData() const
{
    return m_data;
}

template<class T>
inline const Node<T>* Node<T>::GetNext()
{
    return m_pNext;
}

template<class T>
inline void Node<T>::SetData( const T& data )
{
    m_data = data;
}

template<class T>
inline void Node<T>::SetNext( const Node<T>* a_next )
{
    m_pNext = a_next;
}

//Begin Stack<T> implementation
template<typename T>
inline const s32 Stack<T>::Size() const
{
    return m_size;
}

template<typename T>
inline const s32 Stack<T>::Push( T a_data )
{
    Node<T>* newNode = new Node( a_data );
    newNode->SetNext( m_pRoot );
    m_pRoot = newNode;

    m_size++
    return m_size;
}

template<typename T>
inline const T Stack<T>::Pop()
{
    if ( IsEmpty() )
    {
        return nullptr;
    }

    Node<T>* temp = m_pRoot;
    m_pRoot->SetNext( m_pRoot->GetNext() );
    T poppedData = temp->GetData();
    free( temp );

    return poppedData;
}

template<typename T>
inline const bool Stack<T>::IsEmpty() const
{
    return ( m_size == 0);
}

template<class T>
inline const T Stack<T>::Peek()
{
    if ( m_size == 0 )
    {
        static_assert( false, "Peeking an empty list\n" );
    }
    return m_pRoot->GetData();
}