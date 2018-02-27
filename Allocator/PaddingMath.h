#ifndef PADDING_MATH_H
#define PADDING_MATH_H

class PaddingMath
{
public:
    static const size_t GetPadding( const size_t& a_qwBaseAddress, const size_t& a_qwAlignment )
    {
        const size_t qwMultiplier = ( a_qwBaseAddress / a_qwAlignment ) + 1;
        const size_t qwAlignedAddress = qwMultiplier * a_qwAlignment;
        const size_t qwPadding = qwAlignedAddress - a_qwBaseAddress;
        return qwPadding;
    }

    static const size_t GetPaddingWithHeader( const size_t& a_qwBaseAddress, const size_t& a_qwAlignment, const size_t& a_qwHeaderSize ) {
        size_t qwPadding = GetPadding( a_qwBaseAddress, a_qwAlignment );
        size_t qwNeededSpace = a_qwHeaderSize;

        if ( qwPadding < qwNeededSpace ){
            // Header doesn't fit, get the next address that does, make sure to align it to the 4 byte boundary
            qwNeededSpace -= qwPadding;

            // How many alignments I need to fit       
            if ( qwNeededSpace % a_qwAlignment > 0 ){
                qwPadding += a_qwAlignment * ( 1 + ( qwNeededSpace / a_qwAlignment ) );
            }
            else {
                qwPadding += a_qwAlignment * ( qwNeededSpace / a_qwAlignment );
            }
        }

        return qwPadding;
    }
};

#endif // !PADDING_MATH_H
