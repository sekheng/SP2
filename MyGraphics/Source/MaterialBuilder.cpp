#include "MaterialBuilder.h"

Material MaterialBuilder::GenerateBlinn(float shininess, float ambient, float diffuse, float specular)
{
    Material material;

    material.kSpecular.Set(specular, specular, specular);
    material.kDiffuse.Set(diffuse, diffuse, diffuse);
    material.kAmbient.Set(ambient, ambient, ambient);
    material.kShininess = shininess;

    return material;
}

Material MaterialBuilder::GenerateLambert(float shininess, float ambient, float diffuse, float specular)
{
    Material material = GenerateBlinn(shininess, ambient, diffuse, specular);
    return material;
}

Material MaterialBuilder::GeneratePhong(float shininess, float ambient, float diffuse, float specular)
{
    Material material = GenerateBlinn(shininess, ambient, diffuse, specular);
    return material;
}