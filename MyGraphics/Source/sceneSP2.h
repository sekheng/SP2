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
#include "NPC.h"
#include "StationScene.h"
#include "Quest.h"
#include "SekHeng.h"
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

		//SpaceShuttle
		GEO_SPACESHUTTLE,

        //NPC
        GEO_NPC1,
        GEO_NPC_QUEST1,
        GEO_NPC_QUEST2,
        GEO_NPC_QUEST3,
        GEO_NPC_QUEST4,
        //NPC

        GEO_INVIS_CURSOR,

        //better UI by Sek Heng
        GEO_TEXT_BOX,
        //better UI by Sek Heng

		//chunfei's NPC
		GEO_ROBOTHEAD,
		GEO_ROBOTBODY,
		GEO_SWORD,

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

    //render quest items
    void RenderScrewDriver();
    void RenderHammer();
    void RenderContainer();
    void RenderGasoline();
    //render quest items
	void RenderSpaceShuttle();

	void RenderStation();
	void RenderEmptyBox();

    void RenderNPC();

    void RenderQuestObjects();

    void sceneSP2::RenderUserInterface(Mesh* mesh, float size, float x, float y);
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

	StationScene door;
	float doorSpeed;

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY);


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
    //logic of teleporter
    void teleport();
    //logic of teleporter

	float headrotating;
	bool headrotate;
	void renderChunFei();
	void headanimation(double dt);
	void renderNPC3();
};


#endif