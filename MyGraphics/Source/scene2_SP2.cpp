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
#include <string>

/******************************************************************************/
/*!
\brief -
constructor with 2 arguments to store the width and height of the screen

\param screenwidth - width of the screen
\param screenheight - height of the screen
*/
/******************************************************************************/
scene2_SP2::scene2_SP2(float screenwidth, float screenheight)
    : screenWidth(screenwidth), screenHeight(screenheight)
{
}
/******************************************************************************/
/*!
\brief - destructor
*/
/******************************************************************************/
scene2_SP2::~scene2_SP2()
{
}
/******************************************************************************/
/*!
\brief -
initializing whatever is needed for the scene
*/
/******************************************************************************/
void scene2_SP2::Init()
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

	//deadpool light
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	//deadpool light

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    glUseProgram(m_programID);

    glUniform1i(m_parameters[U_NUMLIGHTS], 2);

    light[0].type = Light::LIGHT_DIRECTIONAL;
    light[0].position.Set(0, 70, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 1;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;
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
	//glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	//deadpool light
	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 70, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 10;
	light[1].kC = 1.f;
	light[1].kL = 0.001f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(25));
	light[1].cosInner = cos(Math::DegreeToRadian(25));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

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
    camera.Init("cameraDriven//scene2.txt");
    camera.InitObjects("scenario3Driven//all_static_OBJ.txt");
    camera.camType = Camera3::FIRST_PERSON;

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    meshList[GEO_COMIC_TEXT] = MeshBuilder::GenerateText("comic sans text", 16, 16);
    meshList[GEO_COMIC_TEXT]->textureID = LoadTGA("Image//comicSans.tga");

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light_ball", Color(1, 1, 1));

	//skybox
	meshList[GEO_PLANET_SKYBOX] = MeshBuilder::GenerateOBJ("planet skybox", "OBJ//Planet_skybox.obj");
	meshList[GEO_PLANET_SKYBOX]->textureID = LoadTGA("Image//skybox//Planet_skybox_UV.tga");
	//skybox

	//LandVehicle
	meshList[GEO_LANDVEHICLE] = MeshBuilder::GenerateOBJ("landvehicle", "OBJ//LandVehicle.obj");
	meshList[GEO_LANDVEHICLE]->textureID = LoadTGA("Image//LandVehicle.tga");

	//FlyingVehicle
	meshList[GEO_FLYINGVEHICLE] = MeshBuilder::GenerateOBJ("flyingvehicle", "OBJ//FlyingVehicle.obj");
	meshList[GEO_FLYINGVEHICLE]->textureID = LoadTGA("Image//FlyingVehicle.tga");
	
	//Robot
	meshList[GEO_ROBOT] = MeshBuilder::GenerateOBJ("robot", "OBJ//Robocop_Black.obj");
	meshList[GEO_ROBOT]->textureID = LoadTGA("Image//Robocop_Black_D.tga");

	//spaceship
	meshList[GEO_SPACESHUTTLE] = MeshBuilder::GenerateOBJ("spaceshuttle", "OBJ//SpaceShuttle.obj");
	meshList[GEO_SPACESHUTTLE]->textureID = LoadTGA("Image//Shuttle_UV.tga");

	//vaultcube
	meshList[GEO_VAULTCUBE] = MeshBuilder::GenerateOBJ("vaultcube", "OBJ//vaultcube.obj");
	meshList[GEO_VAULTCUBE]->textureID = LoadTGA("Image//vaultnew_UV.tga");

	//vaultdoor
	meshList[GEO_VAULTDOOR] = MeshBuilder::GenerateOBJ("vaultdoor", "OBJ//vaultdoor.obj");
	meshList[GEO_VAULTDOOR]->textureID = LoadTGA("Image//vaultnewest.tga");

	//vaultwheel
	meshList[GEO_VAULTWHEEL] = MeshBuilder::GenerateOBJ("vaultwheel", "OBJ//vaultwheel.obj");
	meshList[GEO_VAULTWHEEL]->textureID = LoadTGA("Image//vaultnewest.tga");

	//vaultstick
	meshList[GEO_VAULTSTICK] = MeshBuilder::GenerateOBJ("vaultstick", "OBJ//vaultstick.obj");
	meshList[GEO_VAULTSTICK]->textureID = LoadTGA("Image//vaultnewest.tga");

	//numpad
	meshList[GEO_NUMPAD] = MeshBuilder::GenerateOBJ("numpad", "OBJ//numberpad.obj");
	meshList[GEO_NUMPAD]->textureID = LoadTGA("Image//number2_UV.tga");
	//numroll
	meshList[GEO_NUMROLL] = MeshBuilder::GenerateOBJ("numroll", "OBJ//numberroll.obj");
	meshList[GEO_NUMROLL]->textureID = LoadTGA("Image//number2_UV.tga");

	//Menu
	meshList[GEO_ARROW] = MeshBuilder::GenerateOBJ("arrow", "OBJ//arrow.obj");
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//arrow_UV.tga");

	//satellite
	meshList[GEO_SATELLITEHEAD] = MeshBuilder::GenerateOBJ("satellitehead", "OBJ//satelliteHead.obj");
	meshList[GEO_SATELLITEHEAD]->textureID = LoadTGA("Image//Satellite_UV.tga");

	meshList[GEO_SATELLITEBODY] = MeshBuilder::GenerateOBJ("satellitebody", "OBJ//satellitebody.obj");
	meshList[GEO_SATELLITEBODY]->textureID = LoadTGA("Image//Satellite_UV.tga");

	//diamond
	meshList[GEO_BIGDIAMOND] = MeshBuilder::GenerateOBJ("bigdiamond", "OBJ//bigdiamond.obj");
	meshList[GEO_BIGDIAMOND]->textureID = LoadTGA("Image//diamond.tga");

	meshList[GEO_SMALLDIAMOND] = MeshBuilder::GenerateOBJ("smalldiamond", "OBJ//smalldiamond.obj");
	meshList[GEO_SMALLDIAMOND]->textureID = LoadTGA("Image//diamond.tga");

	//interaction diamond
	meshList[GEO_BIGDIAMOND2] = MeshBuilder::GenerateOBJ("bigdiamond", "OBJ//bdiamond.obj");
	meshList[GEO_BIGDIAMOND2]->textureID = LoadTGA("Image//diamond.tga");

	meshList[GEO_SMALLDIAMOND2] = MeshBuilder::GenerateOBJ("smalldiamond", "OBJ//sdiamond.obj");
	meshList[GEO_SMALLDIAMOND2]->textureID = LoadTGA("Image//diamond.tga");

	//npc
	meshList[GEO_NPCUPPER] = MeshBuilder::GenerateOBJ("npc", "OBJ//scene3NPCupper.obj");
	meshList[GEO_NPCUPPER]->textureID = LoadTGA("Image//scene3NPC.tga");

	meshList[GEO_NPCLOWER] = MeshBuilder::GenerateOBJ("npc", "OBJ//scene3NPClower.obj");
	meshList[GEO_NPCLOWER]->textureID = LoadTGA("Image//scene3NPC.tga");

	meshList[GEO_BOXES] = MeshBuilder::GenerateOBJ("npc", "OBJ//boxes9.obj");
	meshList[GEO_BOXES]->textureID = LoadTGA("Image//boxes9.tga");

	meshList[GEO_NORMALBOXES] = MeshBuilder::GenerateOBJ("npc", "OBJ//boxes9.obj");
	meshList[GEO_NORMALBOXES]->textureID = LoadTGA("Image//normalboxes.tga");

	//plane
	//meshList[GEO_PLANE] = MeshBuilder::GenerateOBJ("plane", "OBJ//plane.obj");
	//meshList[GEO_PLANE]->textureID = LoadTGA("Image//plane.tga");

	//User Interface
	meshList[GEO_UI] = MeshBuilder::GenerateOBJ("User Interface", "OBJ//User_Interface.obj");
	meshList[GEO_UI]->textureID = LoadTGA("Image//UI_UV.tga");
	//User Interface

	//GroundMesh
    meshList[GEO_PLANET_GROUND] = MeshBuilder::GenerateOBJ("Planet ground mesh", "OBJ//planet_ground_mesh.obj");
    meshList[GEO_PLANET_GROUND]->textureID = LoadTGA("Image//planet_ground_mesh.tga");
    //GroundMesh
    
    //DeadPOOL
    meshList[GEO_DEADPOOL] = MeshBuilder::GenerateOBJ("Dead Pool", "OBJ//DeadPool.obj");
    meshList[GEO_DEADPOOL]->textureID = LoadTGA("Image//DeadPool.tga");
    on_light = true;

    Mtx44 projection;
    projection.SetToPerspective(60.f, static_cast<float>(screenWidth / screenHeight), 0.1f, 20000.f);
    projectionStack.LoadMatrix(projection);

    framePerSecond = 0;
    camera.cursorCoordX = screenWidth / 2;
    camera.cursorCoordY = screenHeight / 2;

    Rot_Civ_.init("rot_civ//rot_civ_stuff.txt");
    Rot_Civ_.InitDialogues("rot_civ//rot_civ_dialogues.txt", camera);
    camera.storage_of_objects.push_back(Rot_Civ_);  //This line is just for the camera to recognise its bound.

	//vault animation
	wheelturn = stickpush = dooropen = satelliterotate = bigdiamondtranslate = bigdiamondrotate 
	= smalldiamondrotate = smalldiamondtranslate = NPCrotate= NPCrotate2 = boxesappear = boxestransfer
	= boxesappear2 = change = change2= NPCrotate3= boxesappear3= change3=false;
	wheelturning = stickpushing = dooropening = satelliterotating = bigdiamondtranslating = bigdiamondrotating 
	= smalldiamondrotating = smalldiamondtranslating = NPCrotating = NPCrotating2 = boxesrotating 
	= boxesrotating2 = NPCrotating3= boxesrotating3=0;
	
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "numpad") {
			Numpad.Init(camera, Vector3(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ()));
			break;
		}
	}

	robotNPC1.Init("robotNPC1", 5, Vector3(0, 0, -300), 40, 40, camera, "NPC data//NPC_4.txt");
	robotNPC2.Init("robotNPC2", 6, Vector3(800, 0, 800), 40, 40, camera, "NPC data//NPC_5.txt");
	//diamondNPC.Init("diamondNPC", 6, Vector3(900,200,800), 80, 80, camera, "NPC data//NPC_5.txt");

    //text box
    meshList[GEO_TEXT_BOX] = MeshBuilder::GenerateQuad("text box", Color(1, 1, 1));
    meshList[GEO_TEXT_BOX]->textureID = LoadTGA("Image//textbox.tga");
    //text box

    //ending screen
    meshList[GEO_ENDING_SCREEN] = MeshBuilder::GenerateQuad("ending screen", Color(0, 0, 0));
    meshList[GEO_ENDING_SCREEN]->textureID = LoadTGA("Image//ending_screen.tga");
    //ending screen

    //Beginning cinematic
    beginEnding = false;
    beginIamYourFather = false;
    endingTime = 0;
    moveToDeadPoolZ = 0;
    sizeofEndingScreen = 1;

    //credits
    creditRolling.initCredit("scenario3Driven//credits.txt");
    //credits
    //Beginning cinematic

	//dooropening = 89;
}

