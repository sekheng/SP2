#ifndef BGM_DRIVEN_H_
#define BGM_DRIVEN_H_

//IrrKlang Stuff
#include "../irrKlang-1.5.0/include/irrKlang.h"
using namespace irrklang;
#pragma comment(lib, "../irrKlang-1.5.0/lib/Win32-visualStudio/irrKlang.lib") // link with irrklang.dll
//IrrKlang Stuff

class BGMDriven {
public:
    BGMDriven();
    ~BGMDriven();

    void init();

    void updatePlayerPos(vec3df pos, vec3df target, vec3df up);

    void playDarthVaderBackground();
    void playGateEffect(vec3df pos);

private:
    //these stuff will have the music source files and 
    //ensure engine won't have to keep on going to external files and play music
    ISoundEngine *engine;
    ISoundSource *DarthVaderbackGround;
    ISoundSource *GateEffectSource;

    //these pointers make it clear which music is currently being played
    ISound *ZeBackgroundMusic;
    ISound *GateEffect;
};

#endif