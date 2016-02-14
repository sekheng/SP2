/******************************************************************************/
/*!
\file       DetectMemoryLeak.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief
Check whether is there memory leak by improving the memory allocation.
Taken from Mr Sim's Data Struct Assignment 2 codes.
*/
/******************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
