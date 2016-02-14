/******************************************************************************/
/*!
\file       Utility.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
creating operators
*/
/******************************************************************************/
#ifndef UTILITY_H_
#define UTILITY_H_

#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, const Position& rhs);

#endif