#include "MaterialBuilder.h"

/******************************************************************************/
/*!
\brief -
generate similar properties to Blinn

\param shininess - how bright will the object becomes
\param ambient - gradient of the object
\param diffuse - how the light diffuse on the object
\param specular - how spetacular the object will look like being shined upon

\return the material after it's properties have been set
*/
/******************************************************************************/
Material MaterialBuilder::GenerateBlinn(float shininess, float ambient, float diffuse, float specular)
{
    Material material;

    material.kSpecular.Set(specular, specular, specular);
    material.kDiffuse.Set(diffuse, diffuse, diffuse);
    material.kAmbient.Set(ambient, ambient, ambient);
    material.kShininess = shininess;

    return material;
}

/******************************************************************************/
/*!
\brief -
generate similar properties to Lambert

\param shininess - how bright will the object becomes
\param ambient - gradient of the object
\param diffuse - how the light diffuse on the object
\param specular - how spetacular the object will look like being shined upon

\return the material after it's properties have been set
*/
/******************************************************************************/
Material MaterialBuilder::GenerateLambert(float shininess, float ambient, float diffuse, float specular)
{
    Material material = GenerateBlinn(shininess, ambient, diffuse, specular);
    return material;
}

/******************************************************************************/
/*!
\brief -
generate similar properties to Phong

\param shininess - how bright will the object becomes
\param ambient - gradient of the object
\param diffuse - how the light diffuse on the object
\param specular - how spetacular the object will look like being shined upon

\return the material after it's properties have been set
*/
/******************************************************************************/
Material MaterialBuilder::GeneratePhong(float shininess, float ambient, float diffuse, float specular)
{
    Material material = GenerateBlinn(shininess, ambient, diffuse, specular);
    return material;
}