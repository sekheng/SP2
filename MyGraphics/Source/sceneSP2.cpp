#include "GL\glew.h"
#include <sstream>

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "MaterialBuilder.h"
#include "Material.h"
#include "Light.h"
#include "Material.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <iomanip>


/******************************************************************************/
/*!
\brief - 
constructor with 2 arguments to store the width and height of the screen

\param screenwidth - width of the screen
\param screenheight - height of the screen
*/
/******************************************************************************/
sceneSP2::sceneSP2(float screenwidth, float screenheight)
    : screenWidth(screenwidth), screenHeight(screenheight)
{
}
/******************************************************************************/
/*!
\brief - destructor
*/
/******************************************************************************/
sceneSP2::~sceneSP2()
{
}
/******************************************************************************/
/*!
\brief - 
initializing whatever is needed for the scene
*/
/******************************************************************************/
void sceneSP2::Init()
{

    //// Init VBO here

    //// Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glEnable(GL_CULL_FACE);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Load vertex and fragment shaders
    m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
    m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
    m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
    m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
    m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
    m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
    m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
    m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
    m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
    m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
    m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
    m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
    m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
    m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
    m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
    m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
    m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    glUseProgram(m_programID);

    glUniform1i(m_parameters[U_NUMLIGHTS], 1);

    light[0].type = Light::LIGHT_DIRECTIONAL;
    light[0].position.Set(0, 70, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 1;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.01f;
    light[0].cosCutoff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
    light[0].exponent = 3.f;
    light[0].spotDirection.Set(0.f, 1.f, 0.f);

    glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
    glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
    glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

    //Initialize camera settings
    camera.Init("cameraDriven//scene1.txt");
	//camera.InitObjects("scenario1Driven//");
    camera.camType = Camera3::FIRST_PERSON;

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    meshList[GEO_COMIC_TEXT] = MeshBuilder::GenerateText("comic sans text", 16, 16);
    meshList[GEO_COMIC_TEXT]->textureID = LoadTGA("Image//comicSans.tga");

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light_ball", Color(1,1,1));

    /***************************************************************************/
    //environment
    /***************************************************************************/
    //skybox
    meshList[GEO_SPACE_SKYBOX] = MeshBuilder::GenerateOBJ("space skybox", "OBJ//Space_Skybox.obj");
    meshList[GEO_SPACE_SKYBOX]->textureID = LoadTGA("Image//skybox//Space_Skybox_UV.tga");
    //Space ground mesh
    meshList[GEO_SPACE_GROUNDMESH] = MeshBuilder::GenerateOBJ("Space ground mesh", "OBJ//Space_groundmesh.obj");
    meshList[GEO_SPACE_GROUNDMESH]->textureID = LoadTGA("Image//Space_groundmesh.tga");
    // meshList[GEO_SPACE_GROUNDMESH]->material = MaterialBuilder::GenerateBlinn();

    //space walls
    meshList[GEO_SPACE_WALL] = MeshBuilder::GenerateOBJ("Space wall", "OBJ//space_walls.obj");
    meshList[GEO_SPACE_WALL]->textureID = LoadTGA("Image//space_station_wall.tga");



    //User Interface
    meshList[GEO_UI] = MeshBuilder::GenerateOBJ("User Interface", "OBJ//User_Interface.obj");
    meshList[GEO_UI]->textureID = LoadTGA("Image//UI_UV.tga");
    //User Interface
    
    //quest items
    meshList[GEO_SCREWDRIVER] = MeshBuilder::GenerateOBJ("screw driver", "OBJ//ScrewDriver.obj");
    meshList[GEO_SCREWDRIVER]->textureID = LoadTGA("Image//Screwdriver.tga");
    
    meshList[GEO_CONTAINER] = MeshBuilder::GenerateOBJ("container", "OBJ//Container.obj");
    meshList[GEO_CONTAINER]->textureID = LoadTGA("Image//Container.tga");
   
    meshList[GEO_GASOLINE] = MeshBuilder::GenerateOBJ("gasoline", "OBJ//Gasoline.obj");
    meshList[GEO_GASOLINE]->textureID = LoadTGA("Image//Gasoline.tga");
   
    meshList[GEO_HAMMER] = MeshBuilder::GenerateOBJ("hammer", "OBJ//Hammer.obj");
    meshList[GEO_HAMMER]->textureID = LoadTGA("Image//Hammer.tga");

    //quest items

	
	//SpaceStation
	meshList[GEO_STATION] = MeshBuilder::GenerateOBJ("Station", "OBJ//Station.obj");
	meshList[GEO_STATION]->textureID = LoadTGA("Image//Station.tga");
	meshList[GEO_STATION]->material = MaterialBuilder::GenerateLambert();
	//SpaceStationChair
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("Chair", "OBJ//Chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//Chair.tga");
	meshList[GEO_CHAIR]->material = MaterialBuilder::GenerateBlinn();
	//SpaceStationTable
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Table", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table.tga");
	meshList[GEO_TABLE]->material = MaterialBuilder::GenerateBlinn();

	//SpaceStationBox
	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("Box", "OBJ//Box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//Box.tga");
	meshList[GEO_BOX]->material = MaterialBuilder::GenerateBlinn();

	//SpaceStationBox
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//Door.tga");
	meshList[GEO_DOOR]->material = MaterialBuilder::GenerateLambert();

	//SpaceStationCryostasis
	meshList[GEO_CRYOSTASIS] = MeshBuilder::GenerateOBJ("Cryostasis", "OBJ//cryostasis.obj");
	meshList[GEO_CRYOSTASIS]->textureID = LoadTGA("Image//cryostasis.tga");
	meshList[GEO_CRYOSTASIS]->material = MaterialBuilder::GenerateLambert();
	//SpaceStationKeyCard
	meshList[GEO_KEYCARD] = MeshBuilder::GenerateOBJ("KeyCard", "OBJ//KeyCard.obj");
	meshList[GEO_KEYCARD]->textureID = LoadTGA("Image//KeyCard.tga");
	//SpaceShuttle
	meshList[GEO_SPACESHUTTLE] = MeshBuilder::GenerateOBJ("SpaceShuttle", "OBJ//FlyingVehicle.obj");
	meshList[GEO_SPACESHUTTLE]->textureID = LoadTGA("Image//FlyingVehicle.tga");
	meshList[GEO_SPACESHUTTLE]->material = MaterialBuilder::GenerateBlinn();

	//Teleporter
	meshList[GEO_TELEPORTER] = MeshBuilder::GenerateOBJ("Teleport", "OBJ//Teleporter.obj");
	meshList[GEO_TELEPORTER]->textureID = LoadTGA("Image//Teleporter.tga");
	meshList[GEO_TELEPORTER]->material = MaterialBuilder::GenerateBlinn();

    meshList[GEO_PARTICLE_LIGHT] = MeshBuilder::GenerateOBJ("particle light", "OBJ//Barrel.obj");
    meshList[GEO_PARTICLE_LIGHT]->textureID = LoadTGA("Image//particle_light.tga");
    meshList[GEO_PARTICLE_LIGHT]->material = MaterialBuilder::GenerateBlinn();

    meshList[GEO_PARTICLE_CUBE] = MeshBuilder::GenerateOBJ("particle cube", "OBJ//Box.obj");
    meshList[GEO_PARTICLE_CUBE]->textureID = LoadTGA("Image//particle_light.tga");
    meshList[GEO_PARTICLE_CUBE]->material = MaterialBuilder::GeneratePhong();
    //Teleporter

	//red building
	meshList[GEO_BUILDINGRED] = MeshBuilder::GenerateOBJ("BuildingRed", "OBJ//Building.obj");
	meshList[GEO_BUILDINGRED]->textureID = LoadTGA("Image//BuildingRed.tga");
	meshList[GEO_BUILDINGRED]->material = MaterialBuilder::GenerateBlinn();

	//green building
	meshList[GEO_BUILDINGGREEN] = MeshBuilder::GenerateOBJ("BuildingBlue", "OBJ//Building.obj");
	meshList[GEO_BUILDINGGREEN]->textureID = LoadTGA("Image//BuildingGreen.tga");
	meshList[GEO_BUILDINGGREEN]->material = MaterialBuilder::GenerateBlinn();

	//Blue building
	meshList[GEO_BUILDINGBLUE] = MeshBuilder::GenerateOBJ("BuildingGreen", "OBJ//Building.obj");
	meshList[GEO_BUILDINGBLUE]->textureID = LoadTGA("Image//BuildingBlue.tga");
	meshList[GEO_BUILDINGBLUE]->material = MaterialBuilder::GenerateBlinn();

	//Barrel
	meshList[GEO_BARREL] = MeshBuilder::GenerateOBJ("Barrel", "OBJ//Barrel.obj");
	meshList[GEO_BARREL]->textureID = LoadTGA("Image//Barrel.tga");
	meshList[GEO_BARREL]->material = MaterialBuilder::GenerateLambert();

	//land vehicle
	meshList[GEO_LANDVEHICLE] = MeshBuilder::GenerateOBJ("Vehicle", "OBJ//LandVehicle.obj");
	meshList[GEO_LANDVEHICLE]->textureID = LoadTGA("Image//LandVehicle.tga");
	meshList[GEO_LANDVEHICLE]->material = MaterialBuilder::GenerateLambert();

    //NPC
    meshList[GEO_NPC1] = MeshBuilder::GenerateOBJ("Najib", "OBJ//android.obj");
    meshList[GEO_NPC1]->textureID = LoadTGA("Image//android.tga");
    //NPC


    meshList[GEO_INVIS_CURSOR] = MeshBuilder::GenerateSphere("invisible cursor", Color(0.5, 0.5, 0.5));

    //text box
    meshList[GEO_TEXT_BOX] = MeshBuilder::GenerateQuad("text box", Color(1, 1, 1));
    meshList[GEO_TEXT_BOX]->textureID = LoadTGA("Image//textbox.tga");
    //text box

	//chunfei npc
	meshList[GEO_ROBOTHEAD] = MeshBuilder::GenerateOBJ("robothead", "OBJ//robothead.obj");
	meshList[GEO_ROBOTHEAD]->textureID = LoadTGA("Image//robot.tga");

	meshList[GEO_ROBOTBODY] = MeshBuilder::GenerateOBJ("robotbody", "OBJ//robotbody.obj");
	meshList[GEO_ROBOTBODY]->textureID = LoadTGA("Image//robot.tga");

	meshList[GEO_SWORD] = MeshBuilder::GenerateOBJ("sword", "OBJ//sword.obj");
	meshList[GEO_SWORD]->textureID = LoadTGA("Image//sword.tga");

    meshList[GEO_TYRE] = MeshBuilder::GenerateOBJ("tyre", "OBJ//Tire.obj");


    on_light = true;

    //meshList[]
    Mtx44 projection;
    projection.SetToPerspective(60.f, static_cast<float>(screenWidth / screenHeight), 0.1f, 20000.f);
    projectionStack.LoadMatrix(projection);

    //initialise camera_position_x and z;
    framePerSecond = 0;
    camera.cursorCoordX = screenWidth / 2;
    camera.cursorCoordY = screenHeight / 2;

	door.Init("Sek heng", Vector3(-30, 0, 40), camera, 5, 5);
	door.getQuestStage();
	doorSpeed = 0;
	

	camera.InitObjects("scenario1Driven//objects.txt");

    //initialise npc
    QUEST1.Init("First NPC",4, Vector3(-270, 0, 194), 5, 5, camera, "NPC data//NPC_1.txt");
    //initialise quest
    One.Init("First quest", camera, 2, Vector3(-270, 0, 164),5, Vector3(-270 ,0, 134),5);

	QUEST2.Init("Sec NPC",4, Vector3(175, 0, 175), 5, 5, camera, "NPC data//NPC_2.txt");
	Two.Init("Sec quest", camera, 1, Vector3(185, 0, 185), 5, Vector3(0, 0, 0), 5);

    //Sek Heng's stuff and initialization
    sek_heng_.init("sekheng//sek_heng_stuff.txt");
    sek_heng_.initDialogues("sekheng//dialogues.txt", camera);
    //Sek Heng's stuff and initialization

	//chunfei's robotnpc

	//initialise npc3
	//QUEST3.Init("Chunfei NPChead", Vector3(0, 5.5, 250), 2, 2, camera, "NPC data//NPC_3.txt");
	QUEST3.Init("Chunfei NPCbody", 5,Vector3(0, 0, 250), 5, 5, camera, "NPC data//NPC_3.txt");
	//initialise quest3
	Three.Init("Third quest", camera, 1, Vector3(-300, 0, 275), 5, Vector3(0, 0, 0), 0); 

	/*for (auto it : camera.storage_of_objects) {
		if (it.getName() == "robotbody") {
			robotNPC.Init(camera, Vector3(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ()));
			break;
		}
	}*/
	headrotate = false;
	headrotating = 0;
	//chunfei's stuff

    slowtxt = 0;

    quest_stage = 0;

    Quest1_finished = false;
    Quest2_finished = false;
    Quest3_finished = false;
    Quest4_finished = false;

    //animating particle cube
    for (vector<objectsForDisplay>::iterator it = camera.storage_of_objects.begin(); it != camera.storage_of_objects.end(); ++it) {
        if ((*it).getName() == "ParticleCube1" ||
            (*it).getName() == "ParticleCube2" ||
            (*it).getName() == "ParticleCube3" ||
            (*it).getName() == "ParticleCube4" ||
            (*it).getName() == "ParticleCube5" ||
            (*it).getName() == "ParticleCube6" ||
            (*it).getName() == "ParticleCube7" ||
            (*it).getName() == "ParticleCube8" ||
            (*it).getName() == "ParticleCube9" ||
            (*it).getName() == "ParticleCube10") {
            (*it).objectPos.x = Math::RandFloatMinMax(-3, 3);
            (*it).objectPos.z = Math::RandFloatMinMax(-3, 3);
        }
    }
    //animating particle cube
}

