/******************************************************************************/
/*!
\file       LoadingScreen.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
The Loading Screen
*/
/******************************************************************************/
#ifndef LOADINGSCREEN_H_
#define LOADINGSCREEN_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera3.h"
#include "MatrixStack.h"

/******************************************************************************/
/*!
Class LoadingScreen:
\brief
Just Rendering of the Loading Screen to ease the boredom of player when initialising other scenes
*/
/******************************************************************************/
class LoadingScreen : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_LIGHTBALL,
        GEO_COMIC_TEXT,
        GEO_LOADING_SCREEN_TITLE,
        GEO_LOADING_DOGE,
        GEO_LOADING_BREATHING_CAT,
        NUM_GEOMETRY,
    };

    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHTENABLED,
        U_LIGHT0_TYPE,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_COSCUTOFF,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
        U_TOTAL,
    };

public:
    LoadingScreen(float screenwidth, float screenheight);
    ~LoadingScreen();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

private:
    bool on_light;
    Light light[1];
    float LSPEED = 10.f;
    void renderMesh(Mesh *mesh, bool enableLight);
    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    Camera3 camera;

    MS modelStack, viewStack, projectionStack;

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y);

    double framePerSecond;
    float screenWidth, screenHeight;

    vector<string> loadingHints;
    void initLoadingHints(const char *fileName);
};


#endif // !SCENE3_SP2_H_
