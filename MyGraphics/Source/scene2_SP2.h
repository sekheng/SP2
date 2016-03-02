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
#include "rot_civ.h"
#include "NumPad.h"
#include "creditScene.h"
#include "NPC.h"

/******************************************************************************/
/*!
Class scene2_SP2:
\brief
inheirited from Scene and made improvised to it.
To turn it into a game.
This is Scenario 3
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
		//vault
        GEO_VAULTCUBE,
		GEO_VAULTWHEEL,
		GEO_VAULTSTICK,
		GEO_VAULTDOOR,
		//numpad
		GEO_NUMPAD,
		GEO_NUMROLL,
		GEO_ARROW,

		//satellite
		GEO_SATELLITEHEAD,
		GEO_SATELLITEBODY,

		//diamond
		GEO_BIGDIAMOND,
		GEO_SMALLDIAMOND,

		GEO_BIGDIAMOND2,
		GEO_SMALLDIAMOND2,

		//NPC
		GEO_NPCUPPER,
		GEO_NPCLOWER,

		//asteroid
		GEO_ASTEROID,
		GEO_ASTEROID2,

		//npcrobot
		GEO_NPCROBOT,

        //environment************************************************************//
        GEO_PLANET_SKYBOX,
        GEO_PLANET_GROUND,
        //environment************************************************************//

        //User Interface
        GEO_UI,
        //User Interface

        GEO_BOXES,
		GEO_NORMALBOXES,

        //DeadPOOL
        GEO_DEADPOOL,
        //DeadPOOL

        //text box
        GEO_TEXT_BOX,
        //text box

        //ending screen
        GEO_ENDING_SCREEN,
        //ending screen

       

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
	bool satelliterotate;
	bool bigdiamondtranslate;
	bool bigdiamondrotate;
	bool smalldiamondtranslate;
	bool smalldiamondrotate;
	bool NPCrotate;
	bool NPCrotate2;
	bool NPCrotate3;
	bool boxesappear;
	bool boxesappear2;
	bool boxesappear3;
	bool boxestransfer;
	bool change;
	bool change2;
	bool change3;	
	
    float LSPEED = 10.f;
	float wheelturning;
	float stickpushing;
	float dooropening;
	float satelliterotating;
	float bigdiamondtranslating;
	float bigdiamondrotating;
	float smalldiamondtranslating;
	float smalldiamondrotating;
	float NPCrotating;
	float NPCrotating2;
	float NPCrotating3;
	float boxesrotating;
	float boxesrotating2;
	float boxesrotating3;
	
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
	void RenderSatellite();
	void RenderDiamond();
	void RenderNPC();
	void RenderBoxes();
	void RenderPlane();
	void RenderAsteroid();
	
	//animation function
	void VaultAnimation(double dt);
	void SatelliteAnimation(double dt);
	void diamondAnimation(double dt);
	void NPCAnimation(double dt);
	void BoxesAnimation(double dt);
	
    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

	Light light[2];
    Camera3 camera;
	NumPad Numpad;
	NPC robotNPC1;
	NPC robotNPC2;
	NPC robotNPC3;
	//NPC NumpadNPC;
	
    MS modelStack, viewStack, projectionStack;

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderNumPadOnScreen(Mesh* mesh, float size, float x, float y, float z, float rotate, float rotatex, float rotatey);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY);
    void RenderUserInterface(Mesh* mesh, float size, float x, float y);

    double framePerSecond;
    float screenWidth, screenHeight;

    //Adding rot civ into the game
    rot_civ Rot_Civ_;
    //Adding rot civ into the game
    //rendering the DeadPool
    void renderDeadPool();
    //rendering the DeadPool

    //rendering dialogue box
    void renderDialogueBox(const string& name, const string& dialogue);
    //rendering dialogue box

    //Beginning cinematic
    bool beginEnding;
    bool beginIamYourFather;
    void Ending(double& dt);
    double endingTime;
    float moveToDeadPoolZ;
    float sizeofEndingScreen;
    void renderEndingScreen();

    //credits
    creditScene creditRolling;
    void rollingCredits();
    //credits
    //Beginning cinematic

    //For 3D effects of the music
    double update3DPos;
    //For 3D effects of the music


    
    //displaying instructions
    void renderIntruction();
    double PreventSpammingInstruction;
    bool displayInstruction;
    //displaying instructions
};

#endif