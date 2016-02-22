/******************************************************************************/
/*!
\file       scene2_SP2.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Creating a clean scene so that my teammates can code in ease
Hopefully they don't mess it up
This is for landing on the vault
*/
/******************************************************************************/
#ifndef SCENE2_SP2_H_
#define SCENE2_SP2_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "MatrixStack.h"
#include "removeMonospace.h"
#include "rot_civ.h"

/******************************************************************************/
/*!
Class scene2_SP2:
\brief
inheirited from Scene and made improvised to it.
To turn it into a game.
*/
/******************************************************************************/
class scene2_SP2 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_LIGHTBALL,
        GEO_COMIC_TEXT,

        GEO_LANDVEHICLE,
        GEO_FLYINGVEHICLE,
        GEO_ROBOT,
        GEO_SPACESHUTTLE,
        GEO_VAULTCUBE,
		GEO_VAULTWHEEL,
		GEO_VAULTSTICK,
		GEO_VAULTDOOR,
		GEO_NUMPAD,
		GEO_NUMROLL1,
		GEO_NUMROLL2,
		GEO_NUMROLL3,
		GEO_NUMROLL4,
		GEO_ARROW,

        //environment************************************************************//
        GEO_PLANET_SKYBOX,
        GEO_PLANET_GROUND,
        //environment************************************************************//

        //User Interface
        GEO_UI,
        //User Interface

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
    scene2_SP2(float screenwidth, float screenheight);
    ~scene2_SP2();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:

    bool on_light;
	bool wheelturn;
	bool stickpush;
	bool dooropen;
	bool text;
	bool screentext;
	bool firstroll;
	bool secondroll;
	bool thirdroll;
	bool fourthroll;
	bool check;
	bool rendererror;
    Light light[1];
    float LSPEED = 10.f;
	float wheelturning;
	float stickpushing;
	float dooropening;
	float firstrotate;
	float secondrotate;
	float thirdrotate;
	float fourthrotate;
	float time_delay;
	float changearrow;
	float arrow;
	
	int digit1;
	int digit2;
	int digit3;
	int digit4;
	double time;

	char answer[5];
	char input[5];

	//renderobj function
    void renderMesh(Mesh *mesh, bool enableLight);
    void RenderSkybox();
    void RenderRobot();
    void RenderFlyingVehicle();
    void RenderLandingVehicle();
    void RenderSpaceShuttle();
    void RenderVault();
	void RenderNumpad();
	void RenderNumroll();
	void RenderMenu();
	void RenderArrow();
	void PasswordVerify();
	void CorrectPassword();
	//animation function
	void VaultAnimation(double dt);
	void NumpadAnimation(double dt);
	void NumpadVerify();

    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    Camera3 camera;

    MS modelStack, viewStack, projectionStack;

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderNumPadOnScreen(Mesh* mesh, float size, float x, float y, float z, float rotate, float rotatex, float rotatey);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y);
    void RenderUserInterface(Mesh* mesh, float size, float x, float y);


    double framePerSecond;
    float screenWidth, screenHeight;

    //Adding rot civ into the game
    rot_civ Rot_Civ_;
    //Adding rot civ into the game
};

#endif