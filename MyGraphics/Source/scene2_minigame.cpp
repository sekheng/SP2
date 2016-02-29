#include "scene2_minigame.h"

minigame::minigame()
{

}
minigame::~minigame()
{

}
void minigame::init()
{
    piece_state = 1;

    piece1_state = 0;
    piece2_state = 0;
    piece3_state = 0;
    piece4_state = 0;
    piece5_state = 0;
    piece6_state = 0;
    piece7_state = 0;
    piece8_state = 0;
    piece9_state = 0;

    piece1_rotate = 0;
    piece2_rotate = 0;
    piece3_rotate = 0;
    piece4_rotate = 0;
    piece5_rotate = 0;
    piece6_rotate = 0;
    piece7_rotate = 0;
    piece8_rotate = 0;
    piece9_rotate = 0;
}
float minigame::piece1()
{

}
float minigame::piece2()
{

}
float minigame::piece3()
{

}
float minigame::piece4()
{

}
float minigame::piece5()
{

}
float minigame::piece6()
{

}
float minigame::piece7()
{

}
float minigame::piece8()
{

}
float minigame::piece9()
{

}
void minigame::selection_pointer()
{
    if (Application::IsKeyPressed(VK_LEFT))
    {
        piece_state += 1;
    }
    if (Application::IsKeyPressed(VK_RIGHT))
    {
        piece_state -= 1;
    }
    if (Application::IsKeyPressed(VK_UP))
    {
        piece_state -= 3;
    }
    if (Application::IsKeyPressed(VK_DOWN))
    {
        piece_state += 3;
    }
    if (piece_state < 1)
    {
        piece_state = 1;
    }
    if (piece_state > 9)
    {
        piece_state = 1;
    }
}
void minigame::changePieceRotation()
{

}

void minigame::update(double dt)
{
    selection_pointer();
}