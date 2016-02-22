#include "SekHeng.h"
#include <fstream>
#include <algorithm>
#include "Application.h"

SekHeng::SekHeng()
    : order_of_text(0), stage(0), interatingRadius(4), time(0), isOkay(false), hammerInHand(false)
{
    hammer.init(Vector3(0, 0, 150), 2, 2, "hammer");
}

SekHeng::~SekHeng()
{
}

void SekHeng::initDialogues(const char *fileLocation, Camera3& camera) {
    dub_camera = &camera;
    
    //streaming SekHeng's dialogue
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
            char *nextStuff;
            char *stringtoken = strtok_s(const_cast<char*>(data.c_str()), ",", &nextStuff);
            string taking_the_stuff = "";
            string values = "";
            taking_the_stuff.append(stringtoken);
            values.append(nextStuff);
            values.erase(std::remove(values.begin(), values.end(), '\r'));
            for (size_t num = 0; num < taking_the_stuff.size(); ++num) {
                taking_the_stuff[num] = tolower(taking_the_stuff[num]);
            }
            size_t the_stage = static_cast<size_t>(stoi(taking_the_stuff));
            map<size_t, vector<string>>::iterator it;
            if (dialogues.count(the_stage) == 1) {
                it = dialogues.find(the_stage);
                it->second.push_back(values);
                continue;
            }
            else {
                dialogues.insert(std::pair<size_t, vector<string>>(the_stage, { values }));
            }
        }
        fileStream2.close();
    }
    //streaming SekHeng's dialogue
}

void SekHeng::Update(double dt) {
    time += dt;
    preventSpamming();
    if (Application::IsKeyPressed('E')) {
        if (hammer.boundaryCheck(dub_camera->position.x, dub_camera->position.z))
            hammerInHand = true;
    }
}

string SekHeng::returnDialogue() {
    return dialogues[stage][order_of_text];
}

void SekHeng::activateQuest() {
    stage = 1;
}

bool SekHeng::interaction() {
    if ((objectPos.x + boundaryRadiusX + interatingRadius) > dub_camera->getCameraXcoord() &&
        (objectPos.x - boundaryRadiusX - interatingRadius) < dub_camera->getCameraXcoord() &&
        (objectPos.z + boundaryRadiusZ + interatingRadius) > dub_camera->getCameraZcoord() &&
        (objectPos.z - boundaryRadiusZ - interatingRadius) < dub_camera->getCameraZcoord())
    {
        return false;
    }
    order_of_text = 0;
    return true;
}

/******************************************************************************/
/*!
\brief - Prevention of the dialogue from running to fast if player is holding 'E'
*/
/******************************************************************************/
void SekHeng::preventSpamming() {
    if (Application::IsKeyPressed('E')) {
        if (time > 1) {
            order_of_text += 1;
            time = 0;
            if (order_of_text == dialogues[stage].size()) {
                order_of_text = 0;
            }
        }
    }
}

bool SekHeng::SekHengSayIsOk() {
    if (isOkay) {
        return true;
    }
    else {
        return false;
    }
}

void SekHeng::FinishedQuest() {
    stage = 2;
}

void SekHeng::getItem() {
    if (interaction() == false && interactingWithItem() == false) {
        isOkay = true;
    }
}

bool SekHeng::interactingWithItem() {
    if ((objectPos.x + boundaryRadiusX + interatingRadius) > hammer.getObjectposX() &&
        (objectPos.x - boundaryRadiusX - interatingRadius) < hammer.getObjectposX() &&
        (objectPos.z + boundaryRadiusZ + interatingRadius) > hammer.getObjectposZ() &&
        (objectPos.z - boundaryRadiusZ - interatingRadius) < hammer.getObjectposZ())
    {
        return false;
    }
    return true;
}