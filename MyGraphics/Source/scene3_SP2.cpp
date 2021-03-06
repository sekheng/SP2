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
#include <fstream>
#include <algorithm>

/******************************************************************************/
/*!
\brief -
constructor with 2 arguments to store the width and height of the screen

\param screenwidth - width of the screen
\param screenheight - height of the screen
*/
/******************************************************************************/
scene3_SP2::scene3_SP2(float screenwidth, float screenheight)
    : screenWidth(screenwidth), screenHeight(screenheight)
{
}
/******************************************************************************/
/*!
\brief - destructor
*/
/******************************************************************************/
scene3_SP2::~scene3_SP2()
{
}
/******************************************************************************/
/*!
\brief -
initializing whatever is needed for the scene
*/
/******************************************************************************/
void scene3_SP2::Init()
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
    //2nd light bulb
    m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
    m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
    m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
    m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
    m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
    m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
    //first light bulb
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
    m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
    m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
    m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
    m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

    //second Light_bulb
    m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
    m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
    m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
    m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
    m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
    //second Light_bulb

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    glUseProgram(m_programID);

    glUniform1i(m_parameters[U_NUMLIGHTS], 2);

    light[0].type = Light::LIGHT_DIRECTIONAL;
    light[0].position.Set(0, 1200, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 0.5f;
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

    //second light bulb
    light[1].type = Light::LIGHT_DIRECTIONAL;
    light[1].position.Set(0, 1200, -10000);
    light[1].color.Set(1, 1, 1);
    light[1].power = 1.f;
    light[1].kC = 1.f;
    light[1].kL = 0.01f;
    light[1].kQ = 0.01f;
    light[1].cosCutoff = cos(Math::DegreeToRadian(45));
    light[1].cosInner = cos(Math::DegreeToRadian(30));
    light[1].exponent = 3.f;
    light[1].spotDirection.Set(0.f, 1.f, 0.f);

    glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
    glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
    glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
    glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
    glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
    glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
    glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
    glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
    glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
    //second light bulb

    //Initialize camera settings
    camera.Init("cameraDriven//scene3.txt");
    camera.InitObjects("scenario2Driven//objects.txt");
    camera.camType = Camera3::FIRST_PERSON;

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    meshList[GEO_COMIC_TEXT] = MeshBuilder::GenerateText("comic sans text", 16, 16);
    meshList[GEO_COMIC_TEXT]->textureID = LoadTGA("Image//scene3//comicSans.tga");

    //skybox
    meshList[GEO_SPACE_SKYBOX] = MeshBuilder::GenerateOBJ("space skybox", "OBJ//scene1//Space_Skybox.obj");
    meshList[GEO_SPACE_SKYBOX]->textureID = LoadTGA("Image//scene1//skybox//Space_Skybox_UV.tga");

    //spaceship
    meshList[GEO_FLYINGVEHICLE] = MeshBuilder::GenerateOBJ("landvehicle", "OBJ//scene1//FlyingVehicle.obj");
    meshList[GEO_FLYINGVEHICLE]->textureID = LoadTGA("Image//scene1//FlyingVehicle.tga");
    meshList[GEO_FLYINGVEHICLE]->material = MaterialBuilder::GenerateBlinn();

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light_ball", Color(1, 1, 1));

    meshList[GEO_LIGHT_WRAP] = MeshBuilder::GenerateOBJ("light warp", "OBJ//scene3//light_warpping.obj");
    meshList[GEO_LIGHT_WRAP]->textureID = LoadTGA("Image//scene3//light_warpping.tga");
    meshList[GEO_LIGHT_WRAP]->material = MaterialBuilder::GenerateBlinn();

    meshList[GEO_LIGHT_END] = MeshBuilder::GenerateQuad("light end", Color(1, 1, 1));
    meshList[GEO_LIGHT_END]->textureID = LoadTGA("Image//scene3//white_warp.tga");

    meshList[GEO_ASTEROID] = MeshBuilder::GenerateOBJ("asteroid", "OBJ//scene3//asteroid.obj");
    meshList[GEO_ASTEROID]->textureID = LoadTGA("Image//scene3//asteroid.tga");

    //text box
    meshList[GEO_TEXT_BOX] = MeshBuilder::GenerateQuad("text box", Color(1, 1, 1));
    meshList[GEO_TEXT_BOX]->textureID = LoadTGA("Image//scene1//textbox.tga");
    //text box

    on_light = true;

    Mtx44 projection;
    projection.SetToPerspective(45.f, static_cast<float>(screenWidth / screenHeight), 0.1f, 200000.f);
    projectionStack.LoadMatrix(projection);

    framePerSecond = 0;
    camera.cursorCoordX = screenWidth / 2;
    camera.cursorCoordY = screenHeight / 2;

    //animating the spaceShip
    jitteringShipY = 0;
    toggleUp = false;
    scaleShipZ = 0;
    warppingOn = true;
    //animating the spaceShip

    //animating the SkyBox
    scaleSkyBoxZ_ = 0;
    //animating the SkyBox

    //animating the warp
    warp_lightZ = 0;
    wait_on_white_screen = 0;
    start_white_screen = false;
    //animating the warp

    //for the 2nd light bulb
    turn_on_2nd = false;
    //for the 2nd light bulb

    //animating the light ending
    scaleLightEnd = 1;
    //animating the light ending

    //for QTE
    initQuickTimeEvent("scenario2Driven//quicktimeevent.txt");
    DefaultquickTimeEvent = quickTimeEvent;
    quickTimeEventFlag = false;
    quickTimer = 10;
    makingSureNoDoubleTap = 0;
    moveAsteroidZ = 0;
    moveShipX = 0;
    moveShipZ = 0;
    moveBack = false;
    quickTimeEventOver = false;
    youLost = false;
    //for QTE

    //gives instruction regarding about the QTE
    instructionIsOver = false;
    intructions = {"Avoid the asteroid", 
    "Press according to the keys displayed",
    "You only have 10 Seconds. Good Luck!"};
    order_of_text_ = 0;
    //gives instruction regarding about the QTE

    //rotating the spaceShip to make it looks realistic
    rotationShipY = 0;
    //rotating the spaceShip to make it looks realistic

    std::cout << "Number of objects in Scenario 2: " << camera.storage_of_objects.size() << std::endl;
}