/******************************************************************************/
/*!
\brief -
where the logic of the game is, and update

\param dt - time frame
*/
/******************************************************************************/
void scene2_SP2::Update(double dt)
{
    VaultAnimation(dt);
    Numpad.Update(dt);
    Numpad.NumpadProgram(dt);
    Rot_Civ_.update(dt);
	SatelliteAnimation(dt);
	diamondAnimation(dt);
	NPCAnimation(dt);
	BoxesAnimation(dt);
	robotNPC1.update(dt);
	robotNPC2.update(dt);
	//diamondNPC.update(dt);
    framePerSecond = 1 / dt;
    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    if (Application::IsKeyPressed(VK_NUMPAD1)) {
        Application::changeIntoScenario1();
    }
    if (Application::IsKeyPressed(VK_NUMPAD2)) {
        Application::changeIntoScenario2();
    }

    if (Numpad.NumpadVerify() == true) {
        beginEnding = true;
    }
    if (dooropening >= 90) {
        beginIamYourFather = true;
    }

    if (beginEnding) {
        Ending(dt);
    }
    else {
        camera.Update(dt);
    }

    if (creditRolling.goRollCredit())
    {
        creditRolling.updateCredit(dt);
    }
}

/******************************************************************************/
/*!
\brief - rendering of the meshes

\param mesh - the specific mesh
\param enableLight - to enable lighting on the object
*/
/******************************************************************************/
void scene2_SP2::renderMesh(Mesh *mesh, bool enableLight)
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
\brief -
where the rendering of all the stuff we needed will be here
*/
/******************************************************************************/
void scene2_SP2::Render()
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
        //renderMesh(meshList[GEO_LIGHTBALL], false);
        modelStack.PopMatrix();
    }

	//deadpool light
	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (on_light) {
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		modelStack.PushMatrix();
		modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		//renderMesh(meshList[GEO_LIGHTBALL], false);
		modelStack.PopMatrix();
	}
	//deadpool light

    renderMesh(meshList[GEO_AXES], false);

	//render ground
	modelStack.PushMatrix();
	modelStack.Scale(100, 1, 100);
	renderMesh(meshList[GEO_PLANET_GROUND], false);
	modelStack.PopMatrix();

	//render skybox 
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(300, 300, 300);
	RenderSkybox();
	modelStack.PopMatrix();

	//render robot
	RenderRobot();

	//render flyingvehicle
	RenderFlyingVehicle();

	//render landingvehicle
	RenderLandingVehicle();

	//render spaceshuttle
	RenderSpaceShuttle();

	//render vault
	RenderVault();
	
	//render numpad
	RenderNumpad();

	//render satellite
	RenderSatellite();

	//render rock
	RenderDiamond();
	
    //rendering DeadPOOL
    renderDeadPool();
    //rendering DeadPOOL

	//render npc
	RenderNPC();

	//render boxes
	RenderBoxes();
	
	//render plane
	//RenderPlane();

	//modelStack.PushMatrix();
	//modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	//modelStack.Scale(3, 3, 3);
	//renderMesh(meshList[GEO_LIGHTBALL], false);
	//modelStack.PopMatrix();
	

    if (beginIamYourFather == false && Numpad.NumpadRenderOnScreen())
	{
		RenderNumPadOnScreen(meshList[GEO_NUMPAD], 16, 40, 30, 0, 0,1,0);
		RenderNumPadOnScreen(meshList[GEO_NUMROLL], 15, 40, 30, 2, 0 + Numpad.getfirstrotate(),1, 0);
		RenderNumPadOnScreen(meshList[GEO_NUMROLL], 15, 55, 30, 2, 0 + Numpad.getsecondrotate(), 1, 0);
		RenderNumPadOnScreen(meshList[GEO_NUMROLL], 15, 70, 30, 2, 0 + Numpad.getthirdrotate(), 1, 0);
		RenderNumPadOnScreen(meshList[GEO_NUMROLL], 15, 85, 30, 2, 0 + Numpad.getfourthrotate(), 1, 0);
		RenderNumPadOnScreen(meshList[GEO_ARROW], 3, Numpad.getarrowposition(), 3, 7, -90, 0, 1); //19.5 34.5 49.5 64.5
	}

	if (Numpad.displayerror()) // if input wrong, display "Try Again!"
	{
			RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Try Again!", Color(1, 0, 0), 5, 6, 8);
	}
	//interaction text
	if (Numpad.interactiontext()) // "Press 'C' to interact" appear
	{
		modelStack.PushMatrix();
		modelStack.Translate(5, 10, 40);
		modelStack.Scale(3, 3, 3);
		RenderText(meshList[GEO_COMIC_TEXT], "Press 'C' to interact", Color(0, 1, 0));
		modelStack.PopMatrix();
	}
    if (beginIamYourFather == true && moveToDeadPoolZ < -135) {
        renderEndingScreen();
    }

    rollingCredits();

	std::stringstream connectPosX;
    connectPosX << std::fixed << std::setprecision(2) << "X : " << camera.getCameraXcoord();
	RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosX.str(), Color(0, 1, 0), 1.8f, 1.25f, 19.f);

    std::stringstream connectPosZ;
    connectPosZ << std::fixed << std::setprecision(2) << "Z : " << camera.getCameraZcoord();
	RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosZ.str(), Color(0, 1, 0), 1.8f, 1.25f, 16.5f);

    std::stringstream ss;
    ss << "FPS : " << static_cast<int>(framePerSecond);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 4, 0.5, 0.5);

	std::stringstream input;
	input << "FPS : " << robotNPC2.get_LineOfDialogue(); /*<< Numpad.getdigit2() << Numpad.getdigit3() << Numpad.getdigit4();*/
	RenderTextOnScreen(meshList[GEO_COMIC_TEXT], input.str(), Color(0, 1, 0), 15, 0.5, 0.5);

}

