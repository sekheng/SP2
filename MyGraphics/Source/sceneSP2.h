/******************************************************************************/
/*!
\file       sceneSP2.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Creating a clean scene so that my teammates can code in ease
Hopefully they don't mess it up
*/
/******************************************************************************/
#ifndef SCENE_SP2_H_
#define SCENE_SP2_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera3.h"
#include "MatrixStack.h"
#include "removeMonospace.h"

/******************************************************************************/
/*!
Class sceneSP2:
\brief
inheirited from Scene and made improvised to it. 
To turn it into a game.
*/
/******************************************************************************/
class sceneSP2 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_LIGHTBALL,
        GEO_COMIC_TEXT,

        
        //skybox
        GEO_SPACE_SKYBOX,
        //skybox
        //User Interface
        GEO_UI,
        //User Interface
        //Space ground mesh
        GEO_SPACE_GROUNDMESH,
        //Space ground mesh
		GEO_BOX,

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
    sceneSP2(float screenwidth, float screenheight);
    ~sceneSP2();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    bool on_light;
    Light light[1];
    float LSPEED = 10.f;
    void renderMesh(Mesh *mesh, bool enableLight);
    void RenderSkybox();
    void Rendergroundmesh();
    void sceneSP2::RenderUserInterface(Mesh* mesh, float size, float x, float y);
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
    removeMonospace forComicSans;
};

#endif