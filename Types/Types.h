#ifndef TYPES_H
#define TYPES_H

//Typedef for the different types

typedef unsigned char   u8;
typedef int             s32;
typedef long            s64;
typedef unsigned int    u32;
typedef unsigned long   u64;
typedef float           f32;
typedef double          f64;

template<class T>
class Node
{
public:
    Node( const T& data );
    ~Node();

    inline const T GetData() const;
    inline const Node<T>* GetNext();

    inline void SetData( const T& data );
    inline void SetNext( const Node<T>* a_next );
private:
    T m_data;
    Node<T>* m_pNext;
};

template<class T>
class List
{
public:
    inline const s32 Size() const = 0;
    inline const s32 Push( Node<T>* a_toAdd ) = 0;
    inline const T Pop() = 0;
    inline const bool IsEmpty() const = 0;
private:
    Node<T>* m_pRoot;
    u32 m_size = 0;
};

//TODO replace with jmalloc or custom allocator
template<class T>
class Stack : public List<T>
{
public:
    //Returns exactly what you think
    inline const s32 Size() const override;
    //Returns the index where the node was added, else return -1 on a failure
    inline const s32 Push( T a_data ) override;
    //Pops the data at end of the stack
    inline const T Pop() override;
    //Checks if the stack is empty
    inline const bool IsEmpty() const override;
    
    //Sees the data at the end without popping
    inline const T Peek();
private:
    Node<T>* m_pTop;
};

#include "Lists.inc"

#endif // !TYPES_H