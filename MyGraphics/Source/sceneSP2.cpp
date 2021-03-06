#include "GL\glew.h"
#include <sstream>

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "MaterialBuilder.h"
#include "Material.h"
#include "Material.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <iomanip>
#include "MyPhysics.h"

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

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");


	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(-280, 70, 290);
	light[0].color.Set(1, 1, 1);
	light[0].power = 3;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.0f, 1.0f, 0.0f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(0, 20, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.0f, 1.0f, 0.0f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);


    //Initialize camera settings
    camera.Init("cameraDriven//scene1.txt");
	//camera.InitObjects("scenario1Driven//");
    camera.camType = Camera3::FIRST_PERSON;

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    meshList[GEO_COMIC_TEXT] = MeshBuilder::GenerateText("comic sans text", 16, 16);
    meshList[GEO_COMIC_TEXT]->textureID = LoadTGA("Image//scene3//comicSans.tga");

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light_ball", Color(1,1,1));

    /***************************************************************************/
    //environment
    /***************************************************************************/
    //skybox
    meshList[GEO_SPACE_SKYBOX] = MeshBuilder::GenerateOBJ("space skybox", "OBJ//scene1//Space_Skybox.obj");
    meshList[GEO_SPACE_SKYBOX]->textureID = LoadTGA("Image//scene1//skybox//Space_Skybox_UV.tga");
    //Space ground mesh
    meshList[GEO_SPACE_GROUNDMESH] = MeshBuilder::GenerateOBJ("Space ground mesh", "OBJ//scene1//Space_groundmesh.obj");
    meshList[GEO_SPACE_GROUNDMESH]->textureID = LoadTGA("Image//scene1//Space_groundmesh.tga");
	meshList[GEO_SPACE_GROUNDMESH]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPACE_GROUNDMESH]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPACE_GROUNDMESH]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPACE_GROUNDMESH]->material.kShininess = 1.0f;
    // meshList[GEO_SPACE_GROUNDMESH]->material = MaterialBuilder::GenerateBlinn();

    //space walls
    meshList[GEO_SPACE_WALL] = MeshBuilder::GenerateOBJ("Space wall", "OBJ//scene1//space_walls.obj");
    meshList[GEO_SPACE_WALL]->textureID = LoadTGA("Image//scene1//space_station_wall.tga");
	meshList[GEO_SPACE_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPACE_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPACE_WALL]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);;
	meshList[GEO_SPACE_WALL]->material.kShininess = 2.0f;



    //User Interface
    meshList[GEO_UI] = MeshBuilder::GenerateOBJ("User Interface", "OBJ//scene1//User_Interface.obj");
    meshList[GEO_UI]->textureID = LoadTGA("Image//scene1//UI_UV.tga");
    //User Interface
    
    //quest items
    meshList[GEO_SCREWDRIVER] = MeshBuilder::GenerateOBJ("screw driver", "OBJ//scene1//ScrewDriver.obj");
    meshList[GEO_SCREWDRIVER]->textureID = LoadTGA("Image//scene1//Screwdriver.tga");
    
    meshList[GEO_CONTAINER] = MeshBuilder::GenerateOBJ("container", "OBJ//scene1//Container.obj");
    meshList[GEO_CONTAINER]->textureID = LoadTGA("Image//scene1//Container.tga");
   
    meshList[GEO_GASOLINE] = MeshBuilder::GenerateOBJ("gasoline", "OBJ//scene1//Gasoline.obj");
    meshList[GEO_GASOLINE]->textureID = LoadTGA("Image//scene1//Gasoline.tga");
   
    meshList[GEO_HAMMER] = MeshBuilder::GenerateOBJ("hammer", "OBJ//scene1//Hammer.obj");
    meshList[GEO_HAMMER]->textureID = LoadTGA("Image//scene1//Hammer.tga");

    //quest items

	
	//SpaceStation
	meshList[GEO_STATION] = MeshBuilder::GenerateOBJ("Station", "OBJ//scene1//Station.obj");
	meshList[GEO_STATION]->textureID = LoadTGA("Image//scene1//Station.tga");
	meshList[GEO_STATION]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_STATION]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_STATION]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_STATION]->material.kShininess = 3.0f;
	//SpaceStationChair
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("Chair", "OBJ//scene1//Chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//scene1//Chair.tga");
	meshList[GEO_CHAIR]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CHAIR]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CHAIR]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CHAIR]->material.kShininess = 3.0f;
	//SpaceStationTable
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Table", "OBJ//scene1//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//scene1//Table.tga");
	meshList[GEO_TABLE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TABLE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TABLE]->material.kShininess = 1.0f;

	//SpaceStationBox
	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("Box", "OBJ//scene1//Box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//scene1//Box.tga");
	meshList[GEO_BOX]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_BOX]->material.kShininess = 1.0f;

	//SpaceStationBox
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//scene1//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//scene1//Door.tga");
	meshList[GEO_DOOR]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DOOR]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DOOR]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DOOR]->material.kShininess = 3.0f;

	//SpaceStationCryostasis
	meshList[GEO_CRYOSTASIS] = MeshBuilder::GenerateOBJ("Cryostasis", "OBJ//scene1//cryostasis.obj");
	meshList[GEO_CRYOSTASIS]->textureID = LoadTGA("Image//scene1//cryostasis.tga");
	meshList[GEO_CRYOSTASIS]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CRYOSTASIS]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CRYOSTASIS]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CRYOSTASIS]->material.kShininess = 2.0f;

	//SpaceStationKeyCard
	meshList[GEO_KEYCARD] = MeshBuilder::GenerateOBJ("KeyCard", "OBJ//scene1//KeyCard.obj");
	meshList[GEO_KEYCARD]->textureID = LoadTGA("Image//scene1//KeyCard.tga");
	//SpaceShuttle
	meshList[GEO_SPACESHUTTLE] = MeshBuilder::GenerateOBJ("SpaceShuttle", "OBJ//scene1//FlyingVehicle.obj");
	meshList[GEO_SPACESHUTTLE]->textureID = LoadTGA("Image//scene1//FlyingVehicle.tga");
	meshList[GEO_SPACESHUTTLE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SPACESHUTTLE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SPACESHUTTLE]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPACESHUTTLE]->material.kShininess = 5.0f;

	//Teleporter
	meshList[GEO_TELEPORTER] = MeshBuilder::GenerateOBJ("Teleport", "OBJ//scene1//Teleporter.obj");
	meshList[GEO_TELEPORTER]->textureID = LoadTGA("Image//scene1//Teleporter.tga");
	meshList[GEO_TELEPORTER]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_TELEPORTER]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_TELEPORTER]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_TELEPORTER]->material.kShininess = 1.0f;

    meshList[GEO_PARTICLE_LIGHT] = MeshBuilder::GenerateOBJ("particle light", "OBJ//scene1//teleporting_light.obj");
    meshList[GEO_PARTICLE_LIGHT]->textureID = LoadTGA("Image//scene1//particle_light.tga");
	meshList[GEO_PARTICLE_LIGHT]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PARTICLE_LIGHT]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PARTICLE_LIGHT]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_PARTICLE_LIGHT]->material.kShininess = 1.0f;

    meshList[GEO_PARTICLE_CUBE] = MeshBuilder::GenerateOBJ("particle cube", "OBJ//scene1//Box.obj");
    meshList[GEO_PARTICLE_CUBE]->textureID = LoadTGA("Image//scene1//particle_light.tga");
	meshList[GEO_PARTICLE_CUBE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PARTICLE_CUBE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PARTICLE_CUBE]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_PARTICLE_CUBE]->material.kShininess = 1.0f;
    //Teleporter

	//red building
	meshList[GEO_BUILDINGRED] = MeshBuilder::GenerateOBJ("BuildingRed", "OBJ//scene1//Building.obj");
	meshList[GEO_BUILDINGRED]->textureID = LoadTGA("Image//scene1//BuildingRed.tga");
	meshList[GEO_BUILDINGRED]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BUILDINGRED]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BUILDINGRED]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);;
	meshList[GEO_BUILDINGRED]->material.kShininess = 1.0f;

	//green building
	meshList[GEO_BUILDINGGREEN] = MeshBuilder::GenerateOBJ("BuildingBlue", "OBJ//scene1//Building.obj");
	meshList[GEO_BUILDINGGREEN]->textureID = LoadTGA("Image//scene1//BuildingGreen.tga");
	meshList[GEO_BUILDINGGREEN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BUILDINGGREEN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BUILDINGGREEN]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BUILDINGGREEN]->material.kShininess = 1.0f;

	//Blue building
	meshList[GEO_BUILDINGBLUE] = MeshBuilder::GenerateOBJ("BuildingGreen", "OBJ//scene1//Building.obj");
	meshList[GEO_BUILDINGBLUE]->textureID = LoadTGA("Image//scene1//BuildingBlue.tga");
	meshList[GEO_BUILDINGBLUE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BUILDINGBLUE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BUILDINGBLUE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BUILDINGBLUE]->material.kShininess = 1.0f;

	//Barrel
	meshList[GEO_BARREL] = MeshBuilder::GenerateOBJ("Barrel", "OBJ//scene1//Barrel.obj");
	meshList[GEO_BARREL]->textureID = LoadTGA("Image//scene1//Barrel.tga");
	meshList[GEO_BARREL]->material = MaterialBuilder::GenerateLambert();
	meshList[GEO_BARREL]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BARREL]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BARREL]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_BARREL]->material.kShininess = 1.0f;

	//land vehicle
	meshList[GEO_LANDVEHICLE] = MeshBuilder::GenerateOBJ("Vehicle", "OBJ//scene1//LandVehicle.obj");
	meshList[GEO_LANDVEHICLE]->textureID = LoadTGA("Image//scene1//LandVehicle.tga");
	meshList[GEO_LANDVEHICLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_LANDVEHICLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_LANDVEHICLE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_LANDVEHICLE]->material.kShininess = 1.0f;

	//land vehicle
	meshList[GEO_BUTTON] = MeshBuilder::GenerateOBJ("Button", "OBJ//scene1//Button.obj");
	meshList[GEO_BUTTON]->textureID = LoadTGA("Image//scene1//Button.tga");
	meshList[GEO_BUTTON]->material = MaterialBuilder::GenerateLambert();

    //NPC
    meshList[GEO_NPC1] = MeshBuilder::GenerateOBJ("Guan Hui", "OBJ//scene1//android_2.obj");
    meshList[GEO_NPC1]->textureID = LoadTGA("Image//scene1//android_2_blue.tga");
	meshList[GEO_NPC1]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_NPC1]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_NPC1]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_NPC1]->material.kShininess = 1.0f;

    //NPC
	meshList[GEO_NPC_QUEST2] = MeshBuilder::GenerateOBJ("Victor", "OBJ//scene1//android.obj");
	meshList[GEO_NPC_QUEST2]->textureID = LoadTGA("Image//scene1//androidRed.tga");

    //sek heng NPC
    meshList[GEO_NPC_QUEST1] = MeshBuilder::GenerateOBJ("Sek Heng", "OBJ//scene1//android_2.obj");
    meshList[GEO_NPC_QUEST1]->textureID = LoadTGA("Image//scene1//android_2_green.tga");
    meshList[GEO_NPC_QUEST1]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
    meshList[GEO_NPC_QUEST1]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
    meshList[GEO_NPC_QUEST1]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
    meshList[GEO_NPC_QUEST1]->material.kShininess = 1.0f;

    meshList[GEO_INVIS_CURSOR] = MeshBuilder::GenerateSphere("invisible cursor", Color(0.5, 0.5, 0.5));

    //text box
    meshList[GEO_TEXT_BOX] = MeshBuilder::GenerateQuad("text box", Color(1, 1, 1));
    meshList[GEO_TEXT_BOX]->textureID = LoadTGA("Image//scene1//textbox.tga");
    //text box

	//chunfei npc
	meshList[GEO_ROBOTHEAD] = MeshBuilder::GenerateOBJ("robothead", "OBJ//scene1//robothead.obj");
	meshList[GEO_ROBOTHEAD]->textureID = LoadTGA("Image//scene1//robot.tga");

	meshList[GEO_ROBOTBODY] = MeshBuilder::GenerateOBJ("robotbody", "OBJ//scene1//robotbody.obj");
	meshList[GEO_ROBOTBODY]->textureID = LoadTGA("Image//scene1//robot.tga");

	meshList[GEO_SWORD] = MeshBuilder::GenerateOBJ("sword", "OBJ//scene1//sword.obj");
	meshList[GEO_SWORD]->textureID = LoadTGA("Image//scene1//sword.tga");

    meshList[GEO_TYRE] = MeshBuilder::GenerateOBJ("tyre", "OBJ//scene1//Tire.obj");

    //MiniGame pieces
    meshList[GEO_MINIGAME_PIECE_1] = MeshBuilder::GenerateOBJ("Minigame Piece 1", "OBJ//scene1//MiniGame//minigame_piece1.obj");
    meshList[GEO_MINIGAME_PIECE_1]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_2] = MeshBuilder::GenerateOBJ("Minigame Piece 2", "OBJ//scene1//MiniGame//minigame_piece2.obj");
    meshList[GEO_MINIGAME_PIECE_2]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_3] = MeshBuilder::GenerateOBJ("Minigame Piece 3", "OBJ//scene1//MiniGame//minigame_piece3.obj");
    meshList[GEO_MINIGAME_PIECE_3]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_4] = MeshBuilder::GenerateOBJ("Minigame Piece 4", "OBJ//scene1//MiniGame//minigame_piece4.obj");
    meshList[GEO_MINIGAME_PIECE_4]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_5] = MeshBuilder::GenerateOBJ("Minigame Piece 5", "OBJ//scene1//MiniGame//minigame_piece5.obj");
    meshList[GEO_MINIGAME_PIECE_5]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_6] = MeshBuilder::GenerateOBJ("Minigame Piece 6", "OBJ//scene1//MiniGame//minigame_piece6.obj");
    meshList[GEO_MINIGAME_PIECE_6]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_7] = MeshBuilder::GenerateOBJ("Minigame Piece 7", "OBJ//scene1//MiniGame//minigame_piece7.obj");
    meshList[GEO_MINIGAME_PIECE_7]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_8] = MeshBuilder::GenerateOBJ("Minigame Piece 8", "OBJ//scene1//MiniGame//minigame_piece8.obj");
    meshList[GEO_MINIGAME_PIECE_8]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_PIECE_9] = MeshBuilder::GenerateOBJ("Minigame Piece 9", "OBJ//scene1//MiniGame//minigame_piece9.obj");
    meshList[GEO_MINIGAME_PIECE_9]->textureID = LoadTGA("Image//scene1//MiniGame//MiniGame.tga");

    meshList[GEO_MINIGAME_SELECTOR] = MeshBuilder::GenerateOBJ("Minigame Selector", "OBJ//scene1//MiniGame//minigame_selector.obj");
    meshList[GEO_MINIGAME_SELECTOR]->textureID = LoadTGA("Image//scene1//MiniGame//selector.tga");


    //on_light = true;

    //meshList[]
    Mtx44 projection;
    projection.SetToPerspective(45.f, static_cast<float>(screenWidth / screenHeight), 0.1f, 20000.f);
    projectionStack.LoadMatrix(projection);

    //initialise camera_position_x and z;
    framePerSecond = 0;
    camera.cursorCoordX = screenWidth / 2;
    camera.cursorCoordY = screenHeight / 2;

	door.Init(camera);
	door.getQuestStage();
	door.getCard1();
	door.getCard2();
	door.openSasame();
	door.roomLight();
	door.switchText();
	door.getCardText();

	camera.InitObjects("scenario1Driven//objects.txt");

    //initialise npc
    QUEST1.Init("First NPC",20, Vector3(-270, 0, 194), 5, 5, camera, "NPC data//NPC_1.txt");
    //initialise quest
	One.Init("First quest", camera, 2, Vector3(314, 0, 314), 5, Vector3(135, 0, 304), 5);

	QUEST2.Init("Sec NPC",16, Vector3(-150, 0, -300), 5, 5, camera, "NPC data//NPC_2.txt");
	Two.Init("Sec quest", camera, 1, Vector3(-167, 0, 297), 5, Vector3(0, 0, 0), 5);

    //Sek Heng sucks 's stuff and initialization
    sek_heng_.init("sekheng//sek_heng_stuff.txt");
    sek_heng_.initDialogues("sekheng//dialogues.txt", camera);
    //Sek Heng's stuff and initialization

	//chunfei's robotnpc

	//initialise npc3
	//QUEST3.Init("Chunfei NPChead", Vector3(0, 5.5, 250), 2, 2, camera, "NPC data//NPC_3.txt");
	QUEST3.Init("Chunfei NPCbody", 12,Vector3(0, 0, 250), 10, 10, camera, "NPC data//NPC_3.txt");
	//initialise quest3
	Three.Init("Third quest", camera, 1, Vector3(300, 0, -140), 5, Vector3(0, 0, 0), 0); 

	/*for (auto it : camera.storage_of_objects) {
		if (it.getName() == "robotbody") {
			robotNPC.Init(camera, Vector3(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ()));
			break;
		}
	}*/
	headrotate = false;
	headrotating = 0;
	//chunfei's stuff

    quest_stage = 0;

	lightSwitch = true;

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
            particleHandlers.push_back(*it);
        }
    }
    //animating particle cube

    //animating teleporting
    teleportCoordY = 0;
    startTeleporting = false;
    //animating teleporting

    //music updates
    musicTimeDelay = 0.5;
    //music updates

    tutorialscreen = true;

    //for minigame
    MiniGame.init();
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

    

    //if (Application::IsKeyPressed('1')) //enable back face culling
    //    glEnable(GL_CULL_FACE);
    //if (Application::IsKeyPressed('2')) //disable back face culling
    //    glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed(VK_NUMPAD4))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed(VK_NUMPAD5))
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
                if ((*it).objectPos.x > -242)
                {
                    (*it).objectPos.x = -242;
                }
                else {
                    Application::musics->playGateEffect(vec3df((*it).getObjectposX(), (*it).getObjectposY(), (*it).getObjectposZ()));
                }
                break;
            }
        }
    }
	if (door.openSasame() == 0)
	{
		for (vector<objectsForDisplay>::iterator it = camera.storage_of_objects.begin(); it != camera.storage_of_objects.end(); ++it) {
			if ((*it).getName() == "Door")
			{
				if (Application::IsKeyPressed('R'))
				{
					(*it).objectPos.x = -275;
				}
				break;
			}
		}
	}

	if (door.roomLight() == true)
	{
		light[0].position.Set(-280, 60, 290);
	}
	else if (door.roomLight() == false)
	{
		light[0].position.Set(-500, 60, 290);
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

    //animating particle cube
    for (vector<objectsForDisplay>::iterator it = particleHandlers.begin(); it != particleHandlers.end(); ++it) {
                if ((*it).objectPos.y < 40) {
                    (*it).objectPos.y += 3 * (float)(dt);
                }
                else {
                    (*it).objectPos.y = (*it).originalPos.y;
                    (*it).objectPos.x = Math::RandFloatMinMax(-3, 3);
                    (*it).objectPos.z = Math::RandFloatMinMax(-3, 3);
                }
    }
    //animating particle cube

    //music updates
    Application::musics->playDarthVaderBackground();
    musicTimeDelay += dt;
    if (musicTimeDelay > 0.5) {
        Application::musics->updatePlayerPos(
            vec3df(camera.getCameraXcoord(), camera.getCameraYcoord(), camera.getCameraZcoord()),   //camera's position
            vec3df(camera.target.x, camera.target.y, camera.target.z),  //camera's target
            vec3df(camera.up.x, camera.up.y, camera.up.z)   //camera's up
            );
    }
    //music updates

    if (Application::IsKeyPressed('E') && sek_heng_.SekHengSayIsOk()
        && teleport() == true) {
        //animateTeleporting(dt);
        //startTeleporting = true;
        MiniGame.update(dt, true);

    }
    //MiniGame update
    if (MiniGame.minigame_started())
    {
        MiniGame.update(dt, true);
    }
    if (MiniGame.result())
    {
        startTeleporting = true;
    }
    if (startTeleporting) {
        animateTeleporting(dt);
    }
    else {
        camera.Update(dt);
    }

	door.update(dt);

    //check for tutorial screen
    if (Application::IsKeyPressed('W') ||
        Application::IsKeyPressed('A') ||
        Application::IsKeyPressed('S') ||
        Application::IsKeyPressed('D')
        )
    {
        tutorialscreen = false;
    }
    if (Application::IsKeyPressed('T'))
    {
        tutorialscreen = true;
    }
	if (Application::IsKeyPressed('R'))
	{
		reset();
	}
}

