/******************************************************************************/
/*!
\file       MaterialBuilder.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
A factory to create different types of materials
*/
/******************************************************************************/
#ifndef MATERIAL_BUILDER_H
#define MATERIAL_BUILDER_H

#include "Material.h"

/******************************************************************************/
/*!
Class MaterialBuilder:
\brief	Provides methods to generate different materials
*/
/******************************************************************************/

class MaterialBuilder
{
public:
    static Material GenerateBlinn(float shininess = 1.f,float ambient = 0.8, float diffuse = 0.8f, float specular = 0.5f);
    static Material GenerateLambert(float shininess = 1.f, float ambient = 0.8f, float diffuse = 0.8f, float specular = 0.2f);
    static Material GeneratePhong(float shininess = 1.f, float ambient = 0.8f, float diffuse = 0.8f, float specular = 0.9f);
};

#endif