#include "BGMDriven.h"

BGMDriven::BGMDriven() 
{
    engine = createIrrKlangDevice();
    sound_names = { 
        "" 
    };
    background_music = { 
        "music//Star Wars- The Imperial March (Darth Vader's Theme).mp3", " "
    };
}

BGMDriven::~BGMDriven()
{
    //ZeBackgroundMusic->drop();
    DarthVaderbackGround->drop();
    engine->drop();
}

void BGMDriven::init() {
    DarthVaderbackGround = 
        engine->addSoundSourceFromFile(background_music[0].c_str());
    ZeBackgroundMusic = engine->play2D(DarthVaderbackGround, false, false, true);
}

void BGMDriven::playDarthVaderBackground() {
    if (!engine->isCurrentlyPlaying(DarthVaderbackGround)) {
        ZeBackgroundMusic->stop();
    }
    if (ZeBackgroundMusic->isFinished()) {
        ZeBackgroundMusic =
            engine->play2D(DarthVaderbackGround, false, false, true);
    }
}