/******************************************************************************/
/*!
\brief -
cleans up the scene
*/
/******************************************************************************/
void scene2_SP2::Exit()
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
void scene2_SP2::RenderText(Mesh* mesh, std::string text, Color color)
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
void scene2_SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void scene2_SP2::RenderImageOnScreen(Mesh* mesh, float size, float x, float y) {
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

void scene2_SP2::RenderNumPadOnScreen(Mesh* mesh, float size, float x, float y, float z, float rotate, float rotatex, float rotatey) {
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

	modelStack.Translate(x, y, z);
	modelStack.Scale(size, size+15, size);
	modelStack.Rotate(rotate, rotatex, rotatey, 0);
	renderMesh(mesh, false);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void scene2_SP2::RenderSkybox()
{
	modelStack.PushMatrix();
	renderMesh(meshList[GEO_PLANET_SKYBOX], false);
	modelStack.PopMatrix();
}

void scene2_SP2::RenderUserInterface(Mesh* mesh, float size, float x, float y)
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
void scene2_SP2::RenderRobot()
{
    modelStack.PushMatrix();
    modelStack.Translate(Rot_Civ_.getObjectposX(), Rot_Civ_.getObjectposY(), Rot_Civ_.getObjectposZ());
	modelStack.Scale(7, 7, 7);
	renderMesh(meshList[GEO_ROBOT], true);
	modelStack.PopMatrix();

    if (Rot_Civ_.interaction() == false) {
        renderDialogueBox(Rot_Civ_.getName(), Rot_Civ_.returnDialogue());
    }
}

void scene2_SP2::RenderFlyingVehicle()
{
	for (auto it : camera.storage_of_objects)
	{
		if (it.getName() == "flyingvehicle")
		{
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			//modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(30, 30, 30);
			renderMesh(meshList[GEO_FLYINGVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void scene2_SP2::RenderLandingVehicle()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "spacevehicle") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_LANDVEHICLE], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void scene2_SP2::RenderSpaceShuttle()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "spaceshuttle") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(50, 60, 50);
			renderMesh(meshList[GEO_SPACESHUTTLE], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void scene2_SP2::RenderVault()
{
	for (auto it : camera.storage_of_objects) {
		
			if (it.getName() == "vaultcube") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(7, 3, 3);
				renderMesh(meshList[GEO_VAULTCUBE], true);
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {
			if (it.getName() == "vaultdoor") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()+45, it.getObjectposY()+7, it.getObjectposZ());
				modelStack.Rotate(dooropening, 0, 1, 0);
				//renderMesh(meshList[GEO_LIGHTBALL], true);

				modelStack.PushMatrix();
				modelStack.Translate(-45, -7, 0);
				modelStack.Rotate(180, 0, 1, 0);
				
				modelStack.Scale(7, 3, 3);
				renderMesh(meshList[GEO_VAULTDOOR], true);
				modelStack.PopMatrix();
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {
			if (it.getName() == "vaultwheel") {

				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()+61, it.getObjectposY()+7, it.getObjectposZ()-10);
				modelStack.Rotate(dooropening, 0, 1, 0);
				//renderMesh(meshList[GEO_LIGHTBALL], true);

				modelStack.PushMatrix();
				modelStack.Translate(-61, -7, 10);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Rotate(wheelturning, 0, 0, 1);
				modelStack.Scale(3, 3, 3);
				renderMesh(meshList[GEO_VAULTWHEEL], true);
				modelStack.PopMatrix();
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {
			if (it.getName() == "vaultstick") {

				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()+33 + stickpushing, it.getObjectposY()-16, it.getObjectposZ()-5);
				modelStack.Rotate(dooropening, 0, 1, 0);
				//renderMesh(meshList[GEO_LIGHTBALL], false);

				modelStack.PushMatrix();
				modelStack.Translate(-33, 16, 5);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(5, 3, 3);
				renderMesh(meshList[GEO_VAULTSTICK], true);
				modelStack.PopMatrix();
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {
			if (it.getName() == "vaultstick2") {

				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()+33 + stickpushing, it.getObjectposY()+16, it.getObjectposZ()-5);
				modelStack.Rotate(dooropening, 0, 1, 0);
				//renderMesh(meshList[GEO_LIGHTBALL], false);

				modelStack.PushMatrix();
				modelStack.Translate(-33, -16, 5);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Scale(5, 3, 3);
				renderMesh(meshList[GEO_VAULTSTICK], true);
				modelStack.PopMatrix();
				modelStack.PopMatrix();
				break;
			}
		}
	}

void scene2_SP2::RenderNumpad()
{
	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "numpad") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX()+23, it.getObjectposY(), it.getObjectposZ()-5);
			modelStack.Rotate(dooropening, 0, 1, 0);

			modelStack.PushMatrix();
			//modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Translate(-23, 0, 5);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_NUMPAD], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "numroll") {

			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 25, it.getObjectposY(), it.getObjectposZ() - 6);
			modelStack.Rotate(dooropening, 0, 1, 0);
			//renderMesh(meshList[GEO_LIGHTBALL], false);

			modelStack.PushMatrix();
			modelStack.Translate(-25, 0, 6);
			modelStack.Rotate(Numpad.getfirstrotate(), 1, 0, 0);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_NUMROLL], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "numroll") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 25, it.getObjectposY(), it.getObjectposZ() - 6);
			modelStack.Rotate(dooropening, 0, 1, 0);
			//renderMesh(meshList[GEO_LIGHTBALL], false);

			modelStack.PushMatrix();
			modelStack.Translate(-15, 0, 6);
			//modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(Numpad.getsecondrotate(), 1, 0, 0);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_NUMROLL], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "numroll") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 25, it.getObjectposY(), it.getObjectposZ() - 6);
			modelStack.Rotate(dooropening, 0, 1, 0);
			//renderMesh(meshList[GEO_LIGHTBALL], false);

			modelStack.PushMatrix();
			modelStack.Translate(-5, 0, 6);
			//modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(Numpad.getthirdrotate(), 1, 0, 0);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_NUMROLL], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {
		if (it.getName() == "numroll") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 25, it.getObjectposY(), it.getObjectposZ() - 6);
			modelStack.Rotate(dooropening, 0, 1, 0);
			//renderMesh(meshList[GEO_LIGHTBALL], false);

			modelStack.PushMatrix();
			modelStack.Translate(5, 0, 6);
			//modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(Numpad.getfourthrotate(), 1, 0, 0);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_NUMROLL], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
	}

}

