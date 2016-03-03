/******************************************************************************/
/*!
\file       BGMDriven.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
This is where the music logic is being handled
*/
/******************************************************************************/
#ifndef BGM_DRIVEN_H_
#define BGM_DRIVEN_H_

//IrrKlang Stuff
#include "../irrKlang-1.5.0/include/irrKlang.h"
using namespace irrklang;
#pragma comment(lib, "../irrKlang-1.5.0/lib/Win32-visualStudio/irrKlang.lib") // link with irrklang.dll
//IrrKlang Stuff

/******************************************************************************/
/*!
Class BGMDriven:
\brief
A class to handle the music, and allows the use of its function when other scenes are using it.
*/
/******************************************************************************/
class BGMDriven {
public:
    BGMDriven();
    ~BGMDriven();

    void init();

    void updatePlayerPos(vec3df pos, vec3df target, vec3df up);
    
    //background musics
    void playDarthVaderBackground();
    void playJohnCenaBackground();
    void playStarWarsThemeBackground();
    void playWarpBackground();
    void playPokemonBattleBackground();
    void playLovelyLullaby();

    //the sound effects
    void playGateEffect(vec3df pos);
    void playIamYourFatherEffect(vec3df pos);
    void playJoinDarkSideEffect(vec3df pos);

    //to stop all music
    void stopAllSound();

    void reset();

private:
    //these stuff will have the music source files and 
    //ensure engine won't have to keep on going to external files and play music
    ISoundEngine *engine;
    ISoundSource *DarthVaderbackGround;
    ISoundSource *GateEffectSource;
    ISoundSource *StarWarsTheme;
    ISoundSource *PokemonGymBattleSource;
    ISoundSource *SpaceWarpSource;
    ISoundSource *john_cenaSource;
    ISoundSource *i_amYourFather;
    ISoundSource *join_DarkSide;
    ISoundSource *LovelyLullabySource;

    //these pointers make it clear which music is currently being played
    ISound *ZeBackgroundMusic;
    ISound *GateEffect;
    ISound *iamYourFatherEffect;
    ISound *join_DarkSideEffect;

    bool soundEffectArePlaying();
    bool playIAmYourFatherOnce;
    bool playJoinDarkSideOnce;
};

#endif