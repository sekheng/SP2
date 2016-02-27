#ifndef BGM_DRIVEN_H_
#define BGM_DRIVEN_H_

#include <vector>
#include<string>

using std::vector;
using std::string;

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
    void playDarthVaderBackground();

private:
    vector<string> sound_names;
    vector<string> background_music;

    ISoundEngine *engine;
    ISoundSource *DarthVaderbackGround;
    ISound *ZeBackgroundMusic;
};

#endif