/******************************************************************************/
/*!
\brief - reset the entire scene 1
/******************************************************************************/

void sceneSP2::reset()
{
	quest_stage = 0;
	camera.Reset();
	npc1.reset();
	door.reset();
	sek_heng_.reset();
	Quest1_finished = false;
	Quest2_finished = false;
	Quest3_finished = false;
	Quest4_finished = false;
	tutorialscreen = true;
	teleportCoordY = 0;
	startTeleporting = false;
	musicTimeDelay = 0.5;
	test_quest.reset();

	//initialise quest
	One.Init("First quest", camera, 2, Vector3(314, 0, 314), 5, Vector3(135, 0, 304), 5);
	Two.Init("Sec quest", camera, 1, Vector3(-167, 0, 297), 5, Vector3(0, 0, 0), 5);
	//initialise quest3
	Three.Init("Third quest", camera, 1, Vector3(300, 0, -140), 5, Vector3(0, 0, 0), 0);

	MiniGame.init();
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

/******************************************************************************/
/*!
\brief - render everything in the room
*/
/******************************************************************************/

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
		renderMesh(meshList[GEO_BOX], true);
		modelStack.PopMatrix();
	}

	for (float i = 0; i < 50; i += 10)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-255, 0, 270 + i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], true);
		modelStack.PopMatrix();
	}

	for (float i = 0; i < 50; i += 5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-255, 5, 268 + i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], true);
		modelStack.PopMatrix();
	}

	for (float i = 0; i < 55; i += 5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-250.f, 0.f, 265 + i);
		modelStack.Scale(5, 5, 5);
		renderMesh(meshList[GEO_BOX], true);
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
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Button") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.5, 0.5, 0.5);
			renderMesh(meshList[GEO_BUTTON], true);
			modelStack.PopMatrix();
			break;
		}
	}

	if (door.switchText() == true)
	{
		renderDialogueBox("Light", "Press E to toggle light");
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
	
	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	

    //renderMesh(meshList[GEO_AXES], false);

    //render skybox
    modelStack.PushMatrix();
    modelStack.Scale(300, 300, 300);
    RenderSkybox();
    modelStack.PopMatrix();
    //render skybox

    //render ground mesh
    modelStack.PushMatrix();
    modelStack.Scale(19.9f, 1, 19.9f);
    Rendergroundmesh();
    
    modelStack.PopMatrix();
    //render ground mesh

    modelStack.PushMatrix();
    modelStack.Scale(19.9f, 19.9f, 19.9f);
	renderMesh(meshList[GEO_SPACE_WALL], true);
    modelStack.PopMatrix();

    
	//render Spaceship
	RenderSpaceShuttle();
	//render Building
	RenderBuilding();

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
    //RenderUserInterface(meshList[GEO_UI], 1, 40, 40);
    //modelStack.PopMatrix();

    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Hello Screen", Color(0, 1, 0), 4, 0.5, 1.5);

	RenderStation();

    populateArea();
    
    modelStack.PushMatrix();
    //modelStack.Rotate(180,0,1,0);
    RenderMinigamePieces();
    modelStack.PopMatrix();

   /* modelStack.PushMatrix();
    modelStack.Translate(camera.getCrossHairX(), camera.getCrossHairY(), camera.getCrossHairZ());
    renderMesh(meshList[GEO_INVIS_CURSOR], false);
    modelStack.PopMatrix();*/

    //****************************************************************************//
    //On screen objects
    //****************************************************************************//
    //
    //std::stringstream ss;
    //ss << "FPS : " << static_cast<int>(framePerSecond);
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 1.8f, 1.25f, 16.5f);
    //
    //std::stringstream connectPosX;

    //connectPosX << std::fixed << std::setprecision(2) << "X : " << camera.getCameraXcoord();
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosX.str(), Color(0, 1, 0), 1.8f, 1.5f, 21.2f);

    //std::stringstream connectPosZ;
    //connectPosZ << std::fixed << std::setprecision(2) << "Z : " << camera.getCameraZcoord();
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosZ.str(), Color(0, 1, 0), 1.8f, 1.5f, 19.f);

    //testing(DO NOT DELETE THIS)
   /* RenderStuffOnScreen(meshList[GEO_CONTAINER],"left",0.05f,1.3,2,-0.8,0,0,0);

    RenderStuffOnScreen(meshList[GEO_CONTAINER], "right", 0.05f, -1.3, 2, -0.8,0,0,0);*/
    
    /*
    RenderStuffOnScreen(meshList[GEO_SWORD], "left", 0.3f, 0.75, 2, -0.6,0,0,0);

    RenderStuffOnScreen(meshList[GEO_SWORD], "right", 0.3f, -0.75, 2, -0.65,0,0,0);
    */
    /*
    RenderStuffOnScreen(meshList[GEO_GASOLINE], "left", 0.7f, 1.4, 2, -1,90,90,90);
    
    RenderStuffOnScreen(meshList[GEO_GASOLINE], "right", 0.7f, -1.4, 2, -1,90,90,90);
    */

    //RenderStuffOnScreen(meshList[GEO_HAMMER], "left", 0.2f, 1.4, 2, -0.7, 0, 0, 90);

    //RenderStuffOnScreen(meshList[GEO_HAMMER], "right", 0.2f, -1.4, 2, -0.7, 0, 0, -90);



    RenderTutorialScreen();


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
/******************************************************************************/
/*!
\brief -
rendering of skybox

*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief -
rendering of user interface

\param mesh - a pointer to the specific mesh
\param size - size of the text
\param x - x coordinate of the text
\param y - y coordinate of the text
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief -
rendering of ground texture

*/
/******************************************************************************/
void sceneSP2::Rendergroundmesh()
{
    modelStack.PushMatrix();
	renderMesh(meshList[GEO_SPACE_GROUNDMESH], true);
    modelStack.PopMatrix();
}
/**********************************************************************************************************/
//render quest items
/**********************************************************************************************************/
void sceneSP2::RenderScrewDriver()
{
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);
	renderMesh(meshList[GEO_CONTAINER], true);
    modelStack.PopMatrix();
}
void sceneSP2::RenderHammer()
{
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -200);
	renderMesh(meshList[GEO_GASOLINE], true);
    modelStack.PopMatrix();
}
void sceneSP2::RenderContainer()
{
    modelStack.PushMatrix();
    modelStack.Translate(30, 0, 20);
	renderMesh(meshList[GEO_HAMMER], true);
    modelStack.PopMatrix();
}
void sceneSP2::RenderGasoline()
{
    modelStack.PushMatrix();
    modelStack.Translate(90, 0, -30);
	renderMesh(meshList[GEO_SCREWDRIVER], true);
    modelStack.PopMatrix();
}
/**********************************************************************************************************/
//render quest items
/**********************************************************************************************************/

