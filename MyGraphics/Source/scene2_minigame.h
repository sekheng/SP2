#ifndef SCENE2_MINIGAME_H_
#define SCENE2_MINIGAME_H_

//next time, Don't ANYHOW include!
//#include "Application.h"

class minigame
{
public:
    minigame();
    ~minigame();
    void init();
    float piece1();
    float piece2();
    float piece3();
    float piece4();
    float piece5();
    float piece6();
    float piece7();
    float piece8();
    float piece9();
    void selection_pointer();
    void changePieceRotation();
    void update(double dt, bool start_game);
    bool result();
    void updatePieceState();
    void minigame_started(bool started);
    bool minigame_started();
    short get_selector_state();
private:
    short piece_state;
    float piece1_rotate;
    float piece2_rotate;
    float piece3_rotate;
    float piece4_rotate;
    float piece5_rotate;
    float piece6_rotate;
    float piece7_rotate;
    float piece8_rotate;
    float piece9_rotate;
    short piece1_state;
    short piece2_state;
    short piece3_state;
    short piece4_state;
    short piece5_state;
    short piece6_state;
    short piece7_state;
    short piece8_state;
    short piece9_state;
    bool start;
    double time;
    double input_delay;
protected:

};


#endif