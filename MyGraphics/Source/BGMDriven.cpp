#include "BGMDriven.h"

/******************************************************************************/
/*!
\brief - A default constructor, and the IrrKlang engine is being started right here
*/
/******************************************************************************/
BGMDriven::BGMDriven()
    : DarthVaderbackGround(0), GateEffectSource(0), GateEffect(0),
    StarWarsTheme(0), PokemonGymBattleSource(0), SpaceWarpSource(0),
    john_cenaSource(0), i_amYourFather(0), join_DarkSide(0), join_DarkSideEffect(0),
    iamYourFatherEffect(0), LovelyLullabySource(0), playIAmYourFatherOnce(false), playJoinDarkSideOnce(false)
{
    engine = createIrrKlangDevice();
}

/******************************************************************************/
/*!
\brief - A destructor, and the IrrKlang engine is being dropped right here
*/
/******************************************************************************/
BGMDriven::~BGMDriven()
{
    engine->drop();
}

/******************************************************************************/
/*!
\brief - Where the initialization of the ISoundSource and ISound pointers begin.
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play Darth Vader theme as a background music

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
void BGMDriven::playDarthVaderBackground() {
    if (DarthVaderbackGround) {
        if (!engine->isCurrentlyPlaying(DarthVaderbackGround)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(DarthVaderbackGround, true, false, true);
        }
    }
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play the 3D gate sound effect

\param pos - the position of the Gate

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - An update function to update the player's position, target and up. Be warn that 
if this function is being updated too many times, it will cause inefficiency.

\param pos - position of the player

\param target - target of / where the player is looking at

\param up - the up vector of the player.
*/
/******************************************************************************/
void BGMDriven::updatePlayerPos(vec3df pos, vec3df target, vec3df up) {
    engine->setListenerPosition(pos, target, vec3df(0, 0, 0), up);
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play John Cena theme as a background music

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
void BGMDriven::playJohnCenaBackground() {
    if (john_cenaSource) {
        if (!engine->isCurrentlyPlaying(john_cenaSource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(john_cenaSource, true, false, true);
        }
    }
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play Pokemon Battle theme as a background music

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
void BGMDriven::playPokemonBattleBackground() {
    if (PokemonGymBattleSource) {
        if (!engine->isCurrentlyPlaying(PokemonGymBattleSource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(PokemonGymBattleSource, true, false, true);
        }
    }
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play Star Wars theme as a background music

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
void BGMDriven::playStarWarsThemeBackground() {
    if (StarWarsTheme) {
        if (!engine->isCurrentlyPlaying(StarWarsTheme)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(StarWarsTheme, true, false, true);
        }
    }
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play Space Warp as a background music

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
void BGMDriven::playWarpBackground() {
    if (SpaceWarpSource) {
        if (!engine->isCurrentlyPlaying(SpaceWarpSource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(SpaceWarpSource, true, false, true);
        }
    }
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play the 3D effect of 'I am Your Father'

\param pos - the position of the object which will play out this sound

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - A method functions dedicated to just play the 3D effect of 'Join the Dark Side'

\param pos - position of the object to play this sound

\exception - if the source file of the music cannot be found, nothing is played
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - return true / false if the sound effects are being played

\return true - if either 1 of the sound effects are being played

\return false - if no sound effect is played
*/
/******************************************************************************/
bool BGMDriven::soundEffectArePlaying() {
    if (engine->isCurrentlyPlaying(GateEffectSource) == false ||
        engine->isCurrentlyPlaying(i_amYourFather) == false ||
        engine->isCurrentlyPlaying(join_DarkSide) == false) {
        return true;
    }
    return false;
}

/******************************************************************************/
/*!
\brief - A method functions to stop all sounds
*/
/******************************************************************************/
void BGMDriven::stopAllSound() {
    engine->stopAllSounds();
}

/******************************************************************************/
/*!
\brief - A method functions dedicated to play a Lullaby as a background music

\exception - if the source file cannot be found, nothing is played
*/
/******************************************************************************/
void BGMDriven::playLovelyLullaby() {
    if (LovelyLullabySource) {
        if (!engine->isCurrentlyPlaying(LovelyLullabySource)) {
            ZeBackgroundMusic->stop();
            ZeBackgroundMusic = engine->play2D(LovelyLullabySource, true, false, true);
        }
    }
}