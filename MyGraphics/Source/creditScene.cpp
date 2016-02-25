#include "creditScene.h"
#include <fstream>
#include <algorithm>
#include <iostream>

creditScene::creditScene()
    : rollingTitle(0), rollingTitleCaption(0), rollCredits(false), movePositionY(0)
{
}

creditScene::~creditScene()
{
}

void creditScene::initCredit(char *fileLocation) {
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

            position.push_back(taking_the_stuff);
            names.push_back(values);
        }
        fileStream2.close();
    }
}

void creditScene::updateCredit(double& dt) {
        if (rollingTitle < 15) {
            rollingTitle += (2) * (float)(dt);
            rollingTitleCaption += (float)(dt);
        }
        else {
            movePositionY += 2 * (float)(dt);
        }
}

bool creditScene::goRollCredit() {
    if (rollCredits) {
        return true;
    }
    return false;
}

float creditScene::getRollingTitle() {
    return rollingTitle;
}

float creditScene::getRollingTitleCaption() {
    return rollingTitleCaption;
}

void creditScene::activateCredit() {
    rollCredits = true;
}

float creditScene::getMovePositionY() {
    return movePositionY;
}