void scene2_SP2::RenderArrow()
{
	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "arrow") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(10, 10, 10);
			renderMesh(meshList[GEO_ARROW], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void scene2_SP2::RenderSatellite()
{

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "satellitehead") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(-135, 0, 1, 0);
			modelStack.Rotate(satelliterotating, 0, 1, 0);
			modelStack.Scale(7, 7, 7);
			renderMesh(meshList[GEO_SATELLITEHEAD], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "satellitebody") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(7, 7, 7);
			renderMesh(meshList[GEO_SATELLITEBODY], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "satellitehead2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(-60, 0, 1, 0);
			modelStack.Rotate(satelliterotating, 0, 1, 0);
			modelStack.Scale(7, 7, 7);
			renderMesh(meshList[GEO_SATELLITEHEAD], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "satellitebody2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(7, 7, 7);
			renderMesh(meshList[GEO_SATELLITEBODY], true);
			modelStack.PopMatrix();
			break;
		}
	}
}

void scene2_SP2::RenderDiamond()
{
	for (int i = 0; i <= 1599; i += 533)//front diamonds
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "bigdiamond") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()+i, it.getObjectposY()+bigdiamondtranslating, it.getObjectposZ());
				modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				renderMesh(meshList[GEO_BIGDIAMOND], true);
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "smalldiamond") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()+i, it.getObjectposY()+smalldiamondtranslating, it.getObjectposZ());
				modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				renderMesh(meshList[GEO_SMALLDIAMOND], true);
				modelStack.PopMatrix();
				break;
			}
		}

	}

	for (int i = 0; i <= 1599; i += 533)//back diamonds
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "bigdiamond") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX() + i, it.getObjectposY() + bigdiamondtranslating, it.getObjectposZ() + 2200);
				modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				renderMesh(meshList[GEO_BIGDIAMOND], true);
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "smalldiamond") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX() + i, it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ() + 2200);
				modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				renderMesh(meshList[GEO_SMALLDIAMOND], true);
				modelStack.PopMatrix();
				break;
			}
		}

	}

	for (int i = 533; i <= 1599; i += 533)//left diamonds
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "bigdiamond") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX()-300, it.getObjectposY() + bigdiamondtranslating, it.getObjectposZ() + i);
				modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				renderMesh(meshList[GEO_BIGDIAMOND], true);
				modelStack.PopMatrix();
				break;
			}
		}

		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "smalldiamond") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX() - 300, it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ() + i);
				modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
				modelStack.Scale(25, 25, 25);
				renderMesh(meshList[GEO_SMALLDIAMOND], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}

	//for (int i = 533; i <= 1599; i += 533)//right diamonds
	//{
	//	for (auto it : camera.storage_of_objects) {

	//		if (it.getName() == "bigdiamond") {
	//			modelStack.PushMatrix();
	//			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + bigdiamondtranslating, it.getObjectposZ() + i);
	//			modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
	//			modelStack.Scale(25, 25, 25);
	//			renderMesh(meshList[GEO_BIGDIAMOND], true);
	//			modelStack.PopMatrix();
	//			break;
	//		}
	//	}

	//	for (auto it : camera.storage_of_objects) {

	//		if (it.getName() == "smalldiamond") {
	//			modelStack.PushMatrix();
	//			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ() + i);
	//			modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
	//			modelStack.Scale(25, 25, 25);
	//			renderMesh(meshList[GEO_SMALLDIAMOND], true);
	//			modelStack.PopMatrix();
	//			break;
	//		}
	//	}
	//}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "bigdiamond") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + bigdiamondtranslating, it.getObjectposZ() + 533);
			modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
			modelStack.Scale(25, 25, 25);
			renderMesh(meshList[GEO_BIGDIAMOND], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "smalldiamond") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ() + 533);
			modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
			modelStack.Scale(25, 25, 25);
			renderMesh(meshList[GEO_SMALLDIAMOND], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "bigdiamond") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + bigdiamondtranslating, it.getObjectposZ() + 1066);
			modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
			modelStack.Scale(25, 25, 25);
			renderMesh(meshList[GEO_BIGDIAMOND2], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "smalldiamond") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ() + 1066);
			modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
			modelStack.Scale(25, 25, 25);
			renderMesh(meshList[GEO_SMALLDIAMOND2], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "bigdiamond") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + bigdiamondtranslating, it.getObjectposZ() + 1599);
			modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
			modelStack.Scale(25, 25, 25);
			renderMesh(meshList[GEO_BIGDIAMOND], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "smalldiamond") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX() + 1900, it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ() + 1599);
			modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
			modelStack.Scale(25, 25, 25);
			renderMesh(meshList[GEO_SMALLDIAMOND], true);
			modelStack.PopMatrix();
			break;
		}
	}

	////interactable diamonds
	//for (auto it : camera.storage_of_objects) {

	//	if (it.getName() == "bigdiamond2") {
	//		modelStack.PushMatrix();
	//		modelStack.Translate(diamondNPC.NPC_getposition_x(), diamondNPC.NPC_getposition_y() + bigdiamondtranslating, diamondNPC.NPC_getposition_z());
	//		modelStack.Rotate(bigdiamondrotating, 0, 1, 0);
	//		modelStack.Scale(25,25,25);
	//		renderMesh(meshList[GEO_BIGDIAMOND], true);
	//		if (diamondNPC.interaction() == true)
	//		{
	//			if (!Application::IsKeyPressed('E'))
	//			{
	//				renderDialogueBox("Cursed Diamond", diamondNPC.getDialogue(true));
	//			}
	//			else
	//			{
	//				renderDialogueBox("Cursed Diamond", diamondNPC.getDialogue(false));
	//			}

	//		}
	//		modelStack.PopMatrix();
	//		break;
	//	}
	//}

	//for (auto it : camera.storage_of_objects) {

	//	if (it.getName() == "smalldiamond2") {
	//		modelStack.PushMatrix();
	//		modelStack.Translate(it.getObjectposX(), it.getObjectposY() + smalldiamondtranslating, it.getObjectposZ());
	//		modelStack.Rotate(smalldiamondrotating, 0, 1, 0);
	//		modelStack.Scale(25,25,25);
	//		renderMesh(meshList[GEO_SMALLDIAMOND], true);
	//		modelStack.PopMatrix();
	//		break;
	//	}
	//}
}