/******************************************************************************/
/*!
\brief -
rendering of space shuttle
*/
/******************************************************************************/

void sceneSP2::RenderSpaceShuttle()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "Spaceshuttle") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(30, 30, 30);
			renderMesh(meshList[GEO_SPACESHUTTLE], true);
			modelStack.PopMatrix();
			break;
		}
	}
}
/******************************************************************************/
/*!
\brief -
rendering of NPC and quest
*/
/******************************************************************************/
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
	modelStack.Scale(1.5, 1.5, 1.5);
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
	modelStack.Scale(1.5,1.5,1.5);
	renderMesh(meshList[GEO_NPC_QUEST2], true);
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
    //quest 1
    if (One.stage() == 1)
    {
        modelStack.PushMatrix();
        if (One.get_numberof_items() == 1 && !One.Item1collected())
        {
            modelStack.Translate(One.getObject1_X(), 0, One.getObject1_Z());
            renderMesh(meshList[GEO_CONTAINER], true);
        }

        
        if (One.get_numberof_items() == 2 && !One.Item1collected())
        {
            modelStack.PushMatrix();
            modelStack.Translate(One.getObject1_X(), 0, One.getObject1_Z());
			modelStack.Scale(0.2f, 0.2f, 0.2f);
            renderMesh(meshList[GEO_CONTAINER], true);
            modelStack.PopMatrix();
        }
        if (One.get_numberof_items() == 2 && !One.Item2collected())
        {
            modelStack.Translate(One.getObject2_X(), 0, One.getObject2_Z());
			modelStack.Scale(0.2f, 0.2f, 0.2f);
			renderMesh(meshList[GEO_CONTAINER], true);
        }
        modelStack.PopMatrix();
    }
    else if (One.stage() == 3)
    {
       renderDialogueBox("", "Quest Complete!! Return to Guan Hui");
    }
    //render quest object on screen
    if (One.get_numberof_items() == 1 && One.Item1collected() == true
        && Quest1_finished == false)
    {
        RenderStuffOnScreen(meshList[GEO_CONTAINER], "right", 0.05f, -1.3f, 2, -0.8f, 0, 0, 0);
    }
    if (One.get_numberof_items() == 2 && One.Item1collected() == true
        && Quest1_finished == false)
    {
        RenderStuffOnScreen(meshList[GEO_CONTAINER], "right", 0.05f, -1.3f, 2, -0.8f, 0, 0, 0);
    }
    if (One.get_numberof_items() == 2 && One.Item2collected() == true
        && Quest1_finished == false)
    {
        RenderStuffOnScreen(meshList[GEO_CONTAINER], "left", 0.05f, 1.3f, 2, -0.8f, 0, 0, 0);
    }

    //quest 2
	if (Two.stage() == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Two.getObject1_X(), 0, Two.getObject1_Z());
		modelStack.Scale(2, 2, 2);
		renderMesh(meshList[ GEO_GASOLINE], true);
		modelStack.PopMatrix();
	}
    else if (Two.stage() == 3)
	{
		renderDialogueBox("", "Quest Complete!!");
	}

    if (Two.get_numberof_items() == 1 && Two.Item1collected() == true
        && Quest3_finished == false)
    {
        RenderStuffOnScreen(meshList[GEO_GASOLINE], "right", 0.7f, -1.4f, 2, -1, 90, 90, 90);
    }

    //quest 3
    /*
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

    if (Three.get_numberof_items() == 1 && Three.Item1collected() == true
        && Quest3_finished == false)
    {
        RenderStuffOnScreen(meshList[GEO_SWORD], "right", 0.3f, -0.75f, 2, -0.65f, 0, 0, 0);
    }
    */
}

