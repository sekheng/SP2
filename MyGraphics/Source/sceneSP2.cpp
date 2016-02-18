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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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
	camera.InitObjects("scenario1Driven//");
    camera.camType = Camera3::FIRST_PERSON;

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    meshList[GEO_COMIC_TEXT] = MeshBuilder::GenerateText("comic sans text", 16, 16);
    meshList[GEO_COMIC_TEXT]->textureID = LoadTGA("Image//comicSans.tga");

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light_ball", Color(1,1,1));

    //skybox
    meshList[GEO_SPACE_SKYBOX] = MeshBuilder::GenerateOBJ("space skybox", "OBJ//Space_Skybox.obj");
    meshList[GEO_SPACE_SKYBOX]->textureID = LoadTGA("Image//skybox//Space_Skybox_UV.tga");
    //skybox

	//Cryostasis
	meshList[GEO_CRYOSTASIS] = MeshBuilder::GenerateOBJ("cryostasis", "OBJ//cryostasis.obj");
	meshList[GEO_CRYOSTASIS]->textureID = LoadTGA("Image//cryostasis.tga");

    //User Interface
    meshList[GEO_UI] = MeshBuilder::GenerateOBJ("User Interface", "OBJ//User_Interface.obj");
    meshList[GEO_UI]->textureID = LoadTGA("Image//UI_UV.tga");
    //User Interface
    //Space ground mesh
    meshList[GEO_SPACE_GROUNDMESH] = MeshBuilder::GenerateOBJ("Space ground mesh", "OBJ//Space_groundmesh.obj");
    meshList[GEO_SPACE_GROUNDMESH]->textureID = LoadTGA("Image//Space_groundmesh.tga");
   // meshList[GEO_SPACE_GROUNDMESH]->material = MaterialBuilder::GenerateBlinn();
    //Space ground mesh
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
	//SpaceStationChair
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("Chair", "OBJ//Chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//Chair.tga");
	//SpaceStationTable
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Table", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table.tga");
	//SpaceStationBox
	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("Box", "OBJ//Box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//Box.tga");
	//SpaceStationBox
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//Door.tga");
	//SpaceStationCryostasis
	meshList[GEO_CRYOSTASIS] = MeshBuilder::GenerateOBJ("Cryostasis", "OBJ//cryostasis.obj");
	meshList[GEO_CRYOSTASIS]->textureID = LoadTGA("Image//cryostasis.tga");
	//SpaceStationKeyCard
	meshList[GEO_KEYCARD] = MeshBuilder::GenerateOBJ("KeyCard", "OBJ//KeyCard.obj");
	meshList[GEO_KEYCARD]->textureID = LoadTGA("Image//KeyCard.tga");
	//SpaceStationKeyCard
	meshList[GEO_KEYCARD2] = MeshBuilder::GenerateOBJ("KeyCard2", "OBJ//KeyCard.obj");
	meshList[GEO_KEYCARD2]->textureID = LoadTGA("Image//KeyCard.tga");


    //NPC
    meshList[GEO_NPC1] = MeshBuilder::GenerateOBJ("Najib", "OBJ//android.obj");
    meshList[GEO_NPC1]->textureID = LoadTGA("Image//android.tga");
    //NPC


    meshList[GEO_INVIS_CURSOR] = MeshBuilder::GenerateSphere("invisible cursor", Color(0.5, 0.5, 0.5));


    on_light = true;

    Mtx44 projection;
    projection.SetToPerspective(60.f, static_cast<float>(screenWidth / screenHeight), 0.1f, 20000.f);
    projectionStack.LoadMatrix(projection);

    //initialise camera_position_x and z;
    framePerSecond = 0;
    camera.cursorCoordX = screenWidth / 2;
    camera.cursorCoordY = screenHeight / 2;

	door.Init("Sek heng", Vector3(-30, 0, 40), camera, 5, 5);
	door.getQuestStage();

    //initialise npc
    npc1.Init("Najib",Vector3(2,2,2),5,5,camera,"NPC data//Najib.txt");

    //initialise quest
    test_quest.Init("random quest", camera,Vector3(20,0,20),5,5,Vector3(30,0,30),5,5);
    test_quest.Quest_Taken(true);
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

    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    if (Application::IsKeyPressed('I'))
        light[0].position.z -= (float)(LSPEED * dt);
    if (Application::IsKeyPressed('K'))
        light[0].position.z += (float)(LSPEED * dt);
    if (Application::IsKeyPressed('J'))
        light[0].position.x -= (float)(LSPEED * dt);
    if (Application::IsKeyPressed('L'))
        light[0].position.x += (float)(LSPEED * dt);
    if (Application::IsKeyPressed('O'))
        light[0].position.y -= (float)(LSPEED * dt);
    if (Application::IsKeyPressed('P'))
        light[0].position.y += (float)(LSPEED * dt);

    if (Application::IsKeyPressed('5'))
    {
        on_light = true;
        light[0].color.Set(1, 1, 1);
    }
    if (Application::IsKeyPressed('6'))
    {
        on_light = false;
        light[0].color.Set(0, 0, 0);
    }

    if (Application::IsKeyPressed('7'))
    {
        light[0].type = Light::LIGHT_POINT;
        glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    }
    if (Application::IsKeyPressed('8'))
    {
        light[0].type = Light::LIGHT_DIRECTIONAL;
        glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    }
    if (Application::IsKeyPressed('9'))
    {
        light[0].type = Light::LIGHT_SPOT;
        glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    }

    //transit scene
    if (Application::IsKeyPressed(VK_NUMPAD2)) {
        Application::changeIntoScenario2();
    }
    if (Application::IsKeyPressed(VK_NUMPAD3)) {
        Application::changeIntoScenario3();
    }
    //transit scene

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
	modelStack.PushMatrix();
	modelStack.Translate(-275, 0, 290);
	modelStack.Scale(20,10,10);
	renderMesh(meshList[GEO_STATION], false);
	modelStack.PopMatrix();

	//Table and chair set 1
	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 290);
	modelStack.Scale(1.5, 1.5, 1.5);
	renderMesh(meshList[GEO_CHAIR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180,0,1,0);
	modelStack.Translate(300, 0, -295);
	modelStack.Scale(1.5,1.5,1.5);
	renderMesh(meshList[GEO_CHAIR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 293);
	modelStack.Scale(5, 4, 5);
	renderMesh(meshList[GEO_TABLE], false);
	modelStack.PopMatrix();

	//Table and chair set2 
	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 303);
	modelStack.Scale(1.5, 1.5, 1.5);
	renderMesh(meshList[GEO_CHAIR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(300, 0, -307);
	modelStack.Scale(1.5, 1.5, 1.5);
	renderMesh(meshList[GEO_CHAIR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 305);
	modelStack.Scale(5, 4, 5);
	renderMesh(meshList[GEO_TABLE], false);
	modelStack.PopMatrix();


	//Table and chair set3 
	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 280);
	modelStack.Scale(1.5, 1.5, 1.5);
	renderMesh(meshList[GEO_CHAIR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(300, 0, -284);
	modelStack.Scale(1.5, 1.5, 1.5);
	renderMesh(meshList[GEO_CHAIR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-300, 0, 282);
	modelStack.Scale(5, 4, 5);
	renderMesh(meshList[GEO_TABLE], false);
	modelStack.PopMatrix();


	//Box
	modelStack.PushMatrix();
	modelStack.Translate(-307, 0, 270);
	modelStack.Scale(5, 5, 5);
	renderMesh(meshList[GEO_BOX], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	renderMesh(meshList[GEO_BOX], false);
	modelStack.PopMatrix();

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
	modelStack.PushMatrix();
	modelStack.Translate(-270, 0, 260);
	modelStack.Scale(5, 3, 6);
	renderMesh(meshList[GEO_DOOR], false);
	if (door.getQuestStage() == 1)
	{
		RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Press E to open door", Color(0, 1, 0), 3, 10, 10);
	}
	else if (door.getQuestStage() == 2)
	{
		RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Find the damn key for your asshole", Color(0, 1, 0), 3, 8, 10);
	}
	modelStack.PopMatrix();

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
				RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Press E to get card", Color(0, 1, 0), 3, 8, 10);
			}
			modelStack.PopMatrix();
		}
		if (door.getCard2() == 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-296, 0, 292);
			modelStack.Scale(1, 1, 1);
			renderMesh(meshList[GEO_KEYCARD2], false);
			if (door.getCardText() == true)
			{
				RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Press E to get card", Color(0, 1, 0), 3, 8, 10);
			}
			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(280, 0, -315);
	modelStack.Scale(1, 1, 1);
	renderMesh(meshList[GEO_CRYOSTASIS], false);
	modelStack.PopMatrix();

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
    modelStack.Scale(20, 1, 20);
    Rendergroundmesh();
    modelStack.PopMatrix();
    //render ground mesh

	//render cryostasis
	RenderCryostasis();

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

    modelStack.PushMatrix();
    RenderNPC();
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    RenderQuestObjects();
    modelStack.PopMatrix();

    //****************************************************************************//
    //On screen objects
    //****************************************************************************//
    modelStack.PushMatrix();
    //scale, translate, rotate
    modelStack.Scale(20, 20, 1);
    RenderText(meshList[GEO_COMIC_TEXT], "Hello World", Color(0, 1, 0));
    modelStack.PopMatrix();


    modelStack.PushMatrix();
    RenderUserInterface(meshList[GEO_UI], 1, 40, 40);
    modelStack.PopMatrix();

    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Hello Screen", Color(0, 1, 0), 4, 0.5, 1.5);

    modelStack.PushMatrix();
    
    RenderUserInterface(meshList[GEO_UI], 1, 40, 40);
    
    
    modelStack.PopMatrix();

	RenderStation();

    modelStack.PushMatrix();
    modelStack.Translate(camera.getCrossHairX(), camera.getCrossHairY(), camera.getCrossHairZ());
    renderMesh(meshList[GEO_INVIS_CURSOR], false);
    modelStack.PopMatrix();

    
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Hello Screen", Color(0, 1, 0), 4, 0.5f, 1.5f);
    std::stringstream ss;
    ss << "FPS : " << static_cast<int>(framePerSecond);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 1.8f, 1.25f, 16.5f);
    
    std::stringstream connectPosX;

    connectPosX << std::fixed << std::setprecision(2) << "X : " << camera.getCameraXcoord();
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosX.str(), Color(0, 1, 0), 1.8f, 1.5f, 21.2f);

    std::stringstream connectPosZ;
    connectPosZ << std::fixed << std::setprecision(2) << "Z : " << camera.getCameraZcoord();
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosZ.str(), Color(0, 1, 0), 1.8f, 1.5f, 19.f);
    
    //****************************************************************************//
    //On screen objects
    //****************************************************************************//

}


/******************************************************************************/
/*!
\brief - 
cleans up the scene
*/
/******************************************************************************/
void sceneSP2::Exit()
{
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



void sceneSP2::RenderCryostasis()
{
	modelStack.PushMatrix();
	renderMesh(meshList[GEO_CRYOSTASIS], false);
	modelStack.PopMatrix();
}
void sceneSP2::RenderNPC()
{
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
    /*if (npc1.interaction() == true)
    {
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], npc1.getDialogue(), Color(0, 1, 0),3, 10, 10);
    }*/
    modelStack.PopMatrix();
}

void sceneSP2::RenderQuestObjects()
{
    //text
    if (test_quest.Result() == true)
    {
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Quest Complete!!", Color(0, 1, 0), 3, 10, 10);
    }
    else
    {
        if (test_quest.FirstObject_taken() == false )
        {
            //object 1
            modelStack.PushMatrix();
            modelStack.Translate(test_quest.get_object1_x(), 0, test_quest.get_object1_z());
            renderMesh(meshList[GEO_SCREWDRIVER], false);
            modelStack.PopMatrix();
        }
        if (test_quest.SecondObject_taken() == false)
        {
            //object 2
            modelStack.PushMatrix();
            modelStack.Translate(test_quest.get_object2_x(), 0, test_quest.get_object2_z());
            renderMesh(meshList[GEO_CONTAINER], false);
            modelStack.PopMatrix();
        }
    }
    

        
    
}