void scene2_SP2::RenderNPC()
{
	//npc1,2
	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "npcupper") {
			modelStack.PushMatrix();
			//modelStack.Translate(it.getObjectposX(), it.getObjectposY() , it.getObjectposZ());
			modelStack.Translate(robotNPC1.NPC_getposition_x(), robotNPC1.NPC_getposition_y(), robotNPC1.NPC_getposition_z());
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(NPCrotating, 0, 1, 0);
			modelStack.Scale(2,2,2);
			renderMesh(meshList[GEO_NPCUPPER], true);
			/*if (it.getObjectposX() + 30 > camera.position.x && it.getObjectposX() - 30 < camera.position.x
				&& it.getObjectposZ() + 30 > camera.position.z && it.getObjectposZ() - 30 < camera.position.z)*/
			if (robotNPC1.interaction() == true)
			{
				if (!Application::IsKeyPressed('E'))
				{
					renderDialogueBox("Worker", robotNPC1.getDialogue(true));
				}
				else
				{
					renderDialogueBox("Worker", robotNPC1.getDialogue(false));
				}
				
			}
			modelStack.PopMatrix();
			break;
		}
		
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "npclower") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_NPCLOWER], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "npcupper2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Rotate(NPCrotating2, 0, 1, 0);
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_NPCUPPER], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "npclower2") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_NPCLOWER], true);
			modelStack.PopMatrix();
			break;
		}
	}
	//npc1,2

	//npc3
	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "npcupper3") {
			modelStack.PushMatrix();
			/*modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());*/
			modelStack.Translate(robotNPC2.NPC_getposition_x(), robotNPC2.NPC_getposition_y(), robotNPC2.NPC_getposition_z());
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Rotate(NPCrotating3, 1, 0, 0);
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_NPCUPPER], true);
			if (robotNPC2.interaction() == true)
			{
				if (!Application::IsKeyPressed('E'))
				{
					renderDialogueBox("Disaster", robotNPC2.getDialogue(true));
				}
				else
				{
					renderDialogueBox("Disaster", robotNPC2.getDialogue(false));
				}

			}
			modelStack.PopMatrix();
			break;
		}
	}

	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "npclower3") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_NPCLOWER], true);
			modelStack.PopMatrix();
			break;
		}
	}

	
}