/******************************************************************************/
/*!
\brief - a method to render Sek Heng and his quest
*/
/******************************************************************************/
void sceneSP2::renderingSekHeng() {
    modelStack.PushMatrix();
    modelStack.Translate(sek_heng_.getObjectposX(), sek_heng_.getObjectposY(), sek_heng_.getObjectposZ());
	modelStack.Scale(1.5, 1.5, 1.5);
    renderMesh(meshList[GEO_NPC_QUEST1], true);
    modelStack.PopMatrix();
    if (sek_heng_.interaction() == false) {
        renderDialogueBox(sek_heng_.getName(), sek_heng_.returnDialogue());
    }

    //rendering of the hammer
    if (sek_heng_.gottenHammer() == false && sek_heng_.getStage() == 1) {
        modelStack.PushMatrix();
        modelStack.Translate(sek_heng_.hammer.getObjectposX(), sek_heng_.hammer.getObjectposY(), sek_heng_.hammer.getObjectposZ());
        renderMesh(meshList[GEO_HAMMER], true);
        modelStack.PopMatrix();
    }
    else if (sek_heng_.gottenHammer() == true && sek_heng_.getStage() == 1) {

        RenderStuffOnScreen(meshList[GEO_HAMMER], "right", 0.2f, -1.4f, 2, -0.7f, 0, 0, -90);
    }
    //rendering of the hammer
}

