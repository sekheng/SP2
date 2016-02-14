/******************************************************************************/
/*!
\file       Scene.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief - 
Creating a pure virtual scenes
Taken from Mr Tang's framework
*/
/******************************************************************************/
#ifndef SCENE_H
#define SCENE_H

/******************************************************************************/
/*!
Class Scene:
\brief      
The basic functions of how Scene works. All scenes shall inheirit from this class
*/
/******************************************************************************/
class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif