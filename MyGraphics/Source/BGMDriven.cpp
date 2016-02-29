#include "BGMDriven.h"

BGMDriven::BGMDriven() 
    : DarthVaderbackGround(0), GateEffectSource(0), GateEffect(0),
    StarWarsTheme(0), PokemonGymBattleSource(0), SpaceWarpSource(0),
    john_cenaSource(0), i_amYourFather(0), join_DarkSide(0), join_DarkSideEffect(0),
    iamYourFatherEffect(0)
{
    engine = createIrrKlangDevice();
}

BGMDriven::~BGMDriven()
{
    engine->drop();
}

void BGMDriven::init() {
    DarthVaderbackGround = 
        engine->addSoundSourceFromFile("music//darth_vader_theme_SP2.ogg");
    GateEffectSource =
        engine->addSoundSourceFromFile("music//electric_door_opening_2.ogg");
    StarWarsTheme =
        engine->addSoundSourceFromFile("music//star_wars_edited_SP2.ogg");
    PokemonGymBattleSource =
        engine->addSoundSourceFromFile("music//pokemon_gym_battle.ogg");
    SpaceWarpSource =
        engine->addSoundSourceFromFile("music//space_warp.ogg");
    john_cenaSource =
        engine->addSoundSourceFromFile("music//john_cena.ogg");
    i_amYourFather =
        engine->addSoundSourceFromFile("music//I_am_your_father.ogg");
    join_DarkSide =
        engine->addSoundSourceFromFile("music//join_the_dark_side.ogg");

    //setting volumes for each of the sounds source
    DarthVaderbackGround->setDefaultVolume(0.3f);
    StarWarsTheme->setDefaultVolume(0.5f);
    john_cenaSource->setDefaultVolume(0.5f);
    SpaceWarpSource->setDefaultVolume(0.5f);
    PokemonGymBattleSource->setDefaultVolume(0.3f);

    ZeBackgroundMusic = engine->play2D(StarWarsTheme, true, false, true);

    GateEffect = engine->play3D(GateEffectSource, vec3df(0, 0, 0), false, true, true);
}

void BGMDriven::playDarthVaderBackground() {
    if (DarthVaderbackGround) {
        if (!engine->isCurrentlyPlaying(DarthVaderbackGround)) {
            ZeBackgroundMusic->stop();
            engine->play2D(DarthVaderbackGround, true, false, true);
        }
    }
}

void BGMDriven::playGateEffect(vec3df pos) 
{
    if (GateEffectSource) {
        ZeBackgroundMusic->setVolume(0.2f);
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

void BGMDriven::playJohnCenaBackground() {
    if (john_cenaSource) {
        if (!engine->isCurrentlyPlaying(john_cenaSource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(john_cenaSource, true, false, true);
        }
    }
}

void BGMDriven::playPokemonBattleBackground() {
    if (PokemonGymBattleSource) {
        if (!engine->isCurrentlyPlaying(PokemonGymBattleSource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(PokemonGymBattleSource, true, false, true);
        }
    }
}

void BGMDriven::playStarWarsThemeBackground() {
    if (StarWarsTheme) {
        if (!engine->isCurrentlyPlaying(StarWarsTheme)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(StarWarsTheme, true, false, true);
        }
    }
}

void BGMDriven::playWarpBackground() {
    if (SpaceWarpSource) {
        if (!engine->isCurrentlyPlaying(SpaceWarpSource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(SpaceWarpSource, true, false, true);
        }
    }
}

void BGMDriven::playIamYourFatherEffect(vec3df pos) {
    if (iamYourFatherEffect) {
        ZeBackgroundMusic->setVolume(0.2f);

    }
}

void BGMDriven::playJoinDarkSideEffect(vec3df pos) {
    if (join_DarkSideEffect) {
        ZeBackgroundMusic->setVolume(0.2f);

    }
}
