#include "BGMDriven.h"

BGMDriven::BGMDriven() 
{
    engine = createIrrKlangDevice();
    sound_names = { 
        "" };
    background_music = { 
        "music//Star Wars- The Imperial March (Darth Vader's Theme).mp3" 
    };
}

BGMDriven::~BGMDriven()
{
    engine->drop();
}

void BGMDriven::init() {
    backGround = 
        engine->addSoundSourceFromFile(background_music[0].c_str());
    backGround->setDefaultVolume(0.3f);
}

void BGMDriven::playDarthVaderBackground() {
    if (engine->isCurrentlyPlaying(backGround)) {
        backGround->drop();
    }
    engine->play2D(backGround, true);
}