void scene2_SP2::RenderBoxes()
{
	if (change == true)
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "boxes9") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX() , it.getObjectposY(), it.getObjectposZ());
				modelStack.Rotate(-90, 0, 1, 0);
				modelStack.Rotate(boxesrotating, 0, 1, 0);
				modelStack.Scale(2, 2, 2);
				renderMesh(meshList[GEO_BOXES], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}
		
	if (change2 == true)
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "boxes9_2") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Rotate(boxesrotating2, 0, 1, 0);
				modelStack.Scale(2, 2, 2);
				renderMesh(meshList[GEO_BOXES], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}
	for (int i = 0; i > -60; i -= 20)//first row box
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "normalboxes") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ()+i);
				modelStack.Scale(2, 2, 2);
				renderMesh(meshList[GEO_NORMALBOXES], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}

	for (int i = 0; i > -40; i -= 20)//second row box
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "normalboxes") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX(), it.getObjectposY()+11, it.getObjectposZ()-10 + i);
				modelStack.Scale(2, 2, 2);
				renderMesh(meshList[GEO_NORMALBOXES], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}
	
	for (auto it : camera.storage_of_objects) {

		if (it.getName() == "normalboxes") {
			modelStack.PushMatrix();
			modelStack.Translate(it.getObjectposX(), it.getObjectposY() + 23, it.getObjectposZ() - 20);
			modelStack.Scale(2, 2, 2);
			renderMesh(meshList[GEO_NORMALBOXES], true);
			modelStack.PopMatrix();
			break;
		}
	}

	for (int i = 0; i > -60; i -= 20)//first row box
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "normalboxes2") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ() + i);
				modelStack.Scale(2, 2, 2);
				renderMesh(meshList[GEO_NORMALBOXES], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}

	//npc3 box
	if (change3 == true)
	{
		for (auto it : camera.storage_of_objects) {

			if (it.getName() == "boxes9_3") {
				modelStack.PushMatrix();
				modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Rotate(boxesrotating3, 1, 0, 0);
				modelStack.Scale(2, 2, 2);
				renderMesh(meshList[GEO_BOXES], true);
				modelStack.PopMatrix();
				break;
			}
		}
	}
	
}

