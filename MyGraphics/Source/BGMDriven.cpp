#include "BGMDriven.h"

BGMDriven::BGMDriven() 
{
    engine = createIrrKlangDevice();
    sound_names = { 
        "music//Star Wars- The Imperial March (Darth Vader's Theme).ogg", 
        ""
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
        engine->addSoundSourceFromFile(sound_names[0].c_str());

    ZeBackgroundMusic = engine->play2D(DarthVaderbackGround, false, false, true);
    ZeBackgroundMusic->setVolume(0.5f);
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
