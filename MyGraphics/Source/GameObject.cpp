#include "GameObject.h"

int GameObject::count_ = 0;

/******************************************************************************/
/*!
\brief
Constructor with 1 string argument - construct an object with a name assigned to it and add 1 to the count_ 

\param str - the Name of the GameObject
*/
/******************************************************************************/
GameObject::GameObject(const string& str)
{
	const_cast<string&>(kName) = str;
	++count_;
}

/******************************************************************************/
/*!
\brief
Destructor - destroys GameObject and decrease count_ by 1 when it goes out of scope or deleted
*/
/******************************************************************************/
GameObject::~GameObject()
{
	--count_;
}

/******************************************************************************/
/*!
\brief
Get the string kName and does not take in any argument

\return
string kName
*/
/******************************************************************************/
string GameObject::getName(void)
{
	return kName;
}

/******************************************************************************/
/*!
\brief
Get the value of count_

\return
value of count_
*/
/******************************************************************************/
int GameObject::getCount()
{
	return count_;
}