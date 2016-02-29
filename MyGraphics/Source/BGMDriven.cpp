#include "BGMDriven.h"

BGMDriven::BGMDriven() 
    : DarthVaderbackGround(0), GateEffectSource(0), GateEffect(0)
{
    engine = createIrrKlangDevice();
}

BGMDriven::~BGMDriven()
{
    engine->drop();
}

void BGMDriven::init() {
    DarthVaderbackGround = 
        engine->addSoundSourceFromFile("music//Star Wars- The Imperial March (Darth Vader's Theme).ogg");
    GateEffectSource =
        engine->addSoundSourceFromFile("music//electric_door_opening_2.ogg");

    ZeBackgroundMusic = engine->play2D(DarthVaderbackGround, true, false, true);
    ZeBackgroundMusic->setVolume(0.1f);

    GateEffect = engine->play3D(GateEffectSource, vec3df(0, 0, 0), false, true, true);
}

void BGMDriven::playDarthVaderBackground() {
    if (DarthVaderbackGround) {
        if (!engine->isCurrentlyPlaying(DarthVaderbackGround)) {
            ZeBackgroundMusic->stop();
        }
        if (ZeBackgroundMusic->isFinished()) {
            ZeBackgroundMusic =
                engine->play2D(DarthVaderbackGround, true, false, true);
        }
    }
}

void BGMDriven::playGateEffect(vec3df pos) 
{
    if (GateEffectSource) {
        if (GateEffect->getIsPaused() == true) {
            GateEffect->setIsPaused(false);
            GateEffect->setPosition(pos);
            return;
        }
        if (GateEffect->isFinished() == true) {
            GateEffect =
                engine->play3D(GateEffectSource, pos, false, false, true);
        }
    }
}

void BGMDriven::updatePlayerPos(vec3df pos, vec3df target, vec3df up) {
    engine->setListenerPosition(pos, target, vec3df(0, 0, 0), up);
}