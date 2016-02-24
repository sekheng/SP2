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
	check = open = close = render = false;
	firstrotate = secondrotate = thirdrotate = fourthrotate = arrow = 0.0f;
	time = 0.0;
	time_delay = 0.2f;
	changearrow = 19.5;
	digit1 = digit2 = digit3 = digit4 = 0;
	camera = &cameraDub;
	pos = origPos;
}

void NumPad::Update(double dt)
{

	if (interaction() == true)
	{
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			if (time > time_delay)//0.2second before next key press
			{
				time = 0;
				changearrow += 15; //arrow position move to first digit 
				if (changearrow > 64.5)//arrow position more than fourth digit, move back to first digit
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
			check = true; //verify the input password with the correct paswword
		}
		else
		{
			check = false;
		}
		if (Application::IsKeyPressed('C'))
		{
			open = true; //open the password input userinterface
		}
		if (Application::IsKeyPressed('X'))
		{
			open = false; //close the password input userinterface
		}
	}
	
	
	time += dt;
}

bool NumPad::interactiontext() // if player inside interaction area, "Press 'C' to interact" text will appear
{
	if (interaction() == true )
	{
		return true;
	}
	return false;
}

bool NumPad::NumpadRenderOnScreen()
{
	if (interaction() && open == true)
	{
		return true;
	}
	else if (!interaction() || open ==false)
	{
		return false;
	}
	return false;
}

void NumPad::NumpadProgram(double dt)
{
	if (interactiontext() == true && interaction()==true && NumpadRenderOnScreen())//make sure player inside the interaction area 
	{
		if (arrow == 0)// arrow pointing first digit
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				if (time > time_delay) 
				{
					time = 0;
					//firstrotate += 200 * (int)(dt);
					firstrotate += 36; //rotate 36degree (change to next number)
					/*if (firstrotate<firstrotate+36)
					{
						firstrotate += 100 * (dt);
					}
					static_cast<int>(firstrotate);*/
					digit1++;
					if (digit1 > 9) 
					{
						digit1 = 0;
					}
				}
			}
			else if (Application::IsKeyPressed(VK_DOWN))
			{
				if (time > time_delay)
				{
					time = 0;
					firstrotate -= 36;
					digit1--;
					if (digit1 < 0)
					{
						digit1 = 9;
					}
				}
			}

		}

		if (arrow == 1)// arrow pointing second digit
		{
			if (Application::IsKeyPressed(VK_UP))
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
				}
			}
			else if (Application::IsKeyPressed(VK_DOWN))
			{
				if (time > time_delay)
				{
					time = 0;
					secondrotate -= 36;
					digit2--;
					if (digit2 < 0)
					{
						digit2 = 9;
					}
				}
			}
		}
		
		if (arrow == 2)// arrow pointing third digit
		{
			if (Application::IsKeyPressed(VK_UP))
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
				}
			}
			else if (Application::IsKeyPressed(VK_DOWN))
			{
				if (time > time_delay)
				{
					time = 0;
					thirdrotate -= 36;
					digit3--;
					if (digit3 < 0)
					{
						digit3 = 9;
					}
				}
			}
		}
		
		if (arrow == 3)// arrow pointing fourth digit
		{
			if (Application::IsKeyPressed(VK_UP))
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
				}
			}
			else if (Application::IsKeyPressed(VK_DOWN))
			{
				if (time > time_delay)
				{
					time = 0;
					fourthrotate -= 36;
					digit4--;
					if (digit4 < 0)
					{
						digit4 = 9;
					}
				}
			}
		}
	}
}

bool NumPad::NumpadVerify()
{
	if (check==true)
	{
		if (digit1 == 9 && digit2 == 6 && digit3 == 6 && digit4 == 9) // verify 4 input digits with the correct password 
		{
			return true;
		}
	}
	return false;
}

bool NumPad::displayerror()
{
	if (interaction() && check==true) 
	{
		if (!NumpadVerify()) //if input != correct password, display "Try Again!"
		{
			return true;
		}
		else if (NumpadVerify())
		{
			return false;
		}
	}
	return false;
	
}

bool NumPad::interaction() // interaction area 
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

float NumPad::getfirstrotate()
{
	return firstrotate;
}

float NumPad::getsecondrotate()
{
	return secondrotate;
}

float NumPad::getthirdrotate()
{
	return thirdrotate;
}

float NumPad::getfourthrotate()
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