/******************************************************************************/
/*!
\brief - 
where the logic of the game is, and update

\param dt - time frame
*/
/******************************************************************************/
void sceneSP2::Update(double dt)
{
    camera.Update(dt);
    framePerSecond = 1 / dt;
    npc1.update(dt);
    //update for quest
    QUEST1.update(dt);
    // update for npc
    One.check_quest(QUEST1.quest_given());
    One.Update(dt);

	QUEST2.update(dt);
	Two.check_quest(QUEST2.quest_given());
	Two.Update(dt);

	QUEST3.update(dt);
	Three.check_quest(QUEST3.quest_given());
	Three.Update(dt);
	headanimation(dt);

    QuestCompleteCheck();

    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    //transit scene
    if (Application::IsKeyPressed(VK_NUMPAD2)) {
        Application::changeIntoScenario2();
    }
    if (Application::IsKeyPressed(VK_NUMPAD3)) {
        Application::changeIntoScenario3();
    }
    //transit scene

	if (door.openSasame() == 2)
	{
		for (vector<objectsForDisplay>::iterator it = camera.storage_of_objects.begin(); it != camera.storage_of_objects.end(); ++it) {
			if ((*it).getName() == "Door")
			{
				(*it).objectPos.x += (float)(LSPEED *dt) * 10;
				if ((*it).objectPos.x  > -242)
				{
					(*it).objectPos.x = -242;
				}
				break;
			}
		}
	}

    //Sek Heng's stuff
    if (quest_stage == 4 && sek_heng_.SekHengSayIsOk() == false) {
        sek_heng_.activateQuest();
    }
    if (Application::IsKeyPressed('9')) {
        sek_heng_.FinishedQuest();
    }
    sek_heng_.Update(dt);
    //Sek Heng's stuff

    //just putting the teleport stuff in here
    if (Application::IsKeyPressed('E') && sek_heng_.SekHengSayIsOk()) {
        teleport();
    }
    //just putting the teleport stuff in here

    if (QUEST1.interaction())
    {
        TextSlowDown(dt);
    }
    else
    {
        slowtxt = 0;
    }
	
    //animating particle cube
    for (vector<objectsForDisplay>::iterator it = camera.storage_of_objects.begin(); it != camera.storage_of_objects.end(); ++it) {
        if ((*it).getName() == "ParticleCube1" ||
            (*it).getName() == "ParticleCube2" ||
            (*it).getName() == "ParticleCube3" ||
            (*it).getName() == "ParticleCube4" || 
            (*it).getName() == "ParticleCube5" || 
            (*it).getName() == "ParticleCube6" || 
            (*it).getName() == "ParticleCube7" || 
            (*it).getName() == "ParticleCube8" || 
            (*it).getName() == "ParticleCube9" || 
            (*it).getName() == "ParticleCube10") {
            if ((*it).objectPos.y < 40) {
                (*it).objectPos.y += 3 * (float)(dt);
            }
            else {
                (*it).objectPos.y = (*it).originalPos.y;
                (*it).objectPos.x = Math::RandFloatMinMax(-3, 3);
                (*it).objectPos.z = Math::RandFloatMinMax(-3, 3);
            }
        }
    }
    //animating particle cube
}

