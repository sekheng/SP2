#include "BGMDriven.h"

BGMDriven::BGMDriven() 
    : DarthVaderbackGround(0), GateEffectSource(0), GateEffect(0),
    StarWarsTheme(0), PokemonGymBattleSource(0), SpaceWarpSource(0),
    john_cenaSource(0), i_amYourFather(0), join_DarkSide(0), join_DarkSideEffect(0),
    iamYourFatherEffect(0), LovelyLullabySource(0), playIAmYourFatherOnce(false), playJoinDarkSideOnce(false)
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
    LovelyLullabySource =
        engine->addSoundSourceFromFile("music//1-01 Lullaby of Open Eyes.ogg");

    //setting volumes for each of the sounds source
    DarthVaderbackGround->setDefaultVolume(0.3f);
    StarWarsTheme->setDefaultVolume(0.5f);
    john_cenaSource->setDefaultVolume(0.5f);
    SpaceWarpSource->setDefaultVolume(1.f);
    PokemonGymBattleSource->setDefaultVolume(0.3f);
    LovelyLullabySource->setDefaultVolume(0.5f);

    ZeBackgroundMusic = engine->play2D(StarWarsTheme, true, false, true);

    GateEffect = engine->play3D(GateEffectSource, vec3df(0, 0, 0), false, true, true);
    iamYourFatherEffect = engine->play3D(i_amYourFather, vec3df(0, 0, 0), false, true, true);
    join_DarkSideEffect = engine->play3D(join_DarkSide, vec3df(0, 0, 0), false, true, true);
}

void BGMDriven::playDarthVaderBackground() {
    if (DarthVaderbackGround) {
        if (!engine->isCurrentlyPlaying(DarthVaderbackGround)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(DarthVaderbackGround, true, false, true);
        }
    }
}

void BGMDriven::playGateEffect(vec3df pos) 
{
    if (GateEffectSource) {
        ZeBackgroundMusic->setVolume(0.1f);
        if (GateEffect->getIsPaused() == true) {
            GateEffect->setIsPaused(false);
            GateEffect->setPosition(pos);
        }
        else if (GateEffect->isFinished() == true ) {
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
    if (iamYourFatherEffect && playIAmYourFatherOnce == false) {
        ZeBackgroundMusic->setVolume(0.1f);
        playIAmYourFatherOnce = true;
        if (iamYourFatherEffect->getIsPaused() == true) {
            iamYourFatherEffect->setIsPaused(false);
            iamYourFatherEffect->setPosition(pos);
        }
        else if (iamYourFatherEffect->isFinished() == true) {
            iamYourFatherEffect =
                engine->play3D(i_amYourFather, pos, false, false, true);
        }
    }
}

void BGMDriven::playJoinDarkSideEffect(vec3df pos) {
    if (join_DarkSideEffect && playJoinDarkSideOnce == false) {
        ZeBackgroundMusic->setVolume(0.1f);
        playJoinDarkSideOnce = true;
        if (join_DarkSideEffect->getIsPaused() == true) {
            join_DarkSideEffect->setIsPaused(false);
            join_DarkSideEffect->setPosition(pos);
        }
        else if (join_DarkSideEffect->isFinished() == true) {
            join_DarkSideEffect =
                engine->play3D(join_DarkSide, pos, false, false, true);
        }
    }
}

bool BGMDriven::soundEffectArePlaying() {
    if (GateEffect->isFinished() == false ||
        iamYourFatherEffect->isFinished() == false ||
        join_DarkSideEffect->isFinished() == false) {
        return true;
    }
    return false;
}

void BGMDriven::stopAllSound() {
    engine->stopAllSounds();
}

void BGMDriven::playLovelyLullaby() {
    if (LovelyLullabySource) {
        if (!engine->isCurrentlyPlaying(LovelyLullabySource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(LovelyLullabySource, true, false, true);
        }
    }
}