void scene2_SP2::VaultAnimation(double dt)
{
	if (Numpad.NumpadVerify()==true)
	{
			//camera.position.x = 0;
			//camera.position.y = 20;
			//camera.position.z = 150;
			wheelturning += 100 * (float)(dt);
			if (wheelturning > 360)// wheel will rotate 360 degree
			{
				wheelturning = 360;//wheel will stop at 360 degree
				stickpush = true;
			}
		if (stickpush == true) //stick start pushing after wheel stop turning
		{
			stickpushing += 50 * (float)(dt);
			if (stickpushing > 50) // stick will be translated +200 to x-axis
			{
				stickpushing = 50; // stick will stop when x=+200
				dooropen = true;
			}
		}
		if (dooropen == true)
		{
			if (dooropening >= 90) //door rotate 90 degree
			{
				dooropening = 90;
			}
			else
			{
				dooropening += 20 * (float)(dt);
			}
		}
	}
}

//void scene2_SP2::RenderPlane()
//{
//	for (auto it : camera.storage_of_objects) {
//
//		if (it.getName() == "plane") {
//			modelStack.PushMatrix();
//			modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
//			modelStack.Rotate(-90, 0, 1, 0);
//			modelStack.Scale(20, 20, 20);
//			renderMesh(meshList[GEO_PLANE], true);
//			modelStack.PopMatrix();
//			break;
//		}
//	}
//}

void scene2_SP2::SatelliteAnimation(double dt)
{
	if (satelliterotate == false)
	{
		satelliterotating += 15 * (float)(dt);
		if (satelliterotating > 45)
		{
			satelliterotate = true;
		}
	}
	else if (satelliterotate == true)
	{
		satelliterotating -= 15 * (float)(dt);
		if (satelliterotating < -45)
		{
			satelliterotate = false;
		}
	}
}

void scene2_SP2::diamondAnimation(double dt)
{
	if (bigdiamondtranslate == false) //bigdiamond floating
	{
		bigdiamondtranslating += 20 * (float)(dt);
		if (bigdiamondtranslating > 30)
		{
			bigdiamondtranslate = true;
		}
	}
	else if (bigdiamondtranslate == true)
	{
		bigdiamondtranslating -= 20 * (float)(dt);
		if (bigdiamondtranslating < -20)
		{
			bigdiamondtranslate = false;
		}
	}

	if (smalldiamondtranslate == false) //smalldiamond floating
	{
		smalldiamondtranslating += 20 * (float)(dt);
		if (smalldiamondtranslating > 30)
		{
			smalldiamondtranslate = true;
		}
	}
	else if (smalldiamondtranslate == true)
	{
		smalldiamondtranslating -= 20 * (float)(dt);
		if (smalldiamondtranslating < -20)
		{
			smalldiamondtranslate = false;
		}
	}

		smalldiamondrotating += 50 * (float)(dt);
		bigdiamondrotating += 10 * (float)(dt);

}

void scene2_SP2::NPCAnimation(double dt)
{
	/*if (robotNPC1.interaction())
	{*/
		//npc1 animation
		if (NPCrotate == false)
		{
			NPCrotating -= 150 * (float)(dt);
			if (NPCrotating < 0)
			{
				NPCrotate = true;
			}
		}
		else if (NPCrotate == true)
		{
			NPCrotating += 150 * (float)(dt);
			if (NPCrotating > 180)
			{
				NPCrotate = false;
			}
		}

		//npc1 passing boxes
		if (change == false && NPCrotating < 1)
		{
			change = true;
		}
		else if (change == true && NPCrotating > 178)
		{
			change = false;
		}


		//npc2 animation
		if (NPCrotate2 == false)
		{
			NPCrotating2 -= 150 * (float)(dt);
			if (NPCrotating2 < -180)
			{
				NPCrotate2 = true;
			}
		}
		else if (NPCrotate2 == true)
		{
			NPCrotating2 += 150 * (float)(dt);
			if (NPCrotating2 >0)
			{
				NPCrotate2 = false;
			}
		}

		//npc2 passing boxes
		if (change2 == false && NPCrotating2 < -178)
		{
			change2 = true;
		}
		else if (change == true && NPCrotating2 > -2)
		{
			change2 = false;
		}
	
	/*else
	{
		NPCrotating = NPCrotating2 = 0;
		change = change2 = false;
	}*/
		//npc3 animation
		if (robotNPC2.interaction() && robotNPC2.get_LineOfDialogue() == 5)
		{
			//NPCrotating3 += 50 * (float)(dt);
			if (NPCrotate3 == false)
			{
				NPCrotating3 += 50 * (float)(dt);
				if (NPCrotating3 >75)
				{
					NPCrotate3 = true;
				}
			}
			else if (NPCrotate3 == true)
			{
				NPCrotating3 -= 50 * (float)(dt);
				if (NPCrotating3 <= 0)
				{
					NPCrotating3 = 0;
				}
			}
		}
		else
		{
			NPCrotate3 = false;
		}
		
		if (change3== false && NPCrotating3 >72)
		{
			change3 = true;
		}
		/*else if (change == true && NPCrotating3)
		{
			change2 = false;
		}*/
}

