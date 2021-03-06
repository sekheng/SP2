/******************************************************************************/
/*!
\file       sceneSP2.h
\author  Lee Sek Heng, Seetoo Victor, Lim Guan Hui, Li Chun Fei
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
#include "NPC.h"
#include "StationScene.h"
#include "Quest.h"
#include "SekHeng.h"
#include "scene2_minigame.h"

/******************************************************************************/
/*!
Class sceneSP2:
\brief
inheirited from Scene and made improvised to it. 
To turn it into a game.
This is Scenario 1
*/
/******************************************************************************/
class sceneSP2 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_LIGHTBALL,
        GEO_COMIC_TEXT,

		GEO_LANDVEHICLE,
		GEO_FLYINGVEHICLE,


        //environment**********************************************/
        GEO_SPACE_SKYBOX,
        GEO_SPACE_GROUNDMESH,
        GEO_SPACE_WALL,
        //environment**********************************************/

		//cryostasis
		GEO_CRYOSTASIS,
        
        //User Interface
        GEO_UI,
        //User Interface

        //quest items
        GEO_SCREWDRIVER,
        GEO_CONTAINER,
        GEO_GASOLINE,
        GEO_HAMMER,
        //quest items



		//SpaceStation
		GEO_STATION,
		//Chair
		GEO_CHAIR,
		//Table
		GEO_TABLE,
		//Box
		GEO_BOX,
		//Door
		GEO_DOOR,
		//KeyCard
		GEO_KEYCARD,
		//Teleporter
		GEO_TELEPORTER,
        GEO_PARTICLE_LIGHT,
        GEO_PARTICLE_CUBE,
        //Teleporter
        //building
		GEO_BUILDINGRED,
		GEO_BUILDINGGREEN,
		GEO_BUILDINGBLUE,
		//SpaceShuttle
		GEO_SPACESHUTTLE,
		//light button
		GEO_BUTTON,
		//Barrel
		GEO_BARREL,

        //NPC
        GEO_NPC1,
        GEO_NPC_QUEST1,
        GEO_NPC_QUEST2,
        //no one is using it!!!
        //GEO_NPC_QUEST3,
        //GEO_NPC_QUEST4,
        //NPC

        GEO_INVIS_CURSOR,

        //better UI by Sek Heng
        GEO_TEXT_BOX,
        //better UI by Sek Heng

		//chunfei's NPC
		GEO_ROBOTHEAD,
		GEO_ROBOTBODY,
		GEO_SWORD,

        GEO_TYRE,

        //minigame
        GEO_MINIGAME_PIECE_1,
        GEO_MINIGAME_PIECE_2,
        GEO_MINIGAME_PIECE_3,
        GEO_MINIGAME_PIECE_4,
        GEO_MINIGAME_PIECE_5,
        GEO_MINIGAME_PIECE_6,
        GEO_MINIGAME_PIECE_7,
        GEO_MINIGAME_PIECE_8,
        GEO_MINIGAME_PIECE_9,
        GEO_MINIGAME_SELECTOR,

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
		U_NUMLIGHTS2,
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
	void reset();
private:
    bool on_light;
    Light light[2];
    float LSPEED = 10.f;
    void renderMesh(Mesh *mesh, bool enableLight);
    void RenderSkybox();
    void Rendergroundmesh();

    //render quest items
    void RenderScrewDriver();
    void RenderHammer();
    void RenderContainer();
    void RenderGasoline();
    //render quest items
	void RenderSpaceShuttle();
	void RenderStation();
    void RenderNPC();
    void RenderQuestObjects();
	void RenderBarrel();

    void sceneSP2::RenderUserInterface(Mesh* mesh, float size, float x, float y);

    //minigame functions
    void RenderMinigamePieces();
    void RenderMinigameOnScreen(Mesh* mesh, float size, float x, float y, float rotate_x);
    void RenderMinigameSelectorOnScreen(Mesh* mesh, float size, float x, float y, float rotate_x);


    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    Camera3 camera;

    MS modelStack, viewStack, projectionStack;

    //NPC objects
    NPC npc1;//example
    NPC QUEST1;
    NPC QUEST2;
    NPC QUEST3;
    NPC QUEST4;

    //Quest objects
    Quest test_quest;//example
    Quest One;
    Quest Two;
    Quest Three;
    Quest Four;

	//room interaction
	StationScene door;
	float lightSwitch;

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY);
    void QuestCompleteCheck();
    void RenderStuffOnScreen(Mesh* mesh, string direction, float size, float x, float y, float z, float rotate_x, float rotate_y, float rotate_z);
    void RenderTutorialScreen();
    double framePerSecond;
    float screenWidth, screenHeight;

    //Creating the player who gives the last quest
    SekHeng sek_heng_;
    void renderingSekHeng();
    //Creating the player who gives the last quest

    //making dialogue box easier for use
    void renderDialogueBox(const string& name, const string& dialogue);
    //making dialogue box easier for use

    //rendering the teleporter
    void Renderteleporter();
    //rendering the teleporter

	float headrotating;
	bool headrotate;
	void renderChunFei();
	void headanimation(double dt);
	void renderNPC3();
	//render building
	void RenderBuilding();

    void populateArea();

    //quest flow
    short quest_stage;
    bool Quest1_finished;
    bool Quest2_finished;
    bool Quest3_finished;
    bool Quest4_finished;

    //animating teleportation
    void animateTeleporting(double& dt);
    void animateTeleportation(double& dt);
    //logic of teleporter
    bool teleport();
    float teleportCoordY;
    bool startTeleporting;
    //logic of teleporter
    //animating teleportation

    //particle effect handler
    vector<objectsForDisplay> particleHandlers;
    //particle effect handler

    //music updates
    double musicTimeDelay;
    //music updates

    //show tutorial screen
    bool tutorialscreen;

    //minigame object
    minigame MiniGame;
};


#endif