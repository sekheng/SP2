#include "Utility.h"

/******************************************************************************/
/*!
\brief -
an operator to multiply Mtx44 and positionc coordinates

\param lhs - the matrix
\param rhx - the position

\return a new copy of Position
*/
/******************************************************************************/
Position operator*(const Mtx44& lhs, const Position& rhs)
{
	float b[4];
	for (int i = 0; i < 4; i++)
		b[i] = lhs.a[0 * 4 + i] * rhs.x + lhs.a[1 * 4 + i] * rhs.y + lhs.a[2 * 4 + i] * rhs.z + lhs.a[3 * 4 + i] * 1;
	return Position(b[0], b[1], b[2]);
}