void scene2_SP2::BoxesAnimation(double dt)
{
		//box1
		if (boxesappear == false)
		{
			boxesrotating -= 150 * (float)(dt);
			if (boxesrotating < 0)
			{
				boxesappear = true;
			}
		}
		else if (boxesappear == true)
		{
			boxesrotating += 150 * (float)(dt);
			if (boxesrotating > 180)
			{
				boxesappear = false;
			}
		}

		//box2
		if (boxesappear2 == false)
		{
			boxesrotating2 -= 150 * (float)(dt);
			if (boxesrotating2 <-180)
			{
				boxesappear2 = true;
			}
		}
		else if (boxesappear2 == true)
		{
			boxesrotating2 += 150 * (float)(dt);
			if (boxesrotating2 >0)
			{
				boxesappear2 = false;
			}
		}

		//box3
		if (robotNPC2.interaction() && robotNPC2.get_LineOfDialogue()==5)
		{
			if (boxesappear3 == false)
			{
				boxesrotating3 += 50 * (float)(dt);
				if (boxesrotating3 >75)
				{
					boxesappear3 = true;
				}
			}
			else if (boxesappear3 == true)
			{
				boxesrotating3 -= 50 * (float)(dt);
				if (boxesrotating3 <= 0)
				{
					boxesrotating3 = 0;
				}
			}
		}
		else
		{
			boxesappear3 = false;
		}
		

		/*if (NPCrotate3 == false)
		{
			NPCrotating3 += 50 * (float)(dt);
			if (NPCrotating3 >75)
			{
				NPCrotate3 = true;
			}
		}
		else if (NPCrotate3 == true)
		{
			NPCrotating3 -= 50 * (float)(dt);
			if (NPCrotating3 <= 0)
			{
				NPCrotating3 = 0;
			}
		}*/
	
}

void scene2_SP2::renderDeadPool() {
    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "DeadPool") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
            modelStack.Rotate(-90, 0, 1, 0);
            modelStack.Scale(4, 4, 4);
            renderMesh(meshList[GEO_DEADPOOL], true);
            modelStack.PopMatrix();
            break;
        }
    }

    //rendering his dialogue
    if (beginIamYourFather) {
        if (endingTime < 2) {
            renderDialogueBox("DeadPool", "Join The Dark Side");
        }
        else if (endingTime < 4) {
            renderDialogueBox("DeadPool", "I am Your Father");
        }
    }
    //rendering his dialogue
}


void scene2_SP2::RenderImageOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY) {
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

void scene2_SP2::renderDialogueBox(const string& name, const string& dialogue) {
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 17, 16, 18, 5);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], name, Color(0, 1, 0), 3, 3.5, 5.5);
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 70, 40, -20);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], dialogue, Color(0, 1, 0), 3, 3.5, 4);
}

void scene2_SP2::Ending(double& dt) {
    if (!beginIamYourFather) {
        camera.setLocation(0, camera.defaultPosition.y, 150);
        camera.setRotation(0, 180);
    }
    else {
        endingTime += dt;
    }

    if (beginIamYourFather == true && endingTime < 4) {
        camera.setLocation(10, 30, 10);
        camera.setRotation(0, 220);
    }
    else if (endingTime > 4 && beginIamYourFather == true) {
        camera.setLocation(0, camera.defaultPosition.y, 150 + moveToDeadPoolZ);
        camera.setRotation(0, 180);
        if (moveToDeadPoolZ < -135) {
            if (sizeofEndingScreen > 200) {
                creditRolling.activateCredit();
            }
            else {
                sizeofEndingScreen += 200 * (float)(dt);
            }
        }
        if (moveToDeadPoolZ > -145) {
            moveToDeadPoolZ -= 25 * (float)(dt);
        }
    }

    camera.target = Vector3(sin(Math::DegreeToRadian(camera.getCameraYrotation())) * cos(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.x, -sin(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.y, cos(Math::DegreeToRadian(camera.getCameraYrotation())) * cos(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.z);
    Vector3 view = (camera.target - camera.position).Normalized();
    Vector3 right = view.Cross(camera.defaultUp);
    camera.up = right.Cross(view);
}

void scene2_SP2::renderEndingScreen() {
    modelStack.PushMatrix();
    RenderImageOnScreen(meshList[GEO_ENDING_SCREEN], sizeofEndingScreen, 40, 30);
    modelStack.PopMatrix();
}

void scene2_SP2::rollingCredits() {
    if (creditRolling.goRollCredit()) {
        if (creditRolling.getRollingTitle() < 15) {
            RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Prologue Ended", Color(0, 1, 0), 5, 5, creditRolling.getRollingTitle());
            RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "To Be Continued", Color(0, 1, 0), 3, 10, -1 + creditRolling.getRollingTitle() + creditRolling.getRollingTitleCaption());
            RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Plz buy our expansion packs on Steam", Color(0, 1, 0), 3, 5, -2 + creditRolling.getRollingTitle() + creditRolling.getRollingTitleCaption());
        }
        else if (creditRolling.getMovePositionY() > (5 * creditRolling.position.size()) + 5) {
            RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "And You", Color(0, 1, 0), 5, 6.5, 8);
        }
        else {
            float moveY = 0;
            for (unsigned num = 0; num < creditRolling.position.size(); ++num, moveY -= 4) {
                RenderTextOnScreen(meshList[GEO_COMIC_TEXT], creditRolling.position[num], Color(0, 1, 0), 3, 3, creditRolling.getMovePositionY() + moveY);
                RenderTextOnScreen(meshList[GEO_COMIC_TEXT], creditRolling.names[num], Color(0, 1, 0), 3, 3, -1 + creditRolling.getMovePositionY() + moveY);
            }
        }
    }
}