/******************************************************************************/
/*!
\brief -
where the logic of the game is, and update

\param dt - time frame
*/
/******************************************************************************/
void scene3_SP2::Update(double dt)
{
    animateWarp(dt);
    animateSpaceShip(dt);
    framePerSecond = 1 / dt;

    if (Application::IsKeyPressed(VK_NUMPAD4))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed(VK_NUMPAD5))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode


    if (Application::IsKeyPressed(VK_NUMPAD1)) {
        reset();
        Application::changeIntoScenario1();
    }
    if (Application::IsKeyPressed(VK_NUMPAD3)) {
        reset();
        Application::changeIntoScenario3();
    }
    //transition to the 3rd scenario
    if (start_white_screen) {   
        wait_on_white_screen += dt;
        if (wait_on_white_screen > 0.5) {
            Application::changeIntoScenario3();
        }
    }
    //transition to the 3rd scenario

    //for QTE
    if ((Application::IsKeyPressed('W') || Application::IsKeyPressed('D')
        || Application::IsKeyPressed('S') || Application::IsKeyPressed('A') ||
        Application::IsKeyPressed('E'))
        && quickTimeEventFlag == false) {
        //This is to prevent the keys from being pressed beforehand
    }
    else if (quickTimeEventFlag == true && quickTimeEventOver == false && youLost == false) {
        Application::musics->playPokemonBattleBackground();
        makingSureNoDoubleTap += dt;
        //when the mini-game finished, an animation of the ship escaping the asteroid will be played
        if (quickTimeEvent.empty() == true) {
            //the ship and asteroid will start to move
            moveShipZ -= 55 * (float)(dt);
            camera.position.z -= 55 * (float)(dt);
            moveAsteroidZ += 22 * (float)(dt);
            //the ship will move towards the right to avoid
            if (moveBack == false) {
                moveShipX += 46 * (float)(dt);
                camera.position.x += 41 * (float)(dt);
                //animating the rotation of spaceship
                if (rotationShipY > -20) {
                    rotationShipY -= 4 * (float)(dt);
                }
                //animating the rotation of spaceship
                //the ship will move towards the left when it safely avoids the asteroid and return back to it's normal route
                if (camera.position.x > 280) {
                    moveBack = true;
                }
                //the ship will move towards the left when it safely avoids the asteroid and return back to it's normal route
                //the ship and asteroid will start to move
            }
            //the ship will move towards the left when it safely avoids the asteroid and return back to it's normal route
            else if (moveBack == true && camera.position.x > 0) {
                moveShipX -= 46 * (float)(dt);
                camera.position.x -= 41 * (float)(dt);
                //animating the rotation of spaceship
                if (rotationShipY < 20 && camera.position.x > 100) {
                    rotationShipY += 4 * (float)(dt);
                }
                else if (camera.position.x < 100 && rotationShipY > 0) {
                    rotationShipY -= 4 * (float)(dt);
                }
                //animating the rotation of spaceship
                //if the spaceship went back to it's normal route, it will being warpping
                if (camera.position.x <= 0) {
                    quickTimeEventOver = true;
                    warppingOn = true;
                    moveShipZ = 0;
                    camera.position.z = camera.defaultPosition.z;
                    camera.position.x = camera.defaultPosition.x;
                    rotationShipY = 0;
                }
                //if the spaceship went back to it's normal route, it will being warpping
                //the ship will move towards the left when it safely avoids the asteroid and return back to it's normal route
            }
        }
        //when the mini-game finished, an animation of the ship escaping the asteroid will be played
        else if (instructionIsOver == false) {
            updateIntructions(dt);
        }
        //when the mini-game starts
        else {
            activateQTE(dt);
            //is to prevent the key spamming
            if (makingSureNoDoubleTap > 0.1) {
                if (Application::IsKeyPressed('W')) {
                    if (quickTimeEventFlag == true && quickTimeEvent.front() == 'W') {
                        quickTimeEvent.pop();
                    }
                }
                else if (Application::IsKeyPressed('A')) {
                    if (quickTimeEventFlag == true && quickTimeEvent.front() == 'A') {
                        quickTimeEvent.pop();
                    }
                }
                else if (Application::IsKeyPressed('S')) {
                    if (quickTimeEventFlag == true && quickTimeEvent.front() == 'S') {
                        quickTimeEvent.pop();
                    }
                }
                else if (Application::IsKeyPressed('D')) {
                    if (quickTimeEventFlag == true && quickTimeEvent.front() == 'D') {
                        quickTimeEvent.pop();
                    }
                }
                makingSureNoDoubleTap = 0;
                //is to prevent the key spamming
                //when the mini-game starts
            }
        }
    }
    //reset the whole scenario
    else if (youLost == true) {
        if (Application::IsKeyPressed('E')) {
            reset();
        }
    }
    //reset the whole scenario

    //when the animation of space ship flying over the asteroid is over
    if (quickTimeEventOver) {
        quickTimeEventFlag = false;
    }
    //when the animation of space ship flying over the asteroid is over
    //for QTE

    //reset button
    if (Application::IsKeyPressed('R')) {
        instructionIsOver = false;
        order_of_text_ = 0;
        reset();
    }
    //reset button

    camera.target = Vector3(sin(Math::DegreeToRadian(camera.getCameraYrotation())) * cos(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.x, -sin(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.y, cos(Math::DegreeToRadian(camera.getCameraYrotation())) * cos(Math::DegreeToRadian(camera.getCameraXrotation())) + camera.position.z);
    Vector3 view = (camera.target - camera.position).Normalized();
    Vector3 right = view.Cross(camera.defaultUp);
    camera.up = right.Cross(view);
}

/******************************************************************************/
/*!
\brief - rendering of the meshes

\param mesh - the specific mesh
\param enableLight - to enable lighting on the object
*/
/******************************************************************************/
void scene3_SP2::renderMesh(Mesh *mesh, bool enableLight)
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
void scene3_SP2::Render()
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

    if (light[1].type == Light::LIGHT_DIRECTIONAL)
    {
        Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
    }
    if (turn_on_2nd) {
        Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
        glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
        modelStack.PushMatrix();
        modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
        modelStack.Scale(0.5f, 0.5f, 0.5f);
        renderMesh(meshList[GEO_LIGHTBALL], false);
        modelStack.PopMatrix();
    }
    
    if (youLost == false) {
        //renderMesh(meshList[GEO_AXES], false);

        modelStack.PushMatrix();
        modelStack.Scale(300, 300, 300 + scaleSkyBoxZ_);
        RenderSkybox();
        modelStack.PopMatrix();

        modelStack.PushMatrix();
        renderSpaceShip();
        modelStack.PopMatrix();

        renderWarp();

        //asteroid will only appear when the spaceship suddenly stopped moving
        //thus it's originally being placed in front of the spaceship and move very far away and back
        if ((warppingOn == false || quickTimeEventFlag == true) && quickTimeEventOver == false) {
            for (auto it : camera.storage_of_objects) {
                if (it.getName() == "Asteroid") {
                    modelStack.PushMatrix();
                    modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ() + moveAsteroidZ);
                    modelStack.Scale(50, 50, 50);
                    renderMesh(meshList[GEO_ASTEROID], true);
                    modelStack.PopMatrix();
                }
            }
        }
        //asteroid will only appear when the spaceship suddenly stopped moving
        if (start_white_screen) {
            RenderImageOnScreen(meshList[GEO_LIGHT_END], scaleLightEnd, 40, 30);
        }
        if (moveAsteroidZ == 420 && instructionIsOver == false) {
            renderInstructions();
        }
        else {
            renderQTE();
        }
    }
    else {
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "You Got Hit By An Asteroid", Color(0, 1, 0), 4, 4, 14);
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], "Press E to Retry", Color(0, 1, 0), 4, 6, 12);
    }

    //std::stringstream connectPosX;
    //connectPosX << std::fixed << std::setprecision(2) << "X : " << camera.getCameraXcoord();
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosX.str(), Color(0, 1, 0), 1.8f, 1.5f, 21.2f);

    //std::stringstream connectPosZ;
    //connectPosZ << std::fixed << std::setprecision(2) << "Z : " << camera.getCameraZcoord();
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosZ.str(), Color(0, 1, 0), 1.8f, 1.5f, 19.f);
    //
    //std::stringstream connectPosY;
    //connectPosY << std::fixed << std::setprecision(2) << "Y : " << camera.getCameraYcoord();
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], connectPosY.str(), Color(0, 1, 0), 1.8f, 1.5f, 18.f);

    //std::stringstream asteroidPosZ;
    //asteroidPosZ << moveAsteroidZ;
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], asteroidPosZ.str(), Color(0, 1, 0), 1.8f, 5, 5);

    //std::stringstream ss;
    //ss << "FPS : " << static_cast<int>(framePerSecond);
    //RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 4, 0.5, 0.5);
}