/******************************************************************************/
/*!
\brief - rendering of the meshes

\param mesh - the specific mesh
\param enableLight - to enable lighting on the object
*/
/******************************************************************************/
void sceneSP2::renderMesh(Mesh *mesh, bool enableLight)
{
    Mtx44 MVP, modelView, modelView_inverse_transpose;
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    modelView = viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

    if (enableLight)
    {
        glUniform1i(m_parameters[U_LIGHTENABLED], 1);
        modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
        glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
        //load material
        glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
        glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
        glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
        glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
    }
    else
    {
        glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    }

    if (mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }
    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }
    mesh->Render(); //this line should only be called once 
    if (mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


void sceneSP2::RenderStation()
{

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Station") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(20, 10, 10);
			renderMesh(meshList[GEO_STATION], true);
			modelStack.PopMatrix();
			break;
		}
	}

	//Table and chair set 1
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Chair1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(1.5, 1.5, 1.5);
			renderMesh(meshList[GEO_CHAIR], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Chair2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1.5, 1.5, 1.5);
			renderMesh(meshList[GEO_CHAIR], true);
			modelStack.PopMatrix();
			break;
		}
	}
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Table1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_TABLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	//Table and chair set2 
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Chair3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(1.5, 1.5, 1.5);
			renderMesh(meshList[GEO_CHAIR], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Chair4") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1.5, 1.5, 1.5);
			renderMesh(meshList[GEO_CHAIR], true);
			modelStack.PopMatrix();
			break;
		}
	}


	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Table2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_TABLE], true);
			modelStack.PopMatrix();
			break;
		}
	}


	//Table and chair set3 
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Chair5") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(1.5, 1.5, 1.5);
			renderMesh(meshList[GEO_CHAIR], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Chair6") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1.5, 1.5, 1.5);
			renderMesh(meshList[GEO_CHAIR], true);
			modelStack.PopMatrix();
			break;
		}
	}


	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Table3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_TABLE], true);
			modelStack.PopMatrix();
			break;
		}
	}


	//Box
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Box1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Box2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Box3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Box4") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Box5") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (float i = 0; i < 50; i += 5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-310, 0, 310 - i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], false);
		modelStack.PopMatrix();
	}

	for (float i = 0; i < 50; i += 10)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-255, 0, 270 + i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], false);
		modelStack.PopMatrix();
	}

	for (float i = 0; i < 50; i += 5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-255, 5, 268 + i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], false);
		modelStack.PopMatrix();
	}

	for (float i = 0; i < 55; i += 5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-250.f, 0.f, 265 + i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], false);
		modelStack.PopMatrix();
	}

	//Door

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Door") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 3, 6);
			renderMesh(meshList[GEO_DOOR], true);
			if (door.getQuestStage() == 1)
			{
				renderDialogueBox("Door","Press E to open door");
			}
			else if (door.getQuestStage() == 2)
			{
				renderDialogueBox("Door", "Find the 2 keycard to open");
			}
			else if (door.openSasame() == 1)
			{
				renderDialogueBox("Door", "Press E to unlock");
			}
			modelStack.PopMatrix();
			break;
		}
	}
	//modelStack.PushMatrix();
	//modelStack.Translate(-270 + doorSpeed , 0, 260);
	//modelStack.Scale(5, 3, 6);
	//renderMesh(meshList[GEO_DOOR], false);
	//modelStack.PopMatrix();

	if (door.getQuestStage() == 3)
	{
		if (door.getCard1() == 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-255, 0, 307);
			modelStack.Scale(1, 1, 1);
			renderMesh(meshList[GEO_KEYCARD], false);
			if (door.getCardText() == true)
			{
				renderDialogueBox("Door", "Press E to get card");
			}
			modelStack.PopMatrix();
		}
		if (door.getCard2() == 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-296, 0, 292);
			modelStack.Scale(1, 1, 1);
			renderMesh(meshList[GEO_KEYCARD], false);
			if (door.getCardText() == true)
			{
				renderDialogueBox("Door", "Press E to get card");
			}
			modelStack.PopMatrix();
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Cryostasis") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			renderMesh(meshList[GEO_CRYOSTASIS], true);
			modelStack.PopMatrix();
			break;
		}
	}

}

