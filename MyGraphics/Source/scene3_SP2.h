/******************************************************************************/
/*!
\file       scene3_SP2.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Creating a clean scene so that my teammates can code in ease
Hopefully they don't mess it up
*/
/******************************************************************************/
#ifndef SCENE3_SP2_H_
#define SCENE3_SP2_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera3.h"
#include "MatrixStack.h"
#include <queue>

using std::queue;

/******************************************************************************/
/*!
Class scene3_SP2:
\brief
inheirited from Scene and made improvised to it.
To turn it into a game.
This is the Scenario 3.
*/
/******************************************************************************/
class scene3_SP2 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_LIGHTBALL,
        GEO_COMIC_TEXT,
        //skybox
        GEO_SPACE_SKYBOX,
        //skybox
        GEO_FLYINGVEHICLE,
        GEO_LIGHT_WRAP,
        GEO_LIGHT_END,
        GEO_ASTEROID,
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
        //2nd light bulb
        U_LIGHT1_POSITION,
        U_LIGHT1_COLOR,
        U_LIGHT1_POWER,
        U_LIGHT1_KC,
        U_LIGHT1_KL,
        U_LIGHT1_KQ,
        U_LIGHT1_TYPE,
        U_LIGHT1_SPOTDIRECTION,
        U_LIGHT1_COSCUTOFF,
        U_LIGHT1_COSINNER,
        U_LIGHT1_EXPONENT,
        //2nd light bulb
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
        U_TOTAL,
    };

public:
    scene3_SP2(float screenwidth, float screenheight);
    ~scene3_SP2();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    bool on_light;
    Light light[2];
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

    void RenderSkybox();
    void renderSpaceShip();

    //animating the spaceShip
    void animateSpaceShip(double dt);
    float jitteringShipY;
    bool toggleUp;
    float scaleShipZ;
    bool warppingOn;
    //animating the spaceShip

    //animating the SkyBox
    float scaleSkyBoxZ_;
    //animating the SkyBox

    //rendering of the warp
    void renderWarp();
    //rendering of the warp

    //animating of the warp
    void animateWarp(double dt);
    float warp_lightZ;
    double wait_on_white_screen;
    bool start_white_screen;
    float scaleLightEnd;
    //animating of the warp

    //logic for 2nd light bulb
    bool turn_on_2nd;
    //logic for 2nd light bulb

    //for the QTE
    queue<char> quickTimeEvent;
    void initQuickTimeEvent(const char* fileLocation);
    bool quickTimeEventFlag;
    void activateQTE(double& dt);
    void renderQTE();
    double quickTimer;
    double makingSureNoDoubleTap;
    void renderMeteorite();
    float moveAsteroidZ;
    //for the QTE
};


#endif // !SCENE3_SP2_H_
