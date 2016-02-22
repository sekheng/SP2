#include "NumPad.h"
#include "MyMath.h"
#include "Application.h"
#include <fstream>
#include <iostream>
#include <map>
#include <locale>
#include <algorithm>

NumPad::NumPad() : GameObject("NumPad")
{

}

NumPad::~NumPad()
{

}

void NumPad::Init(Camera3 &cameraDub, const Vector3 &origPos)
{
	wheelturn = stickpush = dooropen = text = screentext = firstroll = secondroll = thirdroll = fourthroll = check = false;
	/*wheelturning = stickpushing = dooropening = */firstrotate = secondrotate = thirdrotate = fourthrotate = arrow = 0.0f;
	time = 0.0;
	time_delay = 0.2f;
	changearrow = 19.5;
	rendererror = false;
	digit1 = digit2 = digit3 = digit4 = 0;
	open = close = false;
	camera = &cameraDub;
	pos = origPos;
}

void NumPad::Update(double dt)
{

	if (interaction() == true)
	{
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			if (time > time_delay)
			{
				time = 0;
				changearrow += 15;
				if (changearrow > 64.5)
				{
					changearrow = 19.5;
				}
				arrow++;
				if (arrow > 3)
				{
					arrow = 0;
				}

			}
		}

		if (Application::IsKeyPressed(VK_LEFT))
		{
			if (time > time_delay)
			{
				time = 0;
				changearrow -= 15;
				if (changearrow < 19.5)
				{
					changearrow = 64.5;
				}
				arrow--;
				if (arrow < 0)
				{
					arrow = 3;
				}
			}
		}

		if (Application::IsKeyPressed(VK_RETURN))
		{
			check = true;
		}
		else
		{
			check = false;
		}
		if (Application::IsKeyPressed('C'))
		{
			open = true;
		}
		if (Application::IsKeyPressed('X'))
		{
			close = true;
		}
	}
	
	
	time += dt;
}

bool NumPad::interactiontext()
{
	if (interaction() == true )
	{
		return true;
	}
	return false;
}

void NumPad::NumpadProgram()
{
	if (interactiontext() == true && interaction()==true)
	{
		if (Application::IsKeyPressed('V') && arrow == 0)
		{
			if (time > time_delay)
			{
				time = 0;
				firstrotate += 36;
				digit1++;
				if (digit1 > 9)
				{
					digit1 = 0;
				}
				//input[0] = digit1;
			}
		}

		else if (Application::IsKeyPressed('V') && arrow == 1)
		{
			if (time > time_delay)
			{
				time = 0;
				secondrotate += 36;
				digit2++;
				if (digit2 > 9)
				{
					digit2 = 0;
				}
				//input[1] = digit2;
			}
		}

		else if (Application::IsKeyPressed('V') && arrow == 2)
		{
			if (time > time_delay)
			{
				time = 0;
				thirdrotate += 36;
				digit3++;
				if (digit3 > 9)
				{
					digit3 = 0;
				}
				//input[2] = digit3;
			}
		}

		else if (Application::IsKeyPressed('V') && arrow == 3)
		{
			if (time > time_delay)
			{
				time = 0;
				fourthrotate += 36;
				digit4++;
				if (digit4 > 9)
				{
					digit4 = 0;
				}
				//input[3] = digit4;
			}
		}
	}
}

bool NumPad::NumpadVerify()
{
	if (check==true)
	{
		if (digit1 == 9 && digit2 == 6 && digit3 == 6 && digit4 == 9)
		{
			return true;
			/*wheelturn = true;
			rendererror = false;*/
		}
			return false;
			/*wheelturn = false;
			if (time < time_delay)
			{

			rendererror = true;

			}
			else
			{
			rendererror = false;
			time = 0;
			}*/
	}
	//return true;
}

bool NumPad::displayerror()
{
	if (!NumpadVerify())
		return true;
	else if (NumpadVerify())
		return false;

	//return false;
	
}

bool NumPad::interaction()
{
	if ((pos.x + 23) > camera->getCameraXcoord() &&
		(pos.x - 18) < camera->getCameraXcoord() &&
		(pos.z + 40) > camera->getCameraZcoord() &&
		(pos.z - 40) < camera->getCameraZcoord())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int NumPad::getfirstrotate()
{
	return firstrotate;
}

int NumPad::getsecondrotate()
{
	return secondrotate;
}

int NumPad::getthirdrotate()
{
	return thirdrotate;
}

int NumPad::getfourthrotate()
{
	return fourthrotate;
}

float NumPad::getarrowposition()
{
	return changearrow;
}

int NumPad::getdigit1()
{
	return digit1;
}

int NumPad::getdigit2()
{
	return digit2;
}

int NumPad::getdigit3()
{
	return digit3;
}

int NumPad::getdigit4()
{
	return digit4;
}