/******************************************************************************/
/*!
\brief - 
where the rendering of all the stuff we needed will be here
*/
/******************************************************************************/
void sceneSP2::Render()
{
    // Render VBO here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Temp variables
    Mtx44 translate, rotate, scale;
    Mtx44 MVP;

    //These will be replaced by matrix stack soon
    Mtx44 model;
    Mtx44 view;
    Mtx44 projection;

    //Set all matrices to identity
    translate.SetToIdentity();
    rotate.SetToIdentity();
    scale.SetToIdentity();
    model.SetToIdentity();

    //Set view matrix using camera settings
    viewStack.LoadIdentity();
    viewStack.LookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
        );

    //Set projection matrix to perspective mode
    projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane


    if (light[0].type == Light::LIGHT_DIRECTIONAL)
    {
        Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
    }
    else if (light[0].type == Light::LIGHT_SPOT)
    {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
        Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
        glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
    }
    else
    {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
    }

    if (on_light) {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
        modelStack.PushMatrix();
        modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
        modelStack.Scale(0.5f, 0.5f, 0.5f);
        renderMesh(meshList[GEO_LIGHTBALL], false);
        modelStack.PopMatrix();
    }

    renderMesh(meshList[GEO_AXES], false);

    //render skybox
    modelStack.PushMatrix();
    modelStack.Scale(300, 300, 300);
    RenderSkybox();
    modelStack.PopMatrix();
    //render skybox


   /* modelStack.PushMatrix();
    renderMesh(meshList[GEO_UI],false),
    modelStack.PopMatrix();*/

    //render ground mesh
    modelStack.PushMatrix();
    modelStack.Scale(19.9f, 1, 19.9f);
    Rendergroundmesh();
    
    modelStack.PopMatrix();
    //render ground mesh

    modelStack.PushMatrix();
    modelStack.Scale(19.9f, 19.9f, 19.9f);
    renderMesh(meshList[GEO_SPACE_WALL], false);
    modelStack.PopMatrix();


	//render Spaceship
	RenderSpaceShuttle();

	//render Building
	RenderBuilding();



    /*
    modelStack.PushMatrix();
    RenderScrewDriver();
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    RenderContainer();
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    RenderGasoline();
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    RenderHammer();
    modelStack.PopMatrix();
    */
    modelStack.PushMatrix();
    RenderNPC();
    modelStack.PopMatrix();
    modelStack.PushMatrix();
    RenderQuestObjects();
    modelStack.PopMatrix();

    //rendering teleporter box
    Renderteleporter();
    //rendering teleporter box

    //rendering Sek Heng
    renderingSekHeng();
    //rendering Sek Heng

	//render chunfei NPC
	renderChunFei();

    //****************************************************************************//
    //On screen objects
    //****************************************************************************//
    //modelStack.PushMatrix();
    ////scale, translate, rotate
    //modelStack.Scale(20, 20, 1);
    //RenderText(meshList[GEO_COMIC_TEXT], "Hello World", Color(0, 1, 0));
    //modelStack.PopMatrix();


    modelStack.PushMatrix();
    RenderUserInterface(meshList[GEO_UI], 1, 40, 40);
    modelStack.PopMatrix();

    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Hello Screen", Color(0, 1, 0), 4, 0.5, 1.5);

    modelStack.PushMatrix();
    
    RenderUserInterface(meshList[GEO_UI], 1, 40, 40);
    
    
    modelStack.PopMatrix();

	RenderEmptyBox();

	RenderStation();

    populateArea();

   /* modelStack.PushMatrix();
    modelStack.Translate(camera.getCrossHairX(), camera.getCrossHairY(), camera.getCrossHairZ());
    renderMesh(meshList[GEO_INVIS_CURSOR], false);
    modelStack.PopMatrix();*/

    //****************************************************************************//
    //On screen objects
    //****************************************************************************//
    
   // RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Hello Screen", Color(0, 1, 0), 4, 0.5f, 1.5f);
    std::stringstream ss;
    ss << "FPS : " << static_cast<int>(framePerSecond);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 1.8f, 1.25f, 16.5f);
    
    std::stringstream connectPosX;

    connectPosX << std::fixed << std::setprecision(2) << "X : " << camera.getCameraXcoord();
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosX.str(), Color(0, 1, 0), 1.8f, 1.5f, 21.2f);

    std::stringstream connectPosZ;
    connectPosZ << std::fixed << std::setprecision(2) << "Z : " << camera.getCameraZcoord();
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosZ.str(), Color(0, 1, 0), 1.8f, 1.5f, 19.f);

    std::stringstream connectPosY;
    connectPosY << std::fixed << std::setprecision(2) << "Y : " << camera.getCameraYcoord();
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosY.str(), Color(0, 1, 0), 1.8f, 1.5f, 15.f);
RenderStuffOnScreen(meshList[GEO_CONTAINER],3,3,3,0,0,0);

}