/******************************************************************************/
/*!
\brief - to allow non-uniform scaling of image

\param mesh - a pointer to the specific mesh
\param text - the text that needs to be rendered
\param color - the color of the text
\param x - x coordinate of the text
\param y - y coordinate of the text

\param sizeX - size of the text based on the X-axis

\param sizeY - size of the text based on the Y-axis
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Teleporter and it's particle effect
*/
/******************************************************************************/
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
    //for (auto it : camera.storage_of_objects) {
    //    if (it.getName() == "ParticleCube1" ||
    //        it.getName() == "ParticleCube2" ||
    //        it.getName() == "ParticleCube3" ||
    //        it.getName() == "ParticleCube4" || 
    //        it.getName() == "ParticleCube5" || 
    //        it.getName() == "ParticleCube6" || 
    //        it.getName() == "ParticleCube7" || 
    //        it.getName() == "ParticleCube8" || 
    //        it.getName() == "ParticleCube9" || 
    //        it.getName() == "ParticleCube10") {
    //        modelStack.PushMatrix();
    //        modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
    //        renderMesh(meshList[GEO_PARTICLE_CUBE], true);
    //        modelStack.PopMatrix();
    //    }
    //}
    for (auto it : particleHandlers) {
                modelStack.PushMatrix();
                modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
                renderMesh(meshList[GEO_PARTICLE_CUBE], true);
                modelStack.PopMatrix();
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

/******************************************************************************/
/*!
\brief - create a dialogue box easily

\param name - the name of the interacted object

\param dialogue - the words said by that interacted object
*/
/******************************************************************************/
void sceneSP2::renderDialogueBox(const string& name, const string& dialogue) {
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 17, 16, 23, 5);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], name, Color(0, 1, 0), 3, 2.5, 5.5);
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 70, 40, -20);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], dialogue, Color(0, 1, 0), 3, 3.5, 4);
}

