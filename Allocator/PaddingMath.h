#ifndef PADDING_MATH_H
#define PADDING_MATH_H

class PaddingMath
{
public:
    static const size_t GetPadding( const size_t& a_BaseAddress, const size_t& a_Alignment )
    {
        const size_t multiplier = ( a_BaseAddress / a_Alignment ) + 1;
        const size_t alignedAddress = multiplier * a_Alignment;
        const size_t padding = alignedAddress - a_BaseAddress;
        return padding;
    }

    static const size_t GetPaddingWithHeader( const size_t& a_BaseAddress, const size_t& a_Alignment, const size_t& a_HeaderSize ) {
        size_t padding = GetPadding( a_BaseAddress, a_Alignment );
        size_t neededSpace = a_HeaderSize;

        if ( padding < neededSpace ){
            // Header doesn't fit, get the next address that does, make sure to align it to the 4 byte boundary
            neededSpace -= padding;

            // How many alignments I need to fit       
            if ( neededSpace % a_Alignment > 0 ){
                padding += a_Alignment * ( 1 + ( neededSpace / a_Alignment ) );
            }
            else {
                padding += a_Alignment * ( neededSpace / a_Alignment );
            }
        }

        return padding;
    }
};

#endif // !PADDING_MATH_H