/******************************************************************************/
/*!
\brief - 
cleans up the scene
*/
/******************************************************************************/
void sceneSP2::Exit()
{
    _CrtDumpMemoryLeaks();
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}

/******************************************************************************/
/*!
\brief - 
rendering of the texts using quads

\param mesh - a pointer to the specific mesh
\param text - the text that needs to be rendered
\param color - the color of the text
*/
/******************************************************************************/
void sceneSP2::RenderText(Mesh* mesh, std::string text, Color color)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    glDisable(GL_DEPTH_TEST);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        mesh->Render((unsigned)text[i] * 6, 6);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
    glEnable(GL_DEPTH_TEST);
}

/******************************************************************************/
/*!
\brief -
rendering of the texts using quads on screen

\param mesh - a pointer to the specific mesh
\param text - the text that needs to be rendered
\param color - the color of the text
\param size - size of the text
\param x - x coordinate of the text
\param y - y coordinate of the text
*/
/******************************************************************************/
void sceneSP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    glDisable(GL_DEPTH_TEST);
    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack
    modelStack.Scale(size, size, size);
    modelStack.Translate(x, y, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        mesh->Render((unsigned)text[i] * 6, 6);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
    glEnable(GL_DEPTH_TEST);
    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}
void sceneSP2::RenderDelayedTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    glDisable(GL_DEPTH_TEST);
    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack
    modelStack.Scale(size, size, size);
    modelStack.Translate(x, y, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        //mesh->Render((unsigned)text[i] * 6, 6);
    }
    for (unsigned i = 0; i < text.length();)
    {
        if (slowtxt > 0.9)
        {
            slowtxt = 0;
            mesh->Render((unsigned)text[i] * 6, 6);
            ++i;
        }
        
    }


    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
    glEnable(GL_DEPTH_TEST);
    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}    
void sceneSP2::TextSlowDown(double dt)
{    
   slowtxt += dt;
}
void sceneSP2::RenderTheSlowTexT(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{

}
/******************************************************************************/
/*!
\brief -
rendering of image using quad on screen

\param mesh - a pointer to the specific mesh
\param text - the text that needs to be rendered
\param color - the color of the text
\param size - size of the text
\param x - x coordinate of the text
\param y - y coordinate of the text
*/
/******************************************************************************/
void sceneSP2::RenderImageOnScreen(Mesh* mesh, float size, float x, float y) {
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack

    modelStack.Translate(x, y, 0);
    modelStack.Scale(size, size, size);
    modelStack.Rotate(90, 1, 0, 0);
    renderMesh(mesh, false);

    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}

void sceneSP2::RenderSkybox()
{
    modelStack.PushMatrix();
    renderMesh(meshList[GEO_SPACE_SKYBOX], false);
    modelStack.PopMatrix();
    //float SCALE = 2000;
    //float TRANSLATE = SCALE / 2 - SCALE / 500;

    //modelStack.PushMatrix();
    ////Skybox Movement
    //modelStack.Translate(Position.x, 0, Position.z);
    ////ft
    //modelStack.PushMatrix();
    //modelStack.Translate(0, 0, -TRANSLATE);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Scale(SCALE, SCALE, SCALE);
    //renderMesh(meshList[GEO_FRONT], false);
    //modelStack.PopMatrix();
    ////bk
    //modelStack.PushMatrix();
    //modelStack.Translate(0, 0, TRANSLATE);
    //modelStack.Rotate(90, -1, 0, 0);
    //modelStack.Rotate(180, 0, 1, 0);
    //modelStack.Scale(SCALE, SCALE, SCALE);
    //renderMesh(meshList[GEO_BACK], false);
    //modelStack.PopMatrix();
    ////up
    //modelStack.PushMatrix();
    //modelStack.Translate(0, TRANSLATE, 0);
    //modelStack.Rotate(180, 1, 0, 0);
    //modelStack.Rotate(90, 0, 1, 0);
    //modelStack.Scale(SCALE, SCALE, SCALE);
    //renderMesh(meshList[GEO_UP], false);
    //modelStack.PopMatrix();
    ////bt
    //modelStack.PushMatrix();
    //modelStack.Translate(0, -TRANSLATE, 0);
    //modelStack.Scale(SCALE, SCALE, SCALE);
    //renderMesh(meshList[GEO_DOWN], false);
    //modelStack.PopMatrix();
    ////lf
    //modelStack.PushMatrix();
    //modelStack.Translate(-TRANSLATE, 0, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Rotate(90, 0, 0, -1);
    //modelStack.Scale(SCALE, SCALE, SCALE);
    //renderMesh(meshList[GEO_LEFT], false);
    //modelStack.PopMatrix();
    ////rt
    //modelStack.PushMatrix();
    //modelStack.Translate(TRANSLATE, 0, 0);
    //modelStack.Rotate(90, 1, 0, 0);
    //modelStack.Rotate(90, 0, 0, 1);
    //modelStack.Scale(SCALE, SCALE, SCALE);
    //renderMesh(meshList[GEO_RIGHT], false);
    //modelStack.PopMatrix();
    //modelStack.PopMatrix();
}

void sceneSP2::RenderUserInterface(Mesh* mesh, float size, float x, float y)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;
    
    
    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 80, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack

    modelStack.Translate(x, y, 0);
    modelStack.Scale(80, 80, 80);
    modelStack.Rotate(90, 0, -1, 0);
    
    renderMesh(mesh, false);
    
    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}