/******************************************************************************/
/*!
\brief - the logic of interaction between the teleporter and player

\return - true if player is inisde it's interacting boundary

\return - false if the player is outside it's interacting boundary
*/
/******************************************************************************/
bool sceneSP2::teleport()
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
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

/******************************************************************************/
/*!
\brief -
rendering of building
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief -
rendering of chun fei head animation
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief -
check if quest is completed
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief -
rendering of item taken on screen
*/
/******************************************************************************/
void sceneSP2::RenderStuffOnScreen(Mesh* mesh, string direction, float size, float x, float y, float z, float rotate_x, float rotate_y, float rotate_z)
{
    if (direction == "left")
    {
        modelStack.PushMatrix();
        modelStack.Translate(camera.getCameraXcoord(), camera.getCameraYcoord(), camera.getCameraZcoord());
        modelStack.PushMatrix();
        modelStack.Rotate(camera.getCameraYrotation(), 0, 1, 0);
        modelStack.Rotate(camera.getCameraXrotation(), 1, 0, 0);

        modelStack.Rotate(90, 1, 0, 0);
        modelStack.Rotate(-60, 0, 1, 0);
        modelStack.Translate(x, y, z);
        modelStack.Rotate(180, 1, 0, 0);
        if (rotate_x != 0)
        {
            modelStack.Rotate(rotate_x, 1, 0, 0);
        }
        if (rotate_y != 0)
        {
            modelStack.Rotate(rotate_y, 0, 1, 0);
        }
        if (rotate_z != 0)
        {
            modelStack.Rotate(rotate_z, 0, 0, 1);
        }
        
        modelStack.Scale(size, size, size);
        //renderMesh(meshList[GEO_AXES], false);
        renderMesh(mesh, true);

        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }
    if (direction == "right")
    {
        modelStack.PushMatrix();
        modelStack.Translate(camera.getCameraXcoord(), camera.getCameraYcoord(), camera.getCameraZcoord());
        modelStack.PushMatrix();
        modelStack.Rotate(camera.getCameraYrotation(), 0, 1, 0);
        modelStack.Rotate(camera.getCameraXrotation(), 1, 0, 0);

        modelStack.Rotate(90, 1, 0, 0);
        modelStack.Rotate(60, 0, 1, 0);

        modelStack.Translate(x, y, z);
        modelStack.Rotate(180, 1, 0, 0);
        if (rotate_x != 0)
        {
            modelStack.Rotate(rotate_x, 1, 0, 0);
        }
        if (rotate_y != 0)
        {
            modelStack.Rotate(rotate_y, 0, 1, 0);
        }
        if (rotate_z != 0)
        {
            modelStack.Rotate(rotate_z, 0, 0, 1);
        }
        modelStack.Scale(size, size, size);
        //renderMesh(meshList[GEO_AXES], false);
        renderMesh(mesh, true);

        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }
    
}

