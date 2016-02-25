#include "GL\glew.h"
#include <sstream>

#include "shader.hpp"
#include "Mtx44.h"

#include "MeshBuilder.h"
#include "MaterialBuilder.h"
#include "Light.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadingScreen.h"
#include "MyMath.h"
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
LoadingScreen::LoadingScreen(float screenwidth, float screenheight)
    : screenWidth(screenwidth), screenHeight(screenheight)
{
}
/******************************************************************************/
/*!
\brief - destructor
*/
/******************************************************************************/
LoadingScreen::~LoadingScreen()
{
}
/******************************************************************************/
/*!
\brief -
initializing whatever is needed for the scene
*/
/******************************************************************************/
void LoadingScreen::Init()
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


    //Initialize camera settings
    camera.Init("cameraDriven//scene3.txt");
    camera.camType = Camera3::FIRST_PERSON;

    meshList[GEO_COMIC_TEXT] = MeshBuilder::GenerateText("comic sans text", 16, 16);
    meshList[GEO_COMIC_TEXT]->textureID = LoadTGA("Image//comicSans.tga");

    meshList[GEO_LOADING_SCREEN_TITLE] = MeshBuilder::GenerateQuad("Screen Title", Color(1, 1, 1));
    meshList[GEO_LOADING_SCREEN_TITLE]->textureID = LoadTGA("Image//loadingTitle.tga");

    meshList[GEO_LOADING_DOGE] = MeshBuilder::GenerateQuad("Loading Doge", Color(1, 1, 1));
    meshList[GEO_LOADING_DOGE]->textureID = LoadTGA("Image//loading_doge.tga");

    meshList[GEO_LOADING_BREATHING_CAT] = MeshBuilder::GenerateQuad("Loading breathing cat", Color(1, 1, 1));
    meshList[GEO_LOADING_BREATHING_CAT]->textureID = LoadTGA("Image//loading_breathingCats.tga");

    on_light = true;

    Mtx44 projection;
    projection.SetToPerspective(60.f, static_cast<float>(screenWidth / screenHeight), 0.1f, 200000.f);
    projectionStack.LoadMatrix(projection);

    framePerSecond = 0;
    camera.cursorCoordX = screenWidth / 2;
    camera.cursorCoordY = screenHeight / 2;

    initLoadingHints("loadingScreenDriven//hints.txt");

    percentage = 0;
}

/******************************************************************************/
/*!
\brief -
where the logic of the game is, and update

\param dt - time frame
*/
/******************************************************************************/
void LoadingScreen::Update(double dt)
{
    camera.Update(dt);
    framePerSecond = 1 / dt;
}

/******************************************************************************/
/*!
\brief - rendering of the meshes

\param mesh - the specific mesh
\param enableLight - to enable lighting on the object
*/
/******************************************************************************/
void LoadingScreen::renderMesh(Mesh *mesh, bool enableLight)
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
void LoadingScreen::Render()
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

    RenderImageOnScreen(meshList[GEO_LOADING_SCREEN_TITLE], 52, 40, 40);

    RenderImageOnScreen(meshList[GEO_LOADING_DOGE], 60, 70, 13);

    RenderImageOnScreen(meshList[GEO_LOADING_BREATHING_CAT], 60, 12, 10);

    srand(static_cast<size_t>(time(NULL)));
    int randomiseTheHint = Math::RandIntMinMax(0, loadingHints.size() - 1);
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], loadingHints[randomiseTheHint], Color(0,1,0), 2, 17, 35);

    std::stringstream ss;
    ss << percentage << "% Completed";
    RenderTextOnScreen(meshList[GEO_COMIC_TEXT], ss.str(), Color(0, 1, 0), 5, 28, 27);
    percentage += 33;
}

/******************************************************************************/
/*!
\brief -
cleans up the scene
*/
/******************************************************************************/
void LoadingScreen::Exit()
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
void LoadingScreen::RenderText(Mesh* mesh, std::string text, Color color)
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
void LoadingScreen::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
    modelStack.Translate(x, y, 0);
    modelStack.Scale(size, size, size);

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
void LoadingScreen::RenderImageOnScreen(Mesh* mesh, float size, float x, float y) {
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
\brief - initialising the hints from a text file

\param fileName - path name to the file's location
*/
/******************************************************************************/
void LoadingScreen::initLoadingHints(const char *fileName) {
    std::ifstream fileStream2(fileName, std::ios::binary);
    if (!fileStream2.is_open()) {
        std::cout << "Impossible to open " << fileName << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream2.eof()) {
            string data = "";
            getline(fileStream2, data);
            if (data == "" || data == "\r") {
                continue;
            }
            data.erase(std::remove(data.begin(), data.end(), '\r'));
            loadingHints.push_back(data);
        }
        fileStream2.close();
    }
}