void sceneSP2::Rendergroundmesh()
{
    modelStack.PushMatrix();
    renderMesh(meshList[GEO_SPACE_GROUNDMESH], false);
    modelStack.PopMatrix();
}
/**********************************************************************************************************/
//render quest items
/**********************************************************************************************************/
void sceneSP2::RenderScrewDriver()
{
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);
    renderMesh(meshList[GEO_CONTAINER], false);
    modelStack.PopMatrix();
}
void sceneSP2::RenderHammer()
{
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -200);
    renderMesh(meshList[GEO_GASOLINE], false);
    modelStack.PopMatrix();
}
void sceneSP2::RenderContainer()
{
    modelStack.PushMatrix();
    modelStack.Translate(30, 0, 20);
    renderMesh(meshList[GEO_HAMMER], false);
    modelStack.PopMatrix();
}
void sceneSP2::RenderGasoline()
{
    modelStack.PushMatrix();
    modelStack.Translate(90, 0, -30);
    renderMesh(meshList[GEO_SCREWDRIVER], false);
    modelStack.PopMatrix();
}
/**********************************************************************************************************/
//render quest items
/**********************************************************************************************************/



void sceneSP2::RenderSpaceShuttle()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Spaceshuttle") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(30, 30, 30);
			renderMesh(meshList[GEO_SPACESHUTTLE], false);
			modelStack.PopMatrix();
			break;
		}
	}
}
void sceneSP2::RenderNPC()
{
    /*
    //example
    modelStack.PushMatrix();
    modelStack.Translate(npc1.NPC_getposition_x(), npc1.NPC_getposition_y(), npc1.NPC_getposition_z());
    //modelStack.Scale(3,3,3);
    renderMesh(meshList[GEO_NPC1], false);
    if (npc1.interaction() == true)
    {
        if (!Application::IsKeyPressed('E'))
        {
            RenderTextOnScreen(meshList[GEO_COMIC_TEXT], npc1.getDialogue(true), Color(0, 1, 0), 3, 10, 10);
        }
        else
        {
            RenderTextOnScreen(meshList[GEO_COMIC_TEXT], npc1.getDialogue(false), Color(0, 1, 0), 3, 10, 10);
        }
    }
    modelStack.PopMatrix();
    */
    
    modelStack.PushMatrix();
    modelStack.Translate(QUEST1.NPC_getposition_x(), QUEST1.NPC_getposition_y(), QUEST1.NPC_getposition_z());
    renderMesh(meshList[GEO_NPC1], true);
    if (quest_stage >= 0)
    {
        if (QUEST1.interaction() == true && One.stage() < 4)
        {

            if (!Application::IsKeyPressed('E'))
            {
                renderDialogueBox("Guan Hui", QUEST1.getDialogue(true));
                //RenderDelayedTextOnScreen(meshList[GEO_COMIC_TEXT], QUEST1.getDialogue(true), Color(0, 1, 0), 3, 10, 10);

            }
            else
            {
                renderDialogueBox("Guan Hui", QUEST1.getDialogue(false));
            }
        }
        if (QUEST1.interaction() == true && One.stage() == 4)
        {
            renderDialogueBox("Guan Hui", QUEST1.quest_complete());
            Quest1_finished = true;
        }
        
    }
    modelStack.PopMatrix();
    
    modelStack.PushMatrix();
    modelStack.Translate(QUEST2.NPC_getposition_x(), QUEST2.NPC_getposition_y(), QUEST2.NPC_getposition_z());
    renderMesh(meshList[GEO_NPC1], true);
    if (quest_stage >= 2)
    {
        if (QUEST2.interaction() == true && Two.stage() < 4)
        {
            if (!Application::IsKeyPressed('E'))
            {
                renderDialogueBox("Victor", QUEST2.getDialogue(true));
            }
            else
            {
                renderDialogueBox("Victor", QUEST2.getDialogue(false));
            }
        }
        if (QUEST2.interaction() == true && Two.stage() == 4)
        {

            renderDialogueBox("Victor", QUEST2.quest_complete());
            Quest3_finished = true;
        }
        
    }
    modelStack.PopMatrix();
	
}