/******************************************************************************/
/*!
\brief -
cleans up the scene
*/
/******************************************************************************/
void scene3_SP2::Exit()
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
void scene3_SP2::RenderText(Mesh* mesh, std::string text, Color color)
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
void scene3_SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void scene3_SP2::RenderImageOnScreen(Mesh* mesh, float size, float x, float y) {
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
\brief - a method to render the skybox
*/
/******************************************************************************/
void scene3_SP2::RenderSkybox()
{
    modelStack.PushMatrix();
    renderMesh(meshList[GEO_SPACE_SKYBOX], false);
    modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief - a method to render the space Ship
*/
/******************************************************************************/
void scene3_SP2::renderSpaceShip() {
    for (auto it : camera.storage_of_objects) {
        if (it.getName() == "spaceship") {
            modelStack.PushMatrix();
            modelStack.Translate(it.getObjectposX() + moveShipX, it.getObjectposY() + jitteringShipY, it.getObjectposZ() + moveShipZ);
            modelStack.Rotate(rotationShipY, 0, 1, 0);
            modelStack.Scale(10, 10, 10 + scaleShipZ);
            renderMesh(meshList[GEO_FLYINGVEHICLE], true);
            modelStack.PopMatrix();
            break;
        }
    }
}

/******************************************************************************/
/*!
\brief - a method to animate the spaceship and it's logic

\param dt - frame time
*/
/******************************************************************************/
void scene3_SP2::animateSpaceShip(double dt) {
    //this is to make the spaceship looks jittering
    if (quickTimeEventFlag == false) {
        if (toggleUp == false)
        {
            jitteringShipY -= 15 * (float)(dt);
            if (jitteringShipY < -1)
            {
                toggleUp = true;
            }
        }
        else
        {
            jitteringShipY += 15 * (float)(dt);
            if (jitteringShipY > 1)
            {
                toggleUp = false;
            }
        }
    }
    //this is to make the spaceship looks jittering
    //when it is warping the spaceship, skybox, and the stars look distorted
    if (warppingOn == true) 
	{
        scaleShipZ += 30 * (float)(dt);
        scaleSkyBoxZ_ += 20000 * (float)(dt);
        moveAsteroidZ -= 30000 * (float)(dt);
        if (scaleShipZ > 100) 
		{
            warppingOn = false;
        }
    }
    //after some time, distorting stopped and spaceship seems to be travelling
    else if (scaleShipZ > 0 && warppingOn == false)
	{
        scaleShipZ -= 30 * (float)(dt);
        scaleSkyBoxZ_ -= 20000 * (float)(dt);
        moveAsteroidZ += 30000 * (float)(dt);
        if (scaleShipZ <= 0 && quickTimeEventFlag == false && quickTimeEventOver == false) {
            moveAsteroidZ = 420;
            scaleSkyBoxZ_ = 0;
            warp_lightZ = 0;
            scaleShipZ = 0;
            quickTimeEventFlag = true;
        }
    }
    if (quickTimeEventOver == true && warppingOn == false && scaleShipZ < 2) {  //animating the light warp end
        start_white_screen = true;
        scaleLightEnd += 500 * (float)(dt);
    }
}   

/******************************************************************************/
/*!
\brief - a method to render the warp
*/
/******************************************************************************/
void scene3_SP2::renderWarp() {
    if (quickTimeEventFlag == false) {
        for (auto it : camera.storage_of_objects) {
            if (it.getName() == "Light Warp1" ||
                it.getName() == "Light Warp2" ||
                it.getName() == "Light Warp3" ||
                it.getName() == "Light Warp4" ||
                it.getName() == "Light Warp5" ||
                it.getName() == "Light Warp6" ||
                it.getName() == "Light Warp7" ||
                it.getName() == "Light Warp8" ||
                it.getName() == "Light Warp9" ||
                it.getName() == "Light Warp10" ||
                it.getName() == "Light Warp11" ||
                it.getName() == "Light Warp12" ||
                it.getName() == "Light Warp13" ||
                it.getName() == "Light Warp14" ||
                it.getName() == "Light Warp15" ||
                it.getName() == "Light Warp16" ||
                it.getName() == "Light Warp17" ||
                it.getName() == "Light Warp18" ||
                it.getName() == "Light Warp19" ||
                it.getName() == "Light Warp20" ||
                it.getName() == "Light Warp21" ||
                it.getName() == "Light Warp22" ||
                it.getName() == "Light Warp23" ||
                it.getName() == "Light Warp24" ||
                it.getName() == "Light Warp25" ||
                it.getName() == "Light Warp26" ||
                it.getName() == "Light Warp27" ||
                it.getName() == "Light Warp28" ||
                it.getName() == "Light Warp29" ||
                it.getName() == "Light Warp30" ||
                it.getName() == "Light Warp31" ||
                it.getName() == "Light Warp32" ||
                it.getName() == "Light Warp33") {
                modelStack.PushMatrix();
                modelStack.Translate(it.getObjectposX(), it.getObjectposY(), it.getObjectposZ());
                modelStack.Scale(1, 1, 1 + warp_lightZ);
                renderMesh(meshList[GEO_LIGHT_WRAP], true);
                modelStack.PopMatrix();
            }
        }
    }
}

/******************************************************************************/
/*!
\brief - a method to animate the warp and it's logic

\param dt - frame time
*/
/******************************************************************************/
void scene3_SP2::animateWarp(double dt) {
    if (warppingOn) {
        warp_lightZ += 700 * (float)(dt);
        Application::musics->playWarpBackground();
    }
    else if (warppingOn == false && scaleShipZ > 0) {
        warp_lightZ -= 700 * (float)(dt);
        Application::musics->playWarpBackground();
    }
}

/******************************************************************************/
/*!
\brief - A Data Driven method that will initialised and determin what are the key press needed to pass this stage

\param fileLocation - the path name to the text file's location
*/
/******************************************************************************/
void scene3_SP2::initQuickTimeEvent(const char* fileLocation) {
    std::ifstream fileStream2(fileLocation, std::ios::binary);
    if (!fileStream2.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream2.eof()) {
            string data = "";
            getline(fileStream2, data);
            if (data == "" || data == "\r") {
                continue;
            }
            data.erase(std::remove(data.begin(), data.end(), '\r'));
            data[0] = toupper(data[0]);
            quickTimeEvent.push(data[0]);
        }
        fileStream2.close();
    }
}

/******************************************************************************/
/*!
\brief - a method to update the logic of QTE

\param dt - frame time
*/
/******************************************************************************/
void scene3_SP2::activateQTE(double& dt) {
    if (quickTimeEventFlag == true) {
        quickTimer -= dt;
        if (quickTimer < 0) {
            youLost = true;
        }
    }
}

/******************************************************************************/
/*!
\brief - a method to render QTE's stuff
*/
/******************************************************************************/
void scene3_SP2::renderQTE() {
    if (quickTimeEventFlag == true && quickTimeEvent.empty() == false) {
        std::stringstream ss;
        ss << "Time Left: " << quickTimer;
        RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 4, 7, 14);

        std::string ss2;
        ss2.append(1, quickTimeEvent.front());
        renderDialogueBox("Key Pressed", ss2);
    }
}

/******************************************************************************/
/*!
\brief - a method to reset everything inside scenario 2
*/
/******************************************************************************/
void scene3_SP2::reset() {
    camera.Reset();
    quickTimeEventFlag = false;
    quickTimer = 10;
    makingSureNoDoubleTap = 0;
    moveAsteroidZ = 0;
    moveShipX = 0;
    moveShipZ = 0;
    moveBack = false;
    quickTimeEventOver = false;
    youLost = false;
    //animating the spaceShip
    jitteringShipY = 0;
    toggleUp = false;
    scaleShipZ = 0;
    warppingOn = true;
    //animating the spaceShip

    //animating the SkyBox
    scaleSkyBoxZ_ = 0;
    //animating the SkyBox

    //animating the warp
    warp_lightZ = 0;
    wait_on_white_screen = 0;
    start_white_screen = false;
    //animating the warp
    //animating the light ending
    scaleLightEnd = 1;
    //animating the light ending
    quickTimeEvent = DefaultquickTimeEvent;

    rotationShipY = 0;
}

/******************************************************************************/
/*!
\brief - a method to render the instructions needed for QTE
*/
/******************************************************************************/
void scene3_SP2::renderInstructions() {
    renderDialogueBox("Instructions", intructions[order_of_text_]);
}

/******************************************************************************/
/*!
\brief - a method to update the logic behind rendering of the instruction and 
prevent the text from going to fast

\param dt - frame time
*/
/******************************************************************************/
void scene3_SP2::updateIntructions(double& dt) {
    if (Application::IsKeyPressed('E')) {
        if (makingSureNoDoubleTap > 0.2) {
            order_of_text_ += 1;
            makingSureNoDoubleTap = 0;
        }
        if (order_of_text_ == intructions.size()) {
            instructionIsOver = true;
        }
    }
}

/******************************************************************************/
/*!
\brief - a method to render the dialogue box in a much simpler way

\param name - the name of the interacted object

\param dialogue - what will be said by that object
*/
/******************************************************************************/
void scene3_SP2::renderDialogueBox(const string& name, const string& dialogue)
{
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 17, 16, 23, 5);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], name, Color(0, 1, 0), 3, 2.5, 5.5);
    RenderImageOnScreen(meshList[GEO_TEXT_BOX], 70, 40, -20);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], dialogue, Color(0, 1, 0), 3, 3.5, 4);
}

/******************************************************************************/
/*!
\brief - a method to render the image on screen which offers non-uniform scalling

\param mesh - the Shape that will be rendered

\param x - the x coordinate of the image

\param y - the y coordinate of the image

\param sizeX - the scalling of image based on X-axis

\param sizeY - the scalling of image based on Y-axis
*/
/******************************************************************************/
void scene3_SP2::RenderImageOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY) {
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