/****************************************************************************/
/*!
\brief
render chunfei npc
*/
/****************************************************************************/

void sceneSP2::renderChunFei()
{
    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "robothead") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(-90, 0, 1, 0);
            modelStack.Rotate(headrotating, 1, 0, 0);
            modelStack.Scale(3,3,3);
            renderMesh(meshList[GEO_ROBOTHEAD], true);
            modelStack.PopMatrix();
            break;
        }
    }



    modelStack.PushMatrix();
    modelStack.Translate(QUEST3.NPC_getposition_x(), QUEST3.NPC_getposition_y(), QUEST3.NPC_getposition_z());
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(2.5,2.5,2.5);
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
                modelStack.Scale(2,2,2);
				renderMesh(meshList[GEO_SWORD], true);
                modelStack.PopMatrix();
                break;
            }
        }
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

    if ( Three.Item1collected() == true && Quest2_finished == false)
    {
        RenderStuffOnScreen(meshList[GEO_SWORD], "right", 0.3f, -0.75f, 2, -0.65f, 0, 0, 0);
    }
}

/******************************************************************************/
/*!
\brief -
rendering of environment object
*/
/******************************************************************************/

void sceneSP2::populateArea()
{
    //guan hui
    for (auto it : camera.storage_of_objects)
    {
        if (it.getName() == "RandomBox1")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Scale(3, 3, 3);
            renderMesh(meshList[GEO_BOX], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBox2")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(-25, 0, 1, 0);
            modelStack.Scale(2.8f, 2.8f, 2.8f);
            renderMesh(meshList[GEO_BOX], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBox3")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(45, 0, 1, 0);
            modelStack.Scale(3.5f, 3.5f, 3.5f);
            renderMesh(meshList[GEO_BOX], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBox4")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(45, 0, 1, 0);
            modelStack.Scale(3.5f, 3.5f, 3.5f);
            renderMesh(meshList[GEO_BOX], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBarrel1")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            //modelStack.Rotate(45, 0, 1, 0);
            modelStack.Scale(2, 2, 2);
            renderMesh(meshList[GEO_BARREL], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBarrel2")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            //modelStack.Rotate(45, 0, 1, 0);
            modelStack.Scale(2, 2, 2);
            renderMesh(meshList[GEO_BARREL], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBarrel3")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            //modelStack.Rotate(45, 0, 1, 0);
            modelStack.Scale(2, 2, 2);
            renderMesh(meshList[GEO_BARREL], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBarrel4")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            //modelStack.Rotate(45, 0, 1, 0);
            modelStack.Scale(2, 2, 2);
            renderMesh(meshList[GEO_BARREL], true);
            modelStack.PopMatrix();
        }
        if (it.getName() == "RandomBarrel5")
        {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(90, 0, 0, 1);
            modelStack.Rotate(-30, 1, 0, 0);
            modelStack.Scale(2, 2, 2);
            renderMesh(meshList[GEO_BARREL], true);
            modelStack.PopMatrix();
            break;
        }
        
    }
    
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


/******************************************************************************/
/*!
\brief - the logic behind animating of teleporting

\param dt - frame time
*/
/******************************************************************************/
void sceneSP2::animateTeleporting(double& dt) {
    if (camera.position.z != 0 || camera.position.x != 0) {
        camera.setLocation(0, camera.position.y, 0);
    }
    else {
        if (camera.position.y > 30) {
            Application::changeIntoScenario2();
        }
        teleportCoordY = Physics::gravitational_pulled(teleportCoordY, dt, 1.f);
        camera.position.y -= teleportCoordY;
    }
    camera.target = Vector3(sin(Math::DegreeToRadian(camera.getCameraYrotation())) * cos(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.x, -sin(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.y, cos(Math::DegreeToRadian(camera.getCameraYrotation())) * cos(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.z);
    Vector3 view = (camera.target - camera.position).Normalized();
    Vector3 right = view.Cross(camera.defaultUp);
    camera.up = right.Cross(view);
}

/******************************************************************************/
/*!
\brief -
rendering of tutorial
*/
/******************************************************************************/
void sceneSP2::RenderTutorialScreen()
{
    
    if (tutorialscreen == true)
    {
        RenderImageOnScreen(meshList[GEO_TEXT_BOX], 43, 32, 30, 16);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "WASD for movement", Color(0.039f, 0.937f, 0.702f), 2, 15, 19);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Use the mouse to look around", Color(0.039f, 0.937f, 0.702f), 2, 15, 17);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Hold Shift to run", Color(0.039f, 0.937f, 0.702f), 2, 15, 15);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Press T to view this again", Color(0.039f, 0.937f, 0.702f), 2, 15, 13);

    }
}
/******************************************************************************/
/*!
\brief -
rendering minigame pieces & minigame selector
*/
/******************************************************************************/
void sceneSP2::RenderMinigamePieces()
{
    if (MiniGame.minigame_started() == true && 
        MiniGame.result() == false)
    {
        modelStack.PushMatrix();
        RenderImageOnScreen(meshList[GEO_TEXT_BOX], 5, 5, 4, 4);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Arrow keys to navigate the circuit", Color(0.039f, 0.937f, 0.702f), 2, 15, 23);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Press Enter to rotate the selected part", Color(0.039f, 0.937f, 0.702f), 2, 15, 22);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Complete the circuit to move on", Color(0.039f, 0.937f, 0.702f), 2, 15, 21);
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_1], 5, 35, 35, MiniGame.piece1());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_2], 5, 40, 35, MiniGame.piece2());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_3], 5, 45, 35, MiniGame.piece3());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_4], 5, 35, 30, MiniGame.piece4());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_5], 5, 40, 30, MiniGame.piece5());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_6], 5, 45, 30, MiniGame.piece6());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_7], 5, 35, 25, MiniGame.piece7());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_8], 5, 40, 25, MiniGame.piece8());
        RenderMinigameOnScreen(meshList[GEO_MINIGAME_PIECE_9], 5, 45, 25, MiniGame.piece9());
        modelStack.PopMatrix();

        modelStack.PushMatrix();
        if (MiniGame.get_selector_state() == 1)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 35, 35, 0);
        }
        else if (MiniGame.get_selector_state() == 2)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 40, 35, 0);
        }
        else if (MiniGame.get_selector_state() == 3)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 45, 35, 0);
        }
        else if (MiniGame.get_selector_state() == 4)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 35, 30, 0);
        }
        else if (MiniGame.get_selector_state() == 5)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 40, 30, 0);
        }
        else if (MiniGame.get_selector_state() == 6)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 45, 30, 0);
        }
        else if (MiniGame.get_selector_state() == 7)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 35, 25, 0);
        }
        else if (MiniGame.get_selector_state() == 8)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 40, 25, 0);
        }
        else if (MiniGame.get_selector_state() == 9)
        {
            RenderMinigameSelectorOnScreen(meshList[GEO_MINIGAME_SELECTOR], 5, 45, 25, 0);
        }
        modelStack.PopMatrix();
    }
    
}
/******************************************************************************/
/*!
\brief -
rendering of the minigame pieces on screen
*/
/******************************************************************************/
void sceneSP2::RenderMinigameOnScreen(Mesh* mesh, float size, float x, float y, float rotate_x)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -7, 5); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack

    modelStack.Translate(x, y, 0);
    modelStack.Scale(size, size, size);
    modelStack.Rotate(90, 0, -1, 0);
    modelStack.Rotate(rotate_x, -1, 0, 0);
    //renderMesh(meshList[GEO_AXES], false);
    renderMesh(mesh, false);

    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief -
rendering minigame selector on screen
*/
/******************************************************************************/
void sceneSP2::RenderMinigameSelectorOnScreen(Mesh* mesh, float size, float x, float y, float rotate_x)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -7, 5); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack

    modelStack.Translate(x, y, 3);
    modelStack.Scale(size, size, size);
    modelStack.Rotate(90, 0, -1, 0);
    modelStack.Rotate(rotate_x, -1, 0, 0);
    //renderMesh(meshList[GEO_AXES], false);
    renderMesh(mesh, false);

    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}