void sceneSP2::RenderQuestObjects()
{
    if (One.stage() == 1)
    {
        modelStack.PushMatrix();
        if (One.get_numberof_items() == 1 && One.Item1collected())
        {
            modelStack.Translate(One.getObject1_X(), 0, One.getObject1_Z());
            renderMesh(meshList[GEO_CONTAINER], true);
            
        }
        if (One.get_numberof_items() == 2 && !One.Item1collected())
        {
            modelStack.PushMatrix();
            modelStack.Translate(One.getObject1_X(), 0, One.getObject1_Z());
            renderMesh(meshList[GEO_CONTAINER], true);
            modelStack.PopMatrix();
        }
        if (One.get_numberof_items() == 2 && !One.Item2collected())
        {
            modelStack.Translate(One.getObject2_X(), 0, One.getObject2_Z());
            renderMesh(meshList[GEO_GASOLINE], true);
        }
        modelStack.PopMatrix();
    }
    else if (One.stage() == 3)
    {
       renderDialogueBox("", "Quest Complete!!");
    }

	if (Two.stage() == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Two.getObject1_X(), 0, Two.getObject1_Z());
		renderMesh(meshList[GEO_CONTAINER], true);
		modelStack.PopMatrix();
	}
	else if (Two.stage() == 3)
	{
		renderDialogueBox("", "Quest Complete!!");
	}

	if (Three.stage() == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Three.getObject1_X(), 0, Three.getObject1_Z());
		renderMesh(meshList[GEO_SWORD], true);
		modelStack.PopMatrix();
	}
	else if (Three.stage() == 3)
	{
		renderDialogueBox("", "Quest Complete!!");
	}

}

void sceneSP2::renderingSekHeng() {
    modelStack.PushMatrix();
    modelStack.Translate(sek_heng_.getObjectposX(), sek_heng_.getObjectposY(), sek_heng_.getObjectposZ());
    renderMesh(meshList[GEO_NPC1], true);
    modelStack.PopMatrix();
    if (sek_heng_.interaction() == false) {
        renderDialogueBox(sek_heng_.getName(), sek_heng_.returnDialogue());
    }

    //rendering of the hammer
    if (sek_heng_.gottenHammer() == false) {
        modelStack.PushMatrix();
        modelStack.Translate(sek_heng_.hammer.getObjectposX(), sek_heng_.hammer.getObjectposY(), sek_heng_.hammer.getObjectposZ());
        renderMesh(meshList[GEO_HAMMER], true);
        modelStack.PopMatrix();
    }
    //rendering of the hammer
}

void sceneSP2::RenderEmptyBox()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "EmptyBox") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "EmptyBox2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "EmptyBox3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "EmptyBox4") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "EmptyBox5") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			renderMesh(meshList[GEO_HAMMER], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void sceneSP2::RenderImageOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY) {
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack

    modelStack.Translate(x, y, 0);
    modelStack.Scale(sizeX, sizeY, 1);
    modelStack.Rotate(90, 1, 0, 0);
    renderMesh(mesh, false);

    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}

void sceneSP2::Renderteleporter() {
    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "TeleporterBox") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5,5,5);
            renderMesh(meshList[GEO_TELEPORTER], true);
            modelStack.PopMatrix();
            if (sek_heng_.SekHengSayIsOk() == true &&
                it.getObjectposX() + 6 > camera.position.x &&
                it.getObjectposX() - 6 < camera.position.x &&
                it.getObjectposZ() + 6 > camera.position.z &&
                it.getObjectposZ() - 6 < camera.position.z)
            {
                renderDialogueBox(it.getName(), "Press E to go to spaceship");
            }
            break;
        }
    }
    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "ParticleCube1" ||
            it.getName() == "ParticleCube2" ||
            it.getName() == "ParticleCube3" ||
            it.getName() == "ParticleCube4" || 
            it.getName() == "ParticleCube5" || 
            it.getName() == "ParticleCube6" || 
            it.getName() == "ParticleCube7" || 
            it.getName() == "ParticleCube8" || 
            it.getName() == "ParticleCube9" || 
            it.getName() == "ParticleCube10") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            renderMesh(meshList[GEO_PARTICLE_CUBE], true);
            modelStack.PopMatrix();
        }
    }
    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "Particle Light") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Scale(7.2f, 20, 7.2f);
            renderMesh(meshList[GEO_PARTICLE_LIGHT], true);
            modelStack.PopMatrix();
            break;
        }
    }
}

void sceneSP2::renderDialogueBox(const string& name, const string& dialogue) {
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 17, 16, 23, 5);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], name, Color(0, 1, 0), 3, 2.5, 5.5);
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 70, 40, -20);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], dialogue, Color(0, 1, 0), 3, 3.5, 4);
}

void sceneSP2::teleport() 
{
    for (auto it : camera.storage_of_objects) 
    {
        if (it.getName() == "TeleporterBox") 
        {
            if (it.getObjectposX() + 6 > camera.position.x &&
                it.getObjectposX() - 6 < camera.position.x &&
                it.getObjectposZ() + 6 > camera.position.z &&
                it.getObjectposZ() - 6 < camera.position.z)
            {
                Application::changeIntoScenario2();
            }
        }
    }
}


