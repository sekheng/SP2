#include "BGMDriven.h"

BGMDriven::BGMDriven() 
{
    engine = createIrrKlangDevice();
    sound_names = { "music//Star Wars- The Imperial March (Darth Vader's Theme).mp3" };
}

BGMDriven::~BGMDriven()
{
    engine->drop();
}

void BGMDriven::init() {
    backGround = 
        engine->addSoundSourceFromFile(sound_names[0].c_str());

}

void BGMDriven::playBackground() {
    engine->play2D(backGround, true);
    backGround->setDefaultVolume(0.5f);
}