void sceneSP2::RenderBuilding()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Building1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(15, 15, 15);
			modelStack.Rotate(-90, 0, 1, 0);
			renderMesh(meshList[GEO_BUILDINGRED], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Building2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(15, 15, 15);
			modelStack.Rotate(90, 0, 1, 0);
			renderMesh(meshList[GEO_BUILDINGGREEN], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Building3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(15, 15, 15);
			modelStack.Rotate(180, 0, 1, 0);
			renderMesh(meshList[GEO_BUILDINGBLUE], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void sceneSP2::headanimation(double dt)
{
	if (QUEST3.interaction() == true)
	{
		if (headrotate == false)
		{
			headrotating += 15 * (float)(dt);
			if (headrotating > 10)
			{
				headrotate = true;
			}
		}
		else if (headrotate == true)
		{
			headrotating -= 15 * (float)(dt);
			if (headrotating < -5)
			{
				headrotate = false;
			}
		}
	}
	else
	{
		headrotating = 0;
	}
}

void sceneSP2::QuestCompleteCheck()
{
    if (Quest1_finished && !Quest2_finished && !Quest3_finished)
    {
        quest_stage = 1;
    }
    if (Quest1_finished && Quest2_finished && !Quest3_finished)
    {
        quest_stage = 2;
    }
    if (Quest1_finished && Quest2_finished && Quest3_finished)
    {
        quest_stage = 3;
    }
    if (quest_stage == 3)
    {
        quest_stage = 4;
    }
}

void sceneSP2::RenderStuffOnScreen(Mesh* mesh, float size_x,float size_y,float size_z, float rotate_X, float rotate_y, float rotate_z)
{
    //glDisable(GL_DEPTH_TEST);
    ////Add these code just after glDisable(GL_DEPTH_TEST);
    //Mtx44 ortho;
    //ortho.SetToOrtho(0, 170, 0, 90, -70, 70); //size of screen UI
    //projectionStack.PushMatrix();
    //projectionStack.LoadMatrix(ortho);
    //viewStack.PushMatrix();
    //viewStack.LoadIdentity(); //No need camera for ortho mode
    //modelStack.PushMatrix();
    //modelStack.LoadIdentity(); //Reset modelStack

    //modelStack.Translate(x, y, 1);
    //if (rotate_X > 0)
    //{
    //    modelStack.Rotate(rotate_X, 1, 0, 0);
    //}
    //if (rotate_y > 0)
    //{
    //    modelStack.Rotate(rotate_y, 0, 1, 0);
    //}

    //modelStack.Scale(sizex, sizey, 1);
    //renderMesh(mesh, true);


    //projectionStack.PopMatrix();
    //viewStack.PopMatrix();
    //modelStack.PopMatrix();

    //glEnable(GL_DEPTH_TEST);

    modelStack.PushMatrix();
    modelStack.Translate(camera.getCrossHairX(), camera.getCrossHairY(),camera.getCrossHairZ() );
    if (rotate_X > 0)
    {
        modelStack.Rotate(rotate_X, 1, 0, 0);
    }
    if (rotate_y > 0)
    {
        modelStack.Rotate(rotate_y, 0, 1, 0);
    }
    if (rotate_z > 0)
    {
        modelStack.Rotate(rotate_z, 0, 1, 0);
    }
    modelStack.Scale(size_x, size_y, size_z);
    renderMesh(meshList[GEO_AXES], false);
    renderMesh(mesh,true);
    modelStack.PopMatrix();
}

void sceneSP2::renderChunFei()
{

    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "robothead") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(-90, 0, 1, 0);
            modelStack.Rotate(headrotating, 1, 0, 0);
            modelStack.Scale(1.5, 1.5, 1.5);
            renderMesh(meshList[GEO_ROBOTHEAD], true);
            modelStack.PopMatrix();
            break;
        }
    }

    modelStack.PushMatrix();
    modelStack.Translate(QUEST3.NPC_getposition_x(), QUEST3.NPC_getposition_y(), QUEST3.NPC_getposition_z());
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    renderMesh(meshList[GEO_ROBOTBODY], true);
    if (quest_stage >= 1)
    {
        if (QUEST3.interaction() == true && Three.stage() < 4)
        {
            if (!Application::IsKeyPressed('E'))
            {
                renderDialogueBox("ChunFei", QUEST3.getDialogue(true));
            }
            else
            {
                renderDialogueBox("ChunFei", QUEST3.getDialogue(false));
            }
        }
        if (QUEST3.interaction() == true && Three.stage() == 4)
        {
            renderDialogueBox("ChunFei", QUEST3.quest_complete());
            Quest2_finished = true;
        }
    }
    modelStack.PopMatrix();
    if (quest_stage >= 2)
    {
        for (auto it : camera.storage_of_objects) {
            if (it.getName() == "sword") {
                modelStack.PushMatrix();
                modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
                modelStack.Rotate(-90, 0, 1, 0);
                modelStack.Scale(1.5, 1.5, 1.5);
                renderMesh(meshList[GEO_SWORD], true);
                modelStack.PopMatrix();
                break;
            }
        }
    }
}

void sceneSP2::populateArea()
{
    modelStack.PushMatrix();
    modelStack.Translate(38, 0, -310);
    modelStack.Scale(3,3,3);
    renderMesh(meshList[GEO_BOX], true);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
    modelStack.Translate(35, 0, -307);
    modelStack.Rotate(-25,0,1,0);
    modelStack.Scale(2.8f, 2.8f, 2.8f);
    renderMesh(meshList[GEO_BOX], true);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
    modelStack.Translate(38, 0, -305);
    modelStack.Rotate(45, 0, 1, 0);
    modelStack.Scale(3.5f, 3.5f, 3.5f);
    renderMesh(meshList[GEO_BOX], true);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
    modelStack.Translate(38, 3.5f, -305.5f);
    modelStack.Rotate(45, 0, 1, 0);
    modelStack.Scale(3.5f, 3.5f, 3.5f);
    renderMesh(meshList[GEO_BOX], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();
    modelStack.Translate(20, 0, -305.5f);
    //modelStack.Rotate(45, 0, 1, 0);
    modelStack.Scale(2, 2, 2);
    renderMesh(meshList[GEO_BARREL], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(15, 0, -305.5f);
    //modelStack.Rotate(45, 0, 1, 0);
    modelStack.Scale(2, 2, 2);
    renderMesh(meshList[GEO_BARREL], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(10, 0, -305.5f);
    //modelStack.Rotate(45, 0, 1, 0);
    modelStack.Scale(2, 2, 2);
    renderMesh(meshList[GEO_BARREL], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(5, 0, -305.5f);
    //modelStack.Rotate(45, 0, 1, 0);
    modelStack.Scale(2, 2, 2);
    renderMesh(meshList[GEO_BARREL], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(17, 0, -310.5f);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(-30, 1, 0, 0);
    modelStack.Scale(2, 2, 2);
    renderMesh(meshList[GEO_BARREL], true);
    modelStack.PopMatrix();


	//victor

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
		}
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel4") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel5") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel6") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel7") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel8") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Barrel9") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_BARREL], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox4") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox5") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox6") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "pBox6") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(5, 5, 5);
			renderMesh(meshList[GEO_BOX], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle1") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle4") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle5") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle6") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle7") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "vehicle8") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(4, 